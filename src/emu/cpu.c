#include "emu/cpu.h"

#include "common.h"
#include "emu/opcode.h"
#include "log.h"

#include <stdio.h>
#include <string.h>

/* NOTE: ROM has a maximum size of 12MiB */
#define MAX_ROM_SIZE 12582912u
#define ROM_START    0x400000

void cpu_powerup(Cpu *cpu, const char *romfile) {
	FILE *rom = xfopen(romfile, "rb");

	/* FIXME: I think this is not portable */
	fseek(rom, 0L, SEEK_END);
	usize rom_size = ftell(rom);
	rewind(rom);

	if (rom_size > MAX_ROM_SIZE) {
		log_fatal("Rom is larger than 12MiB.");
		exit(EXIT_FAILURE);
	}

	/* Only allocate RAM if there's no RAM already allocated */
	if (cpu->ram == NULL) {
		cpu->ram = xcalloc(RAM_SIZE, sizeof(u8));
	}

	fread(cpu->ram + ROM_START, sizeof(u8), rom_size, rom);
	fclose(rom);
	log_info("Readed %d KiB from %s", rom_size / 1024, romfile);

	memset(cpu->regs, 0, sizeof(u16) * REG_COUNT);
}

void cpu_shutdown(Cpu *cpu) {
	free(cpu->ram);
	cpu->ram = NULL;
}

void cpu_reset(Cpu *cpu) {
	cpu->program_counter = ram_read32(cpu, VECTOR_ADDR | VEC_RESET) & 0x00ffffff;

	cpu->stack_pointer = ram_read32(cpu, VECTOR_ADDR | VEC_STACK);
	cpu->stack_pointer &= 0x00ffffff; /* Ignore last byte */

	cpu->regs[REG_X] = cpu->stack_pointer;
	cpu->regs[REG_Y] = cpu->stack_pointer >> 16;

	cpu->status = 0x0004; /* Clear status, and set Ignore Interrupt flag */
	cpu->cycles = 6;
}

void cpu_hardware_request(Cpu *cpu, u8 type) {
	if (cpu->cycles != 0) {
		/* Can't execute interrupt if instruction is executing. */
		cpu->buf_interrupt = true;
		cpu->next_interrupt = type;
		return;
	}

	if (type == VEC_IRQ && bit_get(cpu->status, ST_INTERRUPT)) {
		return; /* Interrupt is disabled */
	}

	stack_push(cpu, cpu->program_counter);
	stack_push(cpu, cpu->program_counter >> 16);
	stack_push(cpu, cpu->status);

	bit_set(&cpu->status, ST_INTERRUPT, true);
	cpu->program_counter = ram_read32(cpu, VEC_ADDRESS | type) & 0x00ffffff;

	cpu->cycles += type == VEC_IRQ ? 8 : 7;
}

void cpu_exception(Cpu *cpu, u8 type) {
	if (cpu->cycles != 0) {
		/* Can't execute interrupt if instruction is executing. */
		cpu->buf_interrupt = true;
		cpu->next_interrupt = VEC_ADDRESS;
		return;
	}

	switch (type) {
	case VEC_DIVZERO:
		cpu->cycles += 5;
		break;
	case VEC_INSTR:
		cpu->program_counter += 2;
		cpu->cycles += 6;
		break;
	case VEC_ADDRESS:
		cpu->cycles += 6;
		break;
	}

	stack_push(cpu, cpu->program_counter);
	stack_push(cpu, cpu->program_counter >> 16);
	stack_push(cpu, cpu->status);

	cpu->program_counter = ram_read32(cpu, VEC_ADDRESS | type) & 0x00ffffff;
}

void cpu_step(Cpu *cpu) {
	if (cpu->buf_interrupt) {
		if (cpu->next_interrupt == VEC_ADDRESS) {
			cpu_exception(cpu, cpu->next_interrupt);
		} else {
			cpu_hardware_request(cpu, cpu->next_interrupt);
		}
	}

	cpu->current_opcode = ram_read16(cpu, cpu->program_counter);
	cpu->program_counter += 2;

	opcode_execute(cpu);
}

void cpu_clock(Cpu *cpu) {
	if (cpu->cycles != 0) {
		cpu->cycles -= 1;
		return;
	}

	cpu_step(cpu);
}

u16 ram_read16(Cpu *cpu, u32 addr) {
	if (addr > RAM_SIZE) {
		cpu_exception(cpu, VEC_ADDRESS);
		addr &= 0x00ffffff;
	}

	u8 low = cpu->ram[addr];
	u8 high = cpu->ram[addr + 1];
	return (high << 8) | low;
}

u32 ram_read32(Cpu *cpu, u32 addr) {
	if (addr > RAM_SIZE) {
		cpu_exception(cpu, VEC_ADDRESS);
		addr &= 0x00ffffff;
	}

	u16 low = ram_read16(cpu, addr);
	u16 high = ram_read16(cpu, addr + 2);
	return (high << 16) | low;
}

void ram_write16(Cpu *cpu, u32 addr, u16 data) {
	if (addr > RAM_SIZE) {
		cpu_exception(cpu, VEC_ADDRESS);
		addr &= 0x00ffffff;
	}

	cpu->ram[addr] = data & 0x00ff; /* Write low byte */
	cpu->ram[addr + 1] = data >> 8; /* Write high byte */
}

u16 stack_pop(Cpu *cpu) {
	cpu->stack_pointer -= 2;
	return ram_read16(cpu, cpu->stack_pointer);
}

void stack_push(Cpu *cpu, u16 data) {
	ram_write16(cpu, cpu->stack_pointer, data);
	cpu->stack_pointer += 2;
}

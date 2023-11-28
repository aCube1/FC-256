#include "emu/cpu.h"

#include "common.h"
#include "emu/opcode.h"
#include "log/log.h"

#include <string.h>

static void set_stackpointer(Cpu *cpu, u32 pointer) {

	cpu->stack_pointer = pointer;
	cpu->regs[REG_LSP] = pointer & 0x0000ffff;
	cpu->regs[REG_HSP] = pointer >> 16;
}

void cpu_powerup(Cpu *cpu) {
	if (cpu->ram == NULL) {
		cpu->ram = xcalloc(RAM_SIZE, sizeof(u8));
	}

	memset(cpu->regs, 0, sizeof(u16) * REG_COUNT);
}

void cpu_shutdown(Cpu *cpu) {
	free(cpu->ram);
	cpu->ram = NULL;
}

void cpu_reset(Cpu *cpu) {
	cpu->program_counter = ram_read32(cpu, VECTOR_ADDR | VEC_RESET);
	set_stackpointer(cpu, ram_read32(cpu, VECTOR_ADDR | VEC_STACK));

	/* Clear status, and set Ignore Interrupts flag */
	cpu->status = 0x0004;

	cpu->cycles = 6; /* Reset takes 6 cycles to complete */
}

void cpu_step(Cpu *cpu) {
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
	if (addr < 0 || addr > RAM_SIZE) {
		log_fatal("Attempt to read address %#x is out of bounds!", addr);
		exit(EXIT_FAILURE);
	}

	return (cpu->ram[addr + 1] << 8) | cpu->ram[addr];
}

u32 ram_read32(Cpu *cpu, u32 addr) {
	u16 low = ram_read16(cpu, addr);
	u16 high = ram_read16(cpu, addr + 2);

	if ((high & 0xff00) != 0x00) {
		/* TODO: Trigger interrupt request: Illegal Address */
		log_trace("32-bit data readed has set the last byte!");
	}

	return (high << 16) | low;
}

void ram_write16(Cpu *cpu, u32 addr, u16 data) {
	if (addr < 0 || addr > RAM_SIZE) {
		log_fatal("Attempt to write on address %#x is out of bounds!", addr);
		exit(EXIT_FAILURE);
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

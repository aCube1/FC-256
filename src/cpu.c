#include "cpu.h"

#include "opcodes.h"

#include <stdlib.h>
#include <string.h>

void cpuPowerUp(CPU *cpu) {
	if (cpu->memory == NULL) {
		cpu->memory = calloc(RAM_SIZE, sizeof(u8));
	}

	/* Reset general registers */
	memset(cpu->regs, 0, sizeof(u8) * REGS_COUNT);
}

void cpuShutdown(CPU *cpu) {
	free(cpu->memory);
}

void cpuReset(CPU *cpu) {
	/* Jump to reset routine */
	cpu->actual_pc = cpuMemRead24(cpu, VEC_RESET);
	cpu->regs[REG_PC] = cpu->actual_pc & 0xffff;

	cpu->status.raw = 0xe0; /* NOTE: Always set the unused bits. */
	cpu->data_bank = 0x00;

	cpu->cycles = 8;
}

void cpuClock(CPU *cpu) {
	if (cpu->cycles == 0) {
		u16 current_opcode = cpuMemRead16(cpu, cpu->actual_pc);

		cpu->actual_pc += 2;
		cpu->regs[REG_PC] = cpu->actual_pc & 0xffff;

		opcode_execute(cpu, current_opcode);
	}

	cpu->cycles -= 1;
}

u8 cpuMemRead(CPU *cpu, u32 addr) {
	if (cpu->memory == NULL) {
		log_error("Unable to read unallocated RAM!");
		return 0x00;
	}

	if (addr < 0 || addr > RAM_SIZE) {
		log_error("Address %#x is out of bounds!", addr);
		return 0x00;
	}

	return cpu->memory[addr];
}

u16 cpuMemRead16(CPU *cpu, u32 addr) {
	u8 l = cpuMemRead(cpu, addr);
	u8 h = cpuMemRead(cpu, addr + 1);

	return (h << 8) | l;
}

u32 cpuMemRead24(CPU *cpu, u32 addr) {
	u16 data = cpuMemRead16(cpu, addr);
	u8 bank = cpuMemRead(cpu, addr + 2);

	return (bank << 16) | data;
}

void cpuMemWrite(CPU *cpu, u32 addr, u8 data) {
	if (cpu->memory == NULL) {
		log_error("Unable to write on unallocated RAM!");
		return;
	}

	if (addr < 0 || addr > RAM_SIZE) {
		log_error("Address %#x is out of bounds!", addr);
	}

	cpu->memory[addr] = data;
}

void cpuMemWrite16(CPU *cpu, u32 addr, u16 data) {
	cpuMemWrite(cpu, addr, data & 0xff);   /* Low byte */
	cpuMemWrite(cpu, addr + 1, data >> 8); /* High byte */
}

void cpuMemWrite24(CPU *cpu, u32 addr, u32 data) {
	cpuMemWrite16(cpu, addr, data & 0xffff); /* Data bytes */
	cpuMemWrite(cpu, addr + 2, data >> 16);  /* Bank byte */
}

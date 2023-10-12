#include "cpu.h"

#include <stdlib.h>

#define RESET_VECTOR   ((u32)0x400000)
#define IRQ_VECTOR     ((u32)0x400003)
#define NMI_VECTOR     ((u32)0x400006)
#define DIVZERO_VECTOR ((u32)0x40000c)

void cpuPowerUp(CPU *cpu, const char *file) {
	(void)file;

	cpu->status.raw = 0xe0; /* NOTE: Always set the unused bits. */
	cpu->data_bank = 0x00;

	cpu->ram = (u8 *)calloc(RAM_SIZE, sizeof(u8));

	/* Reset general registers */
	for (u8 i = 0; i < REG_LENGHT; i += 1) {
		cpu->regs[i] = 0x0000;
	}
}

void cpuReset(CPU *cpu) {
	/* Jump to reset routine */
	cpu->regs[REG_PC] = cpuMemRead16(cpu, RESET_VECTOR);
	cpu->program_bank = cpuMemRead(cpu, RESET_VECTOR + 2);
}

void cpuShutdown(CPU *cpu) {
	free(cpu->ram);
}

u8 cpuMemRead(CPU *cpu, u32 addr) {
	if (addr < 0 || addr > RAM_SIZE) {
		log_error("Address %#x is out of bounds!", addr);
		return 0x00;
	}

	return cpu->ram[addr];
}

u16 cpuMemRead16(CPU *cpu, u32 addr) {
	u8 l = cpuMemRead(cpu, addr);
	u8 h = cpuMemRead(cpu, addr + 1);

	return (h << 8) | l;
}

void cpuMemWrite(CPU *cpu, u32 addr, u8 data) {
	if (addr < 0 || addr > RAM_SIZE) {
		log_error("Address %#x is out of bounds!", addr);
	}

	cpu->ram[addr] = data;
}

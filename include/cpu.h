#ifndef _CPU_H_
#define _CPU_H_

#include "types.h"

#define RAM_SIZE (u32)(0xffffff + 1) /* NOTE: RAM Size has 16MiB of addressable memory. */

/* clang-format off */
enum Registers {
	REG_0, REG_1, REG_2, REG_3,
	REG_A, REG_B, REG_C, REG_D,
	REG_E, REG_F,
	REG_W, REG_X, REG_Y, REG_Z,

	REG_PC, /* Program Counter */
	REG_SP, /* Stack Pointer */
	REG_LENGHT,
};

/* clang-format on */

typedef struct CPU {
	u8 *ram;

	/* General Registers */
	u16 regs[REG_LENGHT];

	u8 program_bank; /* Program Bank */
	u8 data_bank;    /* Data Bank */

	union {
		struct {
			u8 I : 1; /* Disable Interrupt */
			u8 O : 1; /* Overflow/Underflow */
			u8 C : 1; /* Carry */
			u8 N : 1; /* Negative */
			u8 Z : 1; /* Zero */
			u8 U : 3; /* Unused */
		};

		u8 raw;
	} status;
} CPU;

void cpuPowerUp(CPU *cpu, const char *file);
void cpuReset(CPU *cpu);

void cpuShutdown(CPU *cpu);

u8 cpuMemRead(CPU *cpu, u32 addr);
u16 cpuMemRead16(CPU *cpu, u32 addr);

void cpuMemWrite(CPU *cpu, u32 addr, u8 data);

#endif /* _CPU_H_ */

#ifndef _CPU_H_
#define _CPU_H_

#include "operand.h"
#include "types.h"

/* NOTE: RAM Size has 16MiB of addressable memory. */
#define RAM_SIZE ((u32)0xffffff + 1)

/* clang-format off */
enum Registers {
	REG_A, REG_B, REG_C,
	REG_PC, /* Program Counter */
	REG_X, REG_Y, REG_Z,
	REG_SP, /* Stack Pointer*/

	REGS_COUNT,
};

/* clang-format on */

enum SystemVectors {
	VEC_RESET = 0x400000,
	VEC_IRQ = 0x400003,
	VEC_NMI = 0x400006,
	VEC_DIVZERO = 0x400009,
};

typedef struct CPU {
	u8 *memory;

	u16 regs[REGS_COUNT]; /* General Registers */
	u32 actual_pc;        /* PB + program counter */

	/* NOTE: Data Bank is not used in this emulator, but will stay here as a reference. */
	// u8 data_bank; /* Data Bank(DB) */

	union {
		struct {
			u8 Z : 1; /* Zero */
			u8 N : 1; /* Negative */
			u8 C : 1; /* Carry */
			u8 O : 1; /* Overflow/Underflow */
			u8 I : 1; /* Disable Interrupt */
			u8 U : 3; /* Unused */
		};

		u8 raw;
	} status; /* Status register */

	/* Internal private data */
	u16 cycles;

	Operand op1;
	Operand op2;
} CPU;

void cpuPowerUp(CPU *cpu);
void cpuShutdown(CPU *cpu);

void cpuReset(CPU *cpu);
void cpuClock(CPU *cpu);

u8 cpuMemRead(CPU *cpu, u32 addr);
u16 cpuMemRead16(CPU *cpu, u32 addr);
u32 cpuMemRead24(CPU *cpu, u32 addr);

void cpuMemWrite(CPU *cpu, u32 addr, u8 data);
void cpuMemWrite16(CPU *cpu, u32 addr, u16 data);
void cpuMemWrite24(CPU *cpu, u32 addr, u32 data);

#endif /* _CPU_H_ */

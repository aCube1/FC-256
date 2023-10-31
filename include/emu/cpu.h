#ifndef _EMU_CPU_H_
#define _EMU_CPU_H_

#include "emu/operand.h"
#include "types.h"

/* NOTE: RAM Size has 16MiB of addressable memory. */
#define RAM_SIZE (0x1000000u)

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

enum StatusBitPosition {
	STATUS_ZERO = 0,  /* 0000-000x -> Zero */
	STATUS_NEGATIVE,  /* 0000-00x0 -> Negative */
	STATUS_CARRY,     /* 0000-0x00 -> Carry */
	STATUS_OVERFLOW,  /* 0000-x000 -> Overflow/Underflow */
	STATUS_INTERRUPT, /* 000x-0000 -> Disable interrupt */
};

typedef struct CPU {
	u8 *memory;

	u8 status;            /* Status register */
	u16 regs[REGS_COUNT]; /* General Registers */
	u32 actual_pc;        /* PB + program counter */

	/* NOTE: Data Bank is not used in this emulator, but will stay here as a reference. */
	// u8 data_bank; /* Data Bank(DB) */

	/* Internal private data */
	u16 cycles;

	Operand op1;
	Operand op2;

	u16 opcode;
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

#endif /* _EMU_CPU_H_ */

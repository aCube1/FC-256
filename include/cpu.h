#ifndef _CPU_H_
#define _CPU_H_

#include "types.h"

#define RAM_SIZE (u32)(0xffffff + 1) /* NOTE: RAM Size has 16MiB of addressable memory. */

typedef struct CPU {
	u8 *ram;

	/* General Registers */
	u16 rA, rB, rC;
	u16 rX, rY, rZ;

	u16 reg_pc; /* Program Counter */
	u16 reg_sp; /* Stack Pointer */

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

	union {
		struct {
			u8 identifier : 6;
			u8 reg_count : 2;
			u8 access_mode : 2;
			u8 address_mode : 5;
			u8 : 2; /* Unused */
		};

		u16 raw;
	} current_opcode;
} CPU;

void cpuPowerUp(CPU *cpu, const char *file);
void cpuReset(CPU *cpu);

void cpuShutdown(CPU *cpu);

u8 cpuMemRead(CPU *cpu, u32 addr);
u16 cpuMemRead16(CPU *cpu, u32 addr);

void cpuMemWrite(CPU *cpu, u32 addr, u8 data);

#endif /* _CPU_H_ */

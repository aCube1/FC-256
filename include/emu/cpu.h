#ifndef _EMU_CPU_H_
#define _EMU_CPU_H_

#include "types.h"

/* NOTE: RAM has 16MiB of addrassable memory. */
#define RAM_SIZE    16777216u

#define VECTOR_ADDR 0xffff00u

enum SystemVectors {
	VEC_ADDRESS = 0xe4, /* 0xe4-e7: Illegal Address */
	VEC_ILLEGAL = 0xe8, /* 0xe8-eb: Illegal Instruction */
	VEC_DIVZERO = 0xec, /* 0xec-ef: Division by Zero */
	VEC_NMI = 0xf0,     /* 0xf0-f3: Hardware NMI */
	VEC_IRQ = 0xf4,     /* 0xf4-f7: Hardware IRQ */
	VEC_RESET = 0xf8,   /* 0xf8-fb: Reset */
	VEC_STACK = 0xfc,   /* 0xfc-ff: Stack Address */
};

enum ProgramStatus {
	ST_CARRY = 0,
	ST_ZERO = 1,
	ST_INTERRUPT = 2,
	ST_OVERFLOW = 14,
	ST_SIGN = 15,
};

enum Registers {
	REG_0,
	REG_1,
	REG_2,
	REG_3,
	REG_4,
	REG_5,
	REG_6,
	REG_7,
	REG_A,
	REG_B,
	REG_C,
	REG_D,
	REG_E,
	REG_F,
	REG_LSP, /* rX */
	REG_HSP, /* rY */
	REG_COUNT,
};

typedef struct Cpu {
	u8 *ram;
	u16 regs[REG_COUNT];

	u16 status; /* SO------ -----IZC */
	u32 program_counter;
	u32 stack_pointer;

	/* Internal Private Data */
	struct Operands {
		s16 offset; /* Only used by Relative address modes */
		u16 src;
		u32 dest;
		bool is_addr;
	} operand;

	u16 cycles; /* Remaining cycles */
	u16 current_opcode;
} Cpu;

void cpu_powerup(Cpu *cpu);
void cpu_shutdown(Cpu *cpu);

void cpu_reset(Cpu *cpu);
void cpu_step(Cpu *cpu);
void cpu_clock(Cpu *cpu);

u16 ram_read16(Cpu *cpu, u32 addr);
u32 ram_read32(Cpu *cpu, u32 addr);

void ram_write16(Cpu *cpu, u32 addr, u16 data);

u16 stack_pop(Cpu *cpu);
void stack_push(Cpu *cpu, u16 data);

#endif /* _EMU_CPU_H_ */

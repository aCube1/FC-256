#ifndef _CPU_OPCODES_H_
#define _CPU_OPCODES_H_

#include "cpu.h"

#define MAX_OPCODES (0x3ff + 1) /* 1024 opcode identifiers */

enum AddressingMode {
	ADDR_IMP,   /* 0x00 - Implied   : No Operand */
	ADDR_REL,   /* 0x01 - Relative  : Offset */
	ADDR_IMM,   /* 0x02 - Immediate : rX, Const */
	ADDR_REG_1, /* 0x03 - Register  : rX */
	ADDR_REG_2, /* 0x04 - Register  : rX, rY */
	ADDR_ABS_1, /* 0x05 - Absolute  : (Addr) */
	ADDR_ABS_2, /* 0x06 - Absolute  : (Addr), Const */
	ADDR_ABS_3, /* 0x07 - Absolute  : (Addr), rX */
	ADDR_ABS_4, /* 0x08 - Absolute  : rX, (Addr) */
	ADDR_BNK_1, /* 0x09 - Indirect  : (Bank, rX) */
	ADDR_BNK_2, /* 0x0a - Banked    : (Bank, rX), Const */
	ADDR_BNK_3, /* 0x0b - Banked    : (Bank, rX), rY */
	ADDR_BNK_4, /* 0x0c - Banked    : rX, (Bank, rY) */
	ADDR_IDX_1, /* 0x0d - Indexed   : (Addr, rX) */
	ADDR_IDX_2, /* 0x0e - Indexed   : (Addr, rX), rY */
	ADDR_IDX_3, /* 0x0f - Indexed   : rX, (Addr, rY) */
};

typedef struct Opcode {
	const char name[5];
	enum AddressingMode mode;
	u8 cycles;
	void (*handler)(CPU *);
	void (*addr)(CPU *, u8, u8, u8);
} Opcode;

extern const Opcode op_table[MAX_OPCODES];

int opcode_execute(CPU *cpu, u16 opcode);

#endif /* _CPU_OPCODES_H_ */

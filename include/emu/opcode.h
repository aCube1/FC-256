#ifndef _EMU_OPCODES_H_
#define _EMU_OPCODES_H_

#include "emu/cpu.h"

#define OPCODE_COUNT        0x40

#define OP_IDENTIFIER_START 0
#define OP_IDENTIFIER_MASK  0x3f

#define OP_ADDRMODE_START   6
#define OP_ADDRMODE_MASK    0x0f

#define OP_FIRSTREG_START   10
#define OP_FIRSTREG_MASK    0x07

#define OP_SECONDREG_START  13
#define OP_SECONDREG_MASK   0x07

/* NOTE: All handlers always return the cycles taken. */
typedef u8 (*AddrHandler)(CPU *, u8, u8, u8);
typedef u8 (*OpcodeHandler)(CPU *);

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
	ADDR_BNK_1, /* 0x09 - Banked    : (Bank:rX) */
	ADDR_BNK_2, /* 0x0a - Banked    : (Bank:rX), Const */
	ADDR_BNK_3, /* 0x0b - Banked    : (Bank:rX), rY */
	ADDR_BNK_4, /* 0x0c - Banked    : rX, (Bank:rY) */
	ADDR_IDX_1, /* 0x0d - Indexed   : (Addr:rX) */
	ADDR_IDX_2, /* 0x0e - Indexed   : (Addr:rX), rY */
	ADDR_IDX_3, /* 0x0f - Indexed   : rX, (Addr:rY) */
	ADDR_COUNT
};

extern AddrHandler opcode_addresses[ADDR_COUNT];
extern OpcodeHandler opcode_handlers[OPCODE_COUNT];

u8 addrREL(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg);
u8 addrIMM(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg);
u8 addrREG(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg);
u8 addrABS(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg);
u8 addrBNK(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg);
u8 addrIDX(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg);

u8 opcodeMOV(CPU *cpu);
u8 opcodeADD(CPU *cpu);
u8 opcodeSUB(CPU *cpu);
// u8 opcodeADC(CPU *cpu);
// u8 opcodeSBC(CPU *cpu);
// u8 opcodeINC(CPU *cpu);
// u8 opcodeDEC(CPU *cpu);
// u8 opcodeMUL(CPU *cpu);
// u8 opcodeDIV(CPU *cpu);

#endif /* _EMU_OPCODES_H_ */

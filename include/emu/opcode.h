#ifndef _EMU_OPCODE_H_
#define _EMU_OPCODE_H_

#include "emu/cpu.h"
#include "types.h"

#define OPCODE_COUNT (UINT8_MAX + 1)

enum AddressingMode {
	ADDR_IMP_0 = 0x0, /* Implied   - Nothing */
	ADDR_REG_1 = 0x2, /* Register  - r1 */
	ADDR_IMM_1 = 0x4, /* Immediate - Const */
	ADDR_ABS_0 = 0x6, /* Absolute  - [Addr] */
	ADDR_IND_2 = 0x8, /* Indexed   - [Bank:r1] */
	ADDR_REL_0 = 0xa, /* Relative  - (Offset) */
	ADDR_REL_1 = 0xc, /* Relative  - (Offset), Const */
	ADDR_IMP_1 = 0xe, /* Implied   - Nothing */

	ADDR_REG_0 = 0x1, /* Register  - r1, r2 */
	ADDR_IMM_0 = 0x3, /* Immediate - r1, Const */
	ADDR_IND_0 = 0x5, /* Indexed   - [Bank:r1], r2 */
	ADDR_IND_1 = 0x7, /* Indexed   - r1, [Bank:r2] */
	ADDR_IND_3 = 0x9, /* Indexed   - [Bank:r1], Const */
	ADDR_ABS_1 = 0xb, /* Absolute  - [Addr], r1 */
	ADDR_ABS_2 = 0xd, /* Absolute  - r1, [Addr] */
	ADDR_ABS_3 = 0xf, /* Absolute  - [Addr], Const */
};

typedef struct Opcode {
	const char name[4];
	enum AddressingMode addressing;
	void (*handler)(Cpu *);
	u8 cycles;
} Opcode;

extern const Opcode op_table[OPCODE_COUNT];

int opcode_execute(Cpu *cpu, u16 opcode);

/* clang-format off */
void op_add(Cpu *cpu); void op_and(Cpu *cpu); void op_bif(Cpu *cpu); void op_bnf(Cpu *cpu);
void op_bra(Cpu *cpu); void op_clr(Cpu *cpu); void op_cmp(Cpu *cpu); void op_dec(Cpu *cpu);
void op_div(Cpu *cpu); void op_dvs(Cpu *cpu); void op_hlt(Cpu *cpu); void op_inc(Cpu *cpu);
void op_ior(Cpu *cpu); void op_jmp(Cpu *cpu); void op_jsr(Cpu *cpu); void op_mls(Cpu *cpu);
void op_mov(Cpu *cpu); void op_mul(Cpu *cpu); void op_nop(Cpu *cpu); void op_not(Cpu *cpu);
void op_pop(Cpu *cpu); void op_psh(Cpu *cpu); void op_ret(Cpu *cpu); void op_rol(Cpu *cpu);
void op_ror(Cpu *cpu); void op_rti(Cpu *cpu); void op_set(Cpu *cpu); void op_shl(Cpu *cpu);
void op_shr(Cpu *cpu); void op_sub(Cpu *cpu); void op_tst(Cpu *cpu); void op_xor(Cpu *cpu);
void op_xxx(Cpu *cpu);
/* clang-format on */

#endif /*cpu _EMU_OPCODE_H_ */

#ifndef _EMU_OPCODE_H_
#define _EMU_OPCODE_H_

#include "emu/cpu.h"
#include "types.h"

#define OPCODE_COUNT (UINT8_MAX + 1)

typedef struct Opcode {
	const char name[4];
	void (*handler)(Cpu *);
	void (*addr)(Cpu *, u8);
	u8 addr_mode; /* 0 -> 3 */
	u8 cycles;
} Opcode;

extern const Opcode op_table[OPCODE_COUNT];

int opcode_execute(Cpu *cpu);

/* Register  - 0 - r1, r2
 * Register  - 1 - r1 */
void addr_reg(Cpu *cpu, u8 mode);

/* Immediate - 0 - r1, Const
 * Immediate - 1 - Const */
void addr_imm(Cpu *cpu, u8 mode);

/* Indexed - 0 - [Bank:r1], r2
 * Indexed - 1 - r1, [Bank:r2]
 * Indexed - 2 - [Bank:r1]
 * Indexed - 3 - [Bank:r1], Const */
void addr_ind(Cpu *cpu, u8 mode);

/* Relative - 0 - (Offset)
 * Relative - 1 - (Offset), Const */
void addr_rel(Cpu *cpu, u8 mode);

/* Absolute - 0 - [Addr]
 * Absolute - 1 - [Addr], r1
 * Absolute - 2 - r1, [Addr]
 * Absolute - 3 - [Addr], Const */
void addr_abs(Cpu *cpu, u8 mode);

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

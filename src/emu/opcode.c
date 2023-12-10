#include "emu/opcode.h"

#include "common.h"

#include <stdlib.h>

/* clang-format off */
const Opcode op_table[OPCODE_COUNT] = {
	{ "NOP", op_nop, NULL, 0, 1 },     { "HLT", op_hlt, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },
	{ "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },
	{ "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },
	{ "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },
	{ "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },     { "RET", op_ret, NULL, 0, 4 },
	{ "RTI", op_rti, NULL, 0, 4 },     { "MOV", op_mov, addr_reg, 0, 3 }, { "AND", op_and, addr_reg, 0, 3 },
	{ "IOR", op_ior, addr_reg, 0, 3 }, { "XOR", op_xor, addr_reg, 0, 3 }, { "TST", op_tst, addr_reg, 0, 3 },
	{ "ADD", op_add, addr_reg, 0, 4 }, { "SUB", op_sub, addr_reg, 0, 4 }, { "SHL", op_shl, addr_reg, 0, 4 },
	{ "SHR", op_shr, addr_reg, 0, 4 }, { "ROL", op_rol, addr_reg, 0, 4 }, { "ROR", op_ror, addr_reg, 0, 4 },
	{ "CMP", op_cmp, addr_reg, 0, 4 }, { "MUL", op_mul, addr_reg, 0, 3 }, { "MLS", op_mls, addr_reg, 0, 6 },
	{ "DIV", op_div, addr_reg, 0, 6 }, { "DVS", op_dvs, addr_reg, 0, 6 }, { "???", op_xxx, addr_reg, 1, 2 },
	{ "???", op_xxx, addr_reg, 1, 2 }, { "INC", op_inc, addr_reg, 1, 2 }, { "DEC", op_dec, addr_reg, 1, 2 },
	{ "NOT", op_not, addr_reg, 1, 2 }, { "???", op_xxx, addr_reg, 1, 2 }, { "???", op_xxx, addr_reg, 1, 2 },
	{ "POP", op_pop, addr_reg, 1, 3 }, { "PSH", op_psh, addr_reg, 1, 3 }, { "???", op_xxx, addr_reg, 1, 2 },
	{ "???", op_xxx, addr_reg, 1, 2 }, { "???", op_xxx, addr_reg, 1, 2 }, { "???", op_xxx, addr_reg, 1, 2 },
	{ "???", op_xxx, addr_reg, 1, 2 }, { "???", op_xxx, addr_reg, 1, 2 }, { "???", op_xxx, addr_reg, 1, 2 },
	{ "MOV", op_mov, addr_imm, 0, 4 }, { "AND", op_and, addr_imm, 0, 4 }, { "IOR", op_ior, addr_imm, 0, 4 },
	{ "XOR", op_xor, addr_imm, 0, 4 }, { "TST", op_tst, addr_imm, 0, 4 }, { "ADD", op_add, addr_imm, 0, 5 },
	{ "SUB", op_sub, addr_imm, 0, 5 }, { "SHL", op_shl, addr_imm, 0, 5 }, { "SHR", op_shr, addr_imm, 0, 5 },
	{ "ROL", op_rol, addr_imm, 0, 5 }, { "ROR", op_ror, addr_imm, 0, 5 }, { "CMP", op_cmp, addr_imm, 0, 5 },
	{ "MUL", op_mul, addr_imm, 0, 7 }, { "MLS", op_mls, addr_imm, 0, 7 }, { "DIV", op_div, addr_imm, 0, 7 },
	{ "DVS", op_dvs, addr_imm, 0, 7 }, { "???", op_xxx, addr_imm, 1, 3 }, { "???", op_xxx, addr_imm, 1, 3 },
	{ "???", op_xxx, addr_imm, 1, 3 }, { "???", op_xxx, addr_imm, 1, 3 }, { "???", op_xxx, addr_imm, 1, 3 },
	{ "CLR", op_clr, addr_imm, 1, 3 }, { "SET", op_set, addr_imm, 1, 3 }, { "???", op_xxx, addr_imm, 1, 3 },
	{ "PSH", op_psh, addr_imm, 1, 4 }, { "???", op_xxx, addr_imm, 1, 3 }, { "???", op_xxx, addr_imm, 1, 3 },
	{ "???", op_xxx, addr_imm, 1, 3 }, { "???", op_xxx, addr_imm, 1, 3 }, { "???", op_xxx, addr_imm, 1, 3 },
	{ "???", op_xxx, addr_imm, 1, 3 }, { "???", op_xxx, addr_imm, 1, 3 }, { "MOV", op_mov, addr_ind, 0, 4 },
	{ "AND", op_and, addr_ind, 0, 4 }, { "IOR", op_ior, addr_ind, 0, 4 }, { "XOR", op_xor, addr_ind, 0, 4 },
	{ "TST", op_tst, addr_ind, 0, 4 }, { "ADD", op_add, addr_ind, 0, 5 }, { "SUB", op_sub, addr_ind, 0, 5 },
	{ "SHL", op_shl, addr_ind, 0, 5 }, { "SHR", op_shr, addr_ind, 0, 5 }, { "ROL", op_rol, addr_ind, 0, 5 },
	{ "ROR", op_ror, addr_ind, 0, 5 }, { "CMP", op_cmp, addr_ind, 0, 5 }, { "MUL", op_mul, addr_ind, 0, 7 },
	{ "MLS", op_mls, addr_ind, 0, 7 }, { "DIV", op_div, addr_ind, 0, 7 }, { "DVS", op_dvs, addr_ind, 0, 7 },
	{ "???", op_xxx, addr_abs, 0, 4 }, { "???", op_xxx, addr_abs, 0, 4 }, { "INC", op_inc, addr_abs, 0, 4 },
	{ "DEC", op_dec, addr_abs, 0, 4 }, { "NOT", op_not, addr_abs, 0, 4 }, { "???", op_xxx, addr_abs, 0, 4 },
	{ "???", op_xxx, addr_abs, 0, 4 }, { "POP", op_pop, addr_abs, 0, 5 }, { "PSH", op_psh, addr_abs, 0, 5 },
	{ "???", op_xxx, addr_abs, 0, 4 }, { "???", op_xxx, addr_abs, 0, 4 }, { "???", op_xxx, addr_abs, 0, 4 },
	{ "JMP", op_jmp, addr_abs, 0, 5 }, { "JSR", op_jsr, addr_abs, 0, 6 }, { "???", op_xxx, addr_abs, 0, 4 },
	{ "???", op_xxx, addr_abs, 0, 4 }, { "MOV", op_mov, addr_ind, 1, 4 }, { "AND", op_and, addr_ind, 1, 4 },
	{ "IOR", op_ior, addr_ind, 1, 4 }, { "XOR", op_xor, addr_ind, 1, 4 }, { "TST", op_tst, addr_ind, 1, 4 },
	{ "ADD", op_add, addr_ind, 1, 5 }, { "SUB", op_sub, addr_ind, 1, 5 }, { "SHL", op_shl, addr_ind, 1, 5 },
	{ "SHR", op_shr, addr_ind, 1, 5 }, { "ROL", op_rol, addr_ind, 1, 5 }, { "ROR", op_ror, addr_ind, 1, 5 },
	{ "CMP", op_cmp, addr_ind, 1, 5 }, { "MUL", op_mul, addr_ind, 1, 7 }, { "MLS", op_mls, addr_ind, 1, 7 },
	{ "DIV", op_div, addr_ind, 1, 7 }, { "DVS", op_dvs, addr_ind, 1, 7 }, { "???", op_xxx, addr_ind, 2, 4 },
	{ "???", op_xxx, addr_ind, 2, 4 }, { "INC", op_inc, addr_ind, 2, 4 }, { "DEC", op_dec, addr_ind, 2, 4 },
	{ "NOT", op_not, addr_ind, 2, 4 }, { "???", op_xxx, addr_ind, 2, 4 }, { "???", op_xxx, addr_ind, 2, 4 },
	{ "POP", op_pop, addr_ind, 2, 5 }, { "PSH", op_psh, addr_ind, 2, 5 }, { "???", op_xxx, addr_ind, 2, 4 },
	{ "???", op_xxx, addr_ind, 2, 4 }, { "???", op_xxx, addr_ind, 2, 4 }, { "JMP", op_jmp, addr_ind, 2, 5 },
	{ "JSR", op_jsr, addr_ind, 2, 5 }, { "???", op_xxx, addr_ind, 2, 4 }, { "???", op_xxx, addr_ind, 2, 4 },
	{ "MOV", op_mov, addr_ind, 3, 5 }, { "AND", op_and, addr_ind, 3, 5 }, { "IOR", op_ior, addr_ind, 3, 5 },
	{ "XOR", op_xor, addr_ind, 3, 5 }, { "TST", op_tst, addr_ind, 3, 5 }, { "ADD", op_add, addr_ind, 3, 6 },
	{ "SUB", op_sub, addr_ind, 3, 6 }, { "SHL", op_shl, addr_ind, 3, 6 }, { "SHR", op_shr, addr_ind, 3, 6 },
	{ "ROL", op_rol, addr_ind, 3, 6 }, { "ROR", op_ror, addr_ind, 3, 6 }, { "CMP", op_cmp, addr_ind, 3, 6 },
	{ "MUL", op_mul, addr_ind, 3, 8 }, { "MLS", op_mls, addr_ind, 3, 8 }, { "DIV", op_div, addr_ind, 3, 8 },
	{ "DVS", op_dvs, addr_ind, 3, 8 }, { "???", op_xxx, addr_rel, 0, 3 }, { "???", op_xxx, addr_rel, 0, 3 },
	{ "???", op_xxx, addr_rel, 0, 3 }, { "???", op_xxx, addr_rel, 0, 3 }, { "???", op_xxx, addr_rel, 0, 3 },
	{ "???", op_xxx, addr_rel, 0, 3 }, { "???", op_xxx, addr_rel, 0, 3 }, { "???", op_xxx, addr_rel, 0, 3 },
	{ "???", op_xxx, addr_rel, 0, 3 }, { "???", op_xxx, addr_rel, 0, 3 }, { "???", op_xxx, addr_rel, 0, 3 },
	{ "BRA", op_bra, addr_rel, 0, 4 }, { "???", op_xxx, addr_rel, 0, 3 }, { "???", op_xxx, addr_rel, 0, 3 },
	{ "???", op_xxx, addr_rel, 0, 3 }, { "???", op_xxx, addr_rel, 0, 3 }, { "MOV", op_mov, addr_abs, 1, 5 },
	{ "AND", op_and, addr_abs, 1, 5 }, { "IOR", op_ior, addr_abs, 1, 5 }, { "XOR", op_xor, addr_abs, 1, 5 },
	{ "TST", op_tst, addr_abs, 1, 5 }, { "ADD", op_add, addr_abs, 1, 6 }, { "SUB", op_sub, addr_abs, 1, 6 },
	{ "SHL", op_shl, addr_abs, 1, 6 }, { "SHR", op_shr, addr_abs, 1, 6 }, { "ROL", op_rol, addr_abs, 1, 6 },
	{ "ROR", op_ror, addr_abs, 1, 6 }, { "CMP", op_cmp, addr_abs, 1, 6 }, { "MUL", op_mul, addr_abs, 1, 8 },
	{ "MLS", op_mls, addr_abs, 1, 8 }, { "DIV", op_div, addr_abs, 1, 8 }, { "DVS", op_dvs, addr_abs, 1, 8 },
	{ "???", op_xxx, addr_rel, 1, 5 }, { "???", op_xxx, addr_rel, 1, 5 }, { "???", op_xxx, addr_rel, 1, 5 },
	{ "???", op_xxx, addr_rel, 1, 5 }, { "???", op_xxx, addr_rel, 1, 5 }, { "???", op_xxx, addr_rel, 1, 5 },
	{ "???", op_xxx, addr_rel, 1, 5 }, { "???", op_xxx, addr_rel, 1, 5 }, { "???", op_xxx, addr_rel, 1, 5 },
	{ "BIF", op_bif, addr_rel, 1, 6 }, { "BNF", op_bnf, addr_rel, 1, 6 }, { "???", op_xxx, addr_rel, 1, 5 },
	{ "???", op_xxx, addr_rel, 1, 5 }, { "???", op_xxx, addr_rel, 1, 5 }, { "???", op_xxx, addr_rel, 1, 5 },
	{ "???", op_xxx, addr_rel, 1, 5 }, { "MOV", op_mov, addr_abs, 2, 5 }, { "AND", op_and, addr_abs, 2, 5 },
	{ "IOR", op_ior, addr_abs, 2, 5 }, { "XOR", op_xor, addr_abs, 2, 5 }, { "TST", op_tst, addr_abs, 2, 5 },
	{ "ADD", op_add, addr_abs, 2, 6 }, { "SUB", op_sub, addr_abs, 2, 6 }, { "SHL", op_shl, addr_abs, 2, 6 },
	{ "SHR", op_shr, addr_abs, 2, 6 }, { "ROL", op_rol, addr_abs, 2, 6 }, { "ROR", op_ror, addr_abs, 2, 6 },
	{ "CMP", op_cmp, addr_abs, 2, 6 }, { "MUL", op_mul, addr_abs, 2, 8 }, { "MLS", op_mls, addr_abs, 2, 8 },
	{ "DIV", op_div, addr_abs, 2, 8 }, { "DVS", op_dvs, addr_abs, 2, 8 }, { "NOP", op_nop, NULL, 0, 1 },
	{ "HLT", op_hlt, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },
	{ "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },
	{ "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },
	{ "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },     { "???", op_xxx, NULL, 0, 1 },
	{ "???", op_xxx, NULL, 0, 1 },     { "RET", op_ret, NULL, 0, 4 },     { "RTI", op_rti, NULL, 0, 4 },
	{ "MOV", op_mov, addr_abs, 3, 6 }, { "AND", op_and, addr_abs, 3, 6 }, { "IOR", op_ior, addr_abs, 3, 6 },
	{ "XOR", op_xor, addr_abs, 3, 6 }, { "TST", op_tst, addr_abs, 3, 6 }, { "ADD", op_add, addr_abs, 3, 7 },
	{ "SUB", op_sub, addr_abs, 3, 7 }, { "SHL", op_shl, addr_abs, 3, 7 }, { "SHR", op_shr, addr_abs, 3, 7 },
	{ "ROL", op_rol, addr_abs, 3, 7 }, { "ROR", op_ror, addr_abs, 3, 7 }, { "CMP", op_cmp, addr_abs, 3, 7 },
	{ "MUL", op_mul, addr_abs, 3, 9 }, { "MLS", op_mls, addr_abs, 3, 9 }, { "DIV", op_div, addr_abs, 3, 9 },
	{ "DVS", op_dvs, addr_abs, 3, 9 },
}; /* clang-format on */

static void set_signzero(Cpu *cpu, u32 data) {
	bit_set(&cpu->status, ST_ZERO, data == 0);
	bit_set(&cpu->status, ST_SIGN, data & 0x8000);
}

static void set_carry(Cpu *cpu, u32 data) {
	bit_set(&cpu->status, ST_CARRY, data > 0xffff);
}

static void set_overflow(Cpu *cpu, u32 data1, u32 data2, u32 result) {
	bool has_overflow = (data1 ^ result) & (data2 ^ result) & 0x8000 != 0;
	bit_set(&cpu->status, ST_OVERFLOW, has_overflow);
}

static u16 operand_read(Cpu *cpu) {
	if (cpu->operand.is_addr) {
		return ram_read16(cpu, cpu->operand.dest);
	}

	return cpu->regs[cpu->operand.dest];
}

static void operand_write(Cpu *cpu, u16 data) {
	if (cpu->operand.is_addr) {
		ram_write16(cpu, cpu->operand.dest, data);
	} else {
		cpu->regs[cpu->operand.dest] = data;
	}
}

void opcode_execute(Cpu *cpu) {
	Opcode current = op_table[cpu->current_opcode & 0x00ff];

	if (current.addr != NULL) {
		current.addr(cpu, current.addr_mode);
	}

	current.handler(cpu);

	cpu->cycles += current.cycles;
}

void addr_reg(Cpu *cpu, u8 mode) {
	if (mode == 0) { /* r1, r2 */
		cpu->operand.src = cpu->regs[bit_getn(cpu->current_opcode, 12, 0xf)];
	}

	cpu->operand.dest = bit_getn(cpu->current_opcode, 8, 0xf);
	cpu->operand.is_addr = false;
}

void addr_imm(Cpu *cpu, u8 mode) {
	cpu->operand.src = ram_read16(cpu, cpu->program_counter);
	cpu->program_counter += 2;

	if (mode == 0) { /* r1, Const */
		cpu->operand.dest = (cpu->current_opcode & 0x0f00) >> 8;
		cpu->operand.is_addr = false;
	}
}

void addr_ind(Cpu *cpu, u8 mode) {
	u8 dest = bit_getn(cpu->current_opcode, 8, 0xf);
	u8 src = bit_getn(cpu->current_opcode, 12, 0xf);

	u16 bank = ram_read16(cpu, cpu->program_counter);
	cpu->program_counter += 2;

	switch (mode) {
	case 0: /* [Bank:r1], r2 */
		cpu->operand.src = src;
		cpu->operand.dest = (bank << 16) | cpu->regs[dest];
		cpu->operand.is_addr = true;

		break;
	case 1: /* r1, [Bank:r2] */
		cpu->operand.src = ram_read16(cpu, (bank << 16) | cpu->regs[src]);
		cpu->operand.dest = dest;
		cpu->operand.is_addr = false;

		break;
	case 2: /* [Bank:r1] */
		cpu->operand.src = 0;
		cpu->operand.dest = (bank << 16) | cpu->regs[dest];
		cpu->operand.is_addr = true;

		break;
	case 3: /* [Bank:r1], Const */
		cpu->operand.src = ram_read16(cpu, cpu->program_counter);
		cpu->program_counter += 2;
		cpu->operand.dest = (bank << 16) | cpu->regs[dest];
		cpu->operand.is_addr = true;

		break;
	}
}

void addr_rel(Cpu *cpu, u8 mode) {
	cpu->operand.dest = ram_read16(cpu, cpu->program_counter);
	cpu->program_counter += 2;

	if (mode == 0) { /* (Offset), Const */
		cpu->operand.src = ram_read16(cpu, cpu->program_counter);
		cpu->program_counter += 2;
	}
}

void addr_abs(Cpu *cpu, u8 mode) {
	u32 addr = ram_read32(cpu, cpu->program_counter);
	cpu->program_counter += 4;

	switch (mode) {
	case 0: /* [Addr], r1 */
		cpu->operand.src = bit_getn(cpu->current_opcode, 8, 0xf);
		cpu->operand.dest = addr;
		cpu->operand.is_addr = true;

		break;
	case 1: /* r1, [Addr] */
		cpu->operand.src = ram_read16(cpu, addr);
		cpu->operand.dest = bit_getn(cpu->current_opcode, 12, 0xf);
		cpu->operand.is_addr = false;

		break;
	case 2: /* [Addr] */
		cpu->operand.src = 0;
		cpu->operand.dest = addr;
		cpu->operand.is_addr = true;

		break;
	case 3: /* [Addr], Const */
		cpu->operand.src = ram_read16(cpu, cpu->program_counter);
		cpu->program_counter += 2;
		cpu->operand.dest = addr;
		cpu->operand.is_addr = true;

		break;
	}
}

void op_add(Cpu *cpu) {
	u32 result = operand_read(cpu);
	result += cpu->operand.src + bit_get(cpu->status, ST_CARRY);

	set_signzero(cpu, result);
	set_carry(cpu, result);
	set_overflow(cpu, operand_read(cpu), cpu->operand.src, result);

	operand_write(cpu, result);
}

void op_and(Cpu *cpu) {
	u16 result = operand_read(cpu) & cpu->operand.src;
	operand_write(cpu, result);

	set_signzero(cpu, result);
}

void op_bif(Cpu *cpu) {
	if ((cpu->status & cpu->operand.src) == cpu->operand.src) {
		cpu->program_counter += (s16)cpu->operand.dest;
	}
}

void op_bnf(Cpu *cpu) {
	if ((cpu->status & cpu->operand.src) == 0x0) {
		cpu->program_counter += (s16)cpu->operand.dest;
	}
}

void op_bra(Cpu *cpu) {
	cpu->program_counter += (s16)cpu->operand.dest;
}

void op_clr(Cpu *cpu) {
	cpu->status &= ~cpu->operand.src;
}

void op_cmp(Cpu *cpu) {
	u16 dest = operand_read(cpu);

	bit_set(&cpu->status, ST_CARRY, dest >= cpu->operand.src);
	bit_set(&cpu->status, ST_ZERO, dest == cpu->operand.src);
	bit_set(&cpu->status, ST_SIGN, (dest - cpu->operand.src) & 0x8000);
}

void op_dec(Cpu *cpu) {
	u16 result = operand_read(cpu) - 1;
	operand_write(cpu, result);

	set_signzero(cpu, result);
}

void op_div(Cpu *cpu) {
	if (cpu->operand.src == 0) {
		stack_push(cpu, operand_read(cpu));
		operand_write(cpu, 0xffff);
		cpu_exception(cpu, VEC_DIVZERO);
		return;
	}

	div_t result = div(operand_read(cpu), cpu->operand.src);
	operand_write(cpu, result.quot);
	stack_push(cpu, result.rem);

	set_signzero(cpu, result.quot);
	bit_set(&cpu->status, ST_CARRY, false);
}

void op_dvs(Cpu *cpu) {
	/* NOTE: I think there's no difference between DIV and DVS.
	 * Maybe this instruction is Useless. */
	op_div(cpu);
}

void op_hlt(Cpu *cpu) {
	cpu->is_halt = true;
}

void op_inc(Cpu *cpu) {
	u16 result = operand_read(cpu) + 1;
	operand_write(cpu, result);

	set_signzero(cpu, result);
}

void op_ior(Cpu *cpu) {
	u16 result = operand_read(cpu) | cpu->operand.src;
	operand_write(cpu, result);

	set_signzero(cpu, result);
}

void op_jmp(Cpu *cpu) {
	cpu->program_counter = cpu->operand.dest;
}

void op_jsr(Cpu *cpu) {
	stack_push(cpu, cpu->program_counter);
	cpu->program_counter = cpu->operand.dest;
}

void op_mls(Cpu *cpu) {
	/* NOTE: I think there's no difference between MUL and MLS.
	 * Maybe this instruction is Useless. */
	op_mul(cpu);
}

void op_mov(Cpu *cpu) {
	operand_write(cpu, cpu->operand.src);

	set_signzero(cpu, cpu->operand.src);
}

void op_mul(Cpu *cpu) {
	u32 result = operand_read(cpu) * cpu->operand.src;

	set_signzero(cpu, result);
	set_carry(cpu, result);
	set_overflow(cpu, operand_read(cpu), cpu->operand.src, result);

	operand_write(cpu, result & 0xffff);
	if (bit_get(cpu->status, ST_CARRY)) {
		stack_push(cpu, result >> 16);
	}
}

void op_nop(Cpu *cpu) {
	(void)cpu;
	/* Do literally Nothing :) */
}

void op_not(Cpu *cpu) {
	u16 result = ~operand_read(cpu);
	operand_write(cpu, result);

	set_signzero(cpu, result);
}

void op_pop(Cpu *cpu) {
	u16 data = stack_pop(cpu);
	operand_write(cpu, data);

	set_signzero(cpu, data);
}

void op_psh(Cpu *cpu) {
	u16 data = operand_read(cpu);
	stack_push(cpu, data);

	set_signzero(cpu, data);
}

void op_ret(Cpu *cpu) {
	(void)cpu;
}

void op_rol(Cpu *cpu) {
	(void)cpu;
}

void op_ror(Cpu *cpu) {
	(void)cpu;
}

void op_rti(Cpu *cpu) {
	(void)cpu;
}

void op_set(Cpu *cpu) {
	(void)cpu;
}

void op_shl(Cpu *cpu) {
	(void)cpu;
}

void op_shr(Cpu *cpu) {
	(void)cpu;
}

void op_sub(Cpu *cpu) {
	(void)cpu;
}

void op_tst(Cpu *cpu) {
	(void)cpu;
}

void op_xor(Cpu *cpu) {
	(void)cpu;
}

void op_xxx(Cpu *cpu) {
	cpu_exception(cpu, VEC_INSTR);
}

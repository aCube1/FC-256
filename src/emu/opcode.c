#include "emu/opcode.h"

#include "common.h"
#include "log.h"

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

static inline void set_signzero(Cpu *cpu, u32 data) {
	bit_set(&cpu->status, ST_ZERO, data == 0);
	bit_set(&cpu->status, ST_SIGN, data & 0x8000);
}

static inline void set_carry(Cpu *cpu, u32 data) {
	bit_set(&cpu->status, ST_CARRY, data > 0xffff);
}

static inline void set_overflow(Cpu *cpu, u32 data1, u32 data2, u32 result) {
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
	if (current.handler == NULL) {
		log_fatal("Opcode '%#x' doesn't have a handler!", cpu->current_opcode);
		exit(EXIT_FAILURE);
	}

	current.addr(cpu, current.addr_mode);
	current.handler(cpu);

	cpu->cycles += current.cycles;
}

void addr_reg(Cpu *cpu, u8 mode) {
	if (mode == 0) { /* r1, r2 */
		cpu->operand.src = cpu->current_opcode & 0xf000;
	}

	cpu->operand.dest = cpu->current_opcode & 0x0f00;
	cpu->operand.is_addr = false;
}

void addr_imm(Cpu *cpu, u8 mode) {
	cpu->operand.src = ram_read16(cpu, cpu->program_counter);
	cpu->program_counter += 2;

	if (mode == 0) { /* r1, Const */
		cpu->operand.dest = cpu->current_opcode & 0x0f00;
		cpu->operand.is_addr = false;
	}
}

void addr_ind(Cpu *cpu, u8 mode) {
	u8 dest = cpu->current_opcode & 0x0f00;
	u8 src = cpu->current_opcode & 0xf000;

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
	cpu->operand.offset = ram_read16(cpu, cpu->program_counter);
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
		cpu->operand.src = cpu->current_opcode & 0x0f00;
		cpu->operand.dest = addr;
		cpu->operand.is_addr = true;

		break;
	case 1: /* r1, [Addr] */
		cpu->operand.src = ram_read16(cpu, addr);
		cpu->operand.dest = cpu->current_opcode & 0x0f00;
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

	operand_write(cpu, result);

	set_signzero(cpu, result);
	set_carry(cpu, result);
	set_overflow(cpu, cpu->operand.dest, cpu->operand.src, result);
}

void op_and(Cpu *cpu) {
	u16 result = operand_read(cpu) & cpu->operand.src;
	operand_write(cpu, result);

	set_signzero(cpu, result);
}

void op_bif(Cpu *cpu) {
	if ((cpu->status & cpu->operand.src) == cpu->operand.src) {
		cpu->program_counter += cpu->operand.offset;
	}
}

void op_bnf(Cpu *cpu) {
	if ((cpu->status & cpu->operand.src) == 0x0) {
		cpu->program_counter += cpu->operand.offset;
	}
}

void op_bra(Cpu *cpu) {
	cpu->program_counter += cpu->operand.offset;
}

void op_clr(Cpu *cpu) {
	cpu->status |= cpu->operand.src;
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
	(void)cpu;
}

void op_dvs(Cpu *cpu) {
	(void)cpu;
}

void op_hlt(Cpu *cpu) {
	(void)cpu;
}

void op_inc(Cpu *cpu) {
	(void)cpu;
}

void op_ior(Cpu *cpu) {
	(void)cpu;
}

void op_jmp(Cpu *cpu) {
	(void)cpu;
}

void op_jsr(Cpu *cpu) {
	(void)cpu;
}

void op_mls(Cpu *cpu) {
	(void)cpu;
}

void op_mov(Cpu *cpu) {
	(void)cpu;
}

void op_mul(Cpu *cpu) {
	(void)cpu;
}

void op_nop(Cpu *cpu) {
	(void)cpu;
}

void op_not(Cpu *cpu) {
	(void)cpu;
}

void op_pop(Cpu *cpu) {
	(void)cpu;
}

void op_psh(Cpu *cpu) {
	(void)cpu;
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

#include "emu/opcode.h"

#include "log/log.h"

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
};

void opcode_execute(Cpu *cpu) {
	Opcode current = op_table[cpu->current_opcode & 0x00ff];
	if (current.handler == NULL) {
		log_fatal("Opcode '%#x' doesn't have a handler!", cpu->current_opcode);
		exit(EXIT_FAILURE);
	}

	current.addr(cpu, current.addr_mode);

	/* TODO: Execute instruction handler */

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
	u16 offset = ram_read16(cpu, cpu->program_counter);
	cpu->program_counter += 2;

	if (mode == 0) { /* (Offset), Const */
		cpu->operand.src = ram_read16(cpu, cpu->program_counter);
		cpu->program_counter += 2;
	}

	cpu->operand.dest = offset;
	cpu->operand.is_addr = false;
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

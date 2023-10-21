#include "cpu.h"
#include "opcodes.h"
#include "operand.h"

static void MOV(CPU *cpu);

// static void ADD(CPU *cpu);
// static void SUB(CPU *cpu);
// static void ADC(CPU *cpu);
// static void SBC(CPU *cpu);
// static void MUL(CPU *cpu);
// static void DIV(CPU *cpu);
// static void INC(CPU *cpu);
// static void DEC(CPU *cpu);

// static void REL(CPU *cpu, u8 mode, u16 first_reg, u16 second_reg) {
// 	(void)mode;
// 	(void)first_reg;
// 	(void)second_reg;
//
// 	cpu->op1 = (Operand) {
// 		.type = OT_OFFSET,
// 		.offset = cpuMemRead16(cpu, cpu->regs[REG_PC]),
// 	};
//
// 	cpu->actual_pc += 2;
// }

static void IMM(CPU *cpu, u8 mode, u16 first_reg, u16 second_reg) {
	(void)mode;
	(void)second_reg;

	cpu->op1 = (Operand) {
		.type = OT_REGISTER,
		.reg = first_reg,
	};
	cpu->op2 = (Operand) {
		.type = OT_CONSTANT,
		.constant = cpuMemRead16(cpu, cpu->actual_pc),
	};

	cpu->actual_pc += 2;
}

static void REG(CPU *cpu, u8 mode, u16 first_reg, u16 second_reg) {
	switch (mode) {
	case ADDR_REG_1:
		cpu->op1 = (Operand) {
			.type = OT_REGISTER,
			.reg = first_reg,
		};
		break;
	case ADDR_REG_2:
		cpu->op1 = (Operand) {
			.type = OT_REGISTER,
			.reg = first_reg,
		};
		cpu->op2 = (Operand) {
			.type = OT_REGISTER,
			.reg = second_reg,
		};
	default:
		break;
	}
}

static void ABS(CPU *cpu, u8 mode, u16 first_reg, u16 second_reg) {
	(void)second_reg;

	switch (mode) {
	case ADDR_ABS_1:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpuMemRead24(cpu, cpu->actual_pc),
		};
		break;
	case ADDR_ABS_2:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpuMemRead24(cpu, cpu->actual_pc),
		};
		cpu->op2 = (Operand) {
			.type = OT_CONSTANT,
			.constant = cpuMemRead16(cpu, cpu->actual_pc + 3),
		};
		break;
	case ADDR_ABS_3:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpuMemRead24(cpu, cpu->actual_pc),
		};
		cpu->op2 = (Operand) {
			.type = OT_REGISTER,
			.reg = first_reg,
		};
		break;
	case ADDR_ABS_4:
		cpu->op1 = (Operand) {
			.type = OT_REGISTER,
			.reg = first_reg,
		};
		cpu->op2 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpuMemRead24(cpu, cpu->actual_pc),
		};
		break;
	default:
		return;
	}

	cpu->data_bank = cpuMemRead(cpu, cpu->actual_pc);

	if (mode == ADDR_ABS_2) {
		cpu->actual_pc += 5; /* Addr = 3, Const = 2 */
	} else {
		cpu->actual_pc += 3;
	}
}

static void IND(CPU *cpu, u8 mode, u16 first_reg, u16 second_reg) {
	switch (mode) {
	case ADDR_IND_1:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpu->regs[first_reg],
		};
		break;
	case ADDR_IND_2:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpu->regs[first_reg],
		};
		cpu->op2 = (Operand) {
			.type = OT_CONSTANT,
			.constant = cpuMemRead16(cpu, cpu->actual_pc),
		};
		break;
	case ADDR_IND_3:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpu->regs[first_reg],
		};
		cpu->op2 = (Operand) {
			.type = OT_REGISTER,
			.reg = second_reg,
		};
		break;
	case ADDR_IND_4:
		cpu->op1 = (Operand) {
			.type = OT_REGISTER,
			.reg = first_reg,
		};
		cpu->op2 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpu->regs[second_reg],
		};
		break;
	default:
		return;
	}

	if (mode == ADDR_IND_2) {
		cpu->actual_pc += 2; /* Const = 2 */
	} else {
		cpu->actual_pc += 1;
	}
}

static void IDX(CPU *cpu, u8 mode, u16 first_reg, u16 second_reg) {
	u16 constant = cpuMemRead16(cpu, cpu->actual_pc);

	switch (mode) {
	case ADDR_IDX_1:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpu->regs[first_reg] + constant,
		};
		break;
	case ADDR_IDX_2:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpu->regs[first_reg] + constant,
		};
		cpu->op2 = (Operand) {
			.type = OT_REGISTER,
			.reg = second_reg,
		};
		break;
	case ADDR_IDX_3:
		cpu->op1 = (Operand) {
			.type = OT_REGISTER,
			.reg = first_reg,
		};
		cpu->op2 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpu->regs[second_reg] + constant,
		};
		break;
	default:
		return;
	}

	cpu->actual_pc += 2;
}

const Opcode op_table[MAX_OPCODES] = {
	[0x080] = { "MOV", ADDR_IMM, 3, MOV, IMM },   [0x100] = { "MOV", ADDR_REG_2, 3, MOV, REG },
	[0x180] = { "MOV", ADDR_ABS_2, 3, MOV, ABS }, [0x1c0] = { "MOV", ADDR_ABS_3, 3, MOV, ABS },
	[0x200] = { "MOV", ADDR_ABS_4, 3, MOV, ABS }, [0x280] = { "MOV", ADDR_IND_2, 4, MOV, IND },
	[0x2c0] = { "MOV", ADDR_IND_3, 4, MOV, IND }, [0x300] = { "MOV", ADDR_IND_4, 4, MOV, IND },
	[0x380] = { "MOV", ADDR_IDX_2, 5, MOV, IDX }, [0x3c0] = { "MOV", ADDR_IDX_3, 5, MOV, IDX },
};

int opcode_execute(CPU *cpu, u16 opcode) {
	Opcode current = op_table[opcode & 0x3ff]; /* Ignore register selector */
	if (!current.handler) {
		log_warn("Instruction code %#x doesn't have a handler!", opcode);
		return -1;
	}

	if (current.addr != NULL) {
		u8 selector = opcode >> 10;              /* 0bxxxxxx---------- */
		u16 first_reg = selector & 0x07;         /* 0b-----xxx */
		u16 second_reg = (selector >> 3) & 0x07; /* 0b--xxx--- */

		current.addr(cpu, current.mode, first_reg, second_reg);
	}

	current.handler(cpu);
	cpu->cycles += current.cycles;
	return 0;
}

static void MOV(CPU *cpu) {
	u16 data = operandGetData(cpu, &cpu->op2);

	switch (cpu->op1.type) {
	case OT_REGISTER:
		cpu->regs[cpu->op1.reg] = data;
		break;
	case OT_ADDRESS:
		cpuMemWrite16(cpu, cpu->op1.addr, data);
		break;
	default:
		break;
	}
}

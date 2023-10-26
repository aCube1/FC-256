#include "emu/opcode.h"

#include "emu/operand.h"

AddrHandler opcode_addresses[ADDR_COUNT] = {
	NULL,    addrREL, addrIMM, addrREG, addrREG, addrABS, addrABS, addrABS,
	addrABS, addrBNK, addrBNK, addrBNK, addrBNK, addrIDX, addrIDX, addrIDX,
};

OpcodeHandler opcode_handlers[OPCODE_COUNT] = {
	opcodeMOV,
	opcodeADD,
};

u8 addrREL(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg) {
	(void)addr_mode;
	(void)first_reg;
	(void)second_reg;

	cpu->op1 = (Operand) {
		.type = OT_OFFSET,
		.offset = cpuMemRead16(cpu, cpu->regs[REG_PC]),
	};

	cpu->actual_pc += 2;
	cpu->regs[REG_PC] = cpu->actual_pc & 0xffff;

	return 1;
}

u8 addrIMM(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg) {
	(void)addr_mode;
	(void)second_reg;

	cpu->op1 = (Operand) {
		.type = OT_REGISTER,
		.reg = first_reg,
	};
	cpu->op2 = (Operand) {
		.type = OT_CONSTANT,
		.constant = cpuMemRead16(cpu, cpu->actual_pc),
	};

	cpu->actual_pc += 2; /* Const: 2 Bytes */
	cpu->regs[REG_PC] = cpu->actual_pc & 0xffff;

	return 2;
}

u8 addrREG(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg) {
	switch (addr_mode) {
	case ADDR_REG_1:
		cpu->op1 = (Operand) {
			.type = OT_REGISTER,
			.reg = first_reg,
		};
		return 1;
	case ADDR_REG_2:
		cpu->op1 = (Operand) {
			.type = OT_REGISTER,
			.reg = first_reg,
		};
		cpu->op2 = (Operand) {
			.type = OT_REGISTER,
			.reg = second_reg,
		};
		return 2;
	default:
		break;
	}

	return 0;
}

u8 addrABS(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg) {
	(void)second_reg;
	u8 cycles = 0;

	switch (addr_mode) {
	case ADDR_ABS_1:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = cpuMemRead24(cpu, cpu->actual_pc),
		};
		cycles = 1;
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
		cycles = 2;
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
		cycles = 2;
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
		cycles = 2;
		break;
	default:
		return 0;
	}

	if (addr_mode == ADDR_ABS_2) {
		cpu->actual_pc += 5; /* Addr: 3 Bytes + Const: 2 Bytes */
	} else {
		cpu->actual_pc += 3; /* Addr: 3 Bytes */
	}
	cpu->regs[REG_PC] = cpu->actual_pc & 0xffff;

	return cycles;
}

u8 addrBNK(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg) {
	u8 cycles = 0;
	u8 bank = cpuMemRead(cpu, cpu->actual_pc);

	switch (addr_mode) {
	case ADDR_BNK_1:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = (bank << 16) | cpu->regs[first_reg],
		};
		cycles = 2;
		break;
	case ADDR_BNK_2:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = (bank << 16) | cpu->regs[first_reg],
		};
		cpu->op2 = (Operand) {
			.type = OT_CONSTANT,
			.constant = cpuMemRead16(cpu, cpu->actual_pc + 1),
		};
		cycles = 3;
		break;
	case ADDR_BNK_3:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = (bank << 16) | cpu->regs[first_reg],
		};
		cpu->op2 = (Operand) {
			.type = OT_REGISTER,
			.reg = second_reg,
		};
		cycles = 3;
		break;
	case ADDR_BNK_4:
		cpu->op1 = (Operand) {
			.type = OT_REGISTER,
			.reg = first_reg,
		};
		cpu->op2 = (Operand) {
			.type = OT_ADDRESS,
			.addr = (bank << 16) | cpu->regs[second_reg],
		};
		cycles = 3;
		break;
	default:
		return 0;
	}

	if (addr_mode == ADDR_BNK_2) {
		cpu->actual_pc += 3; /* Bank = 1, Const = 2 */
	} else {
		cpu->actual_pc += 1; /* Bank = 1 */
	}
	cpu->regs[REG_PC] = cpu->actual_pc & 0xffff;

	return cycles;
}

u8 addrIDX(CPU *cpu, u8 addr_mode, u8 first_reg, u8 second_reg) {
	u8 cycles = 0;
	u16 addr = cpuMemRead16(cpu, cpu->actual_pc);

	switch (addr_mode) {
	case ADDR_IDX_1:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = addr + cpu->regs[first_reg],
		};
		cycles = 3;
		break;
	case ADDR_IDX_2:
		cpu->op1 = (Operand) {
			.type = OT_ADDRESS,
			.addr = addr + cpu->regs[first_reg],
		};
		cpu->op2 = (Operand) {
			.type = OT_REGISTER,
			.reg = second_reg,
		};
		cycles = 4;
		break;
	case ADDR_IDX_3:
		cpu->op1 = (Operand) {
			.type = OT_REGISTER,
			.reg = first_reg,
		};
		cpu->op2 = (Operand) {
			.type = OT_ADDRESS,
			.addr = addr + cpu->regs[second_reg],
		};
		cycles = 4;
		break;
	default:
		return 0;
	}

	cpu->actual_pc += 2; /* Addr: 2 Bytes */
	cpu->regs[REG_PC] = cpu->actual_pc & 0xffff;

	return cycles;
}

u8 opcodeMOV(CPU *cpu) {
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

	return 1;
}

u8 opcodeADD(CPU *cpu) {
	u16 data = operandGetData(cpu, &cpu->op2);

	switch (cpu->op1.type) {
	case OT_REGISTER:
		cpu->regs[cpu->op1.reg] += data;
		break;
	case OT_OFFSET:
		cpuMemWrite16(cpu, cpu->op1.addr, data);
		break;
	default:
		break;
	}

	return 2;
}

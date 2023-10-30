#include "emu/operand.h"

#include "emu/cpu.h"

u16 operandUnwrap(CPU *cpu, Operand *op) {
	switch (op->type) {
	case OT_REGISTER:
		return cpu->regs[op->reg];
	case OT_CONSTANT:
		return op->constant;
	case OT_ADDRESS:
		return cpuMemRead16(cpu, op->addr);
	case OT_OFFSET:
		return op->offset;
	default:
		log_error("Operand type %d is Unknown!", op->type);
		return 0x00;
	}
}

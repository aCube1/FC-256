#ifndef _EMU_OPERAND_H_
#define _EMU_OPERAND_H_

#include "types.h"

typedef struct CPU CPU;

enum OperandType {
	OT_REGISTER,
	OT_CONSTANT,
	OT_ADDRESS,
	OT_OFFSET,
};

typedef struct {
	enum OperandType type;

	union {
		u8 reg;
		u16 constant;
		u32 addr;
		s16 offset;
	};
} Operand;

u16 operandGetData(CPU *cpu, Operand *op);

#endif /* _EMU_OPERAND_H_ */

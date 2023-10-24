#ifndef _OPERAND_H_
#define _OPERAND_H_

#include "types.h"

struct CPU;

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

u32 operandGetData(struct CPU *cpu, Operand *op);

#endif /* _OPERAND_H_ */

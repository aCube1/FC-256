#ifndef _OPERAND_H_
#define _OPERAND_H_

struct CPU;

enum OperandType {
	OT_REGISTER,
	OT_CONSTANT,
	OT_OFFSET,
	OT_ADDRESS,
};

typedef struct {
	enum OperandType type;

	union {
		u8 reg;
		u16 constant;
		u16 offset;
		u32 addr;
	};
} Operand;

u32 operandGetData(struct CPU *cpu, Operand *op);

#endif /* _OPERAND_H_ */

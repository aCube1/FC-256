#ifndef _ASM_PARSER_H_
#define _ASM_PARSER_H_

#include "asm/token.h"

#include <stdlib.h>

typedef struct ParserState {
	FILE *file;

	size_t line;
	size_t collum;
} ParserState;

#endif /* _ASM_PARSER_H_ */

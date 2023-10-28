#ifndef _ASM_LEX_H_
#define _ASM_LEX_H_

#include "asm/token.h"
#include "common.h"

typedef struct Lexer {
	StreamFile *stream;
	size_t index; /* Current stream index */

	TokenList tokens;

	size_t line;
	size_t col;
} Lexer;

void lexInit(Lexer *lex, StreamFile *stream);
void lexQuit(Lexer *lex);

int lexScan(Lexer *lex);

#endif /* _ASM_LEX_H_ */

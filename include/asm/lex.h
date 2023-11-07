#ifndef _ASM_LEX_H_
#define _ASM_LEX_H_

#include "asm/token.h"

#define CHAR_EOF '\0'

typedef struct Lexer {
	FILE *in;
	char *buf;
	usize bufsize;
	usize buflen;
	char stack[2];

	Location location;
} Lexer;

void lexInit(Lexer *lex, FILE *in, usize fileid);
void lexQuit(Lexer *lex);
TokenType lexScan(Lexer *lex, Token *out);

#endif /* _ASM_LEX_H_ */

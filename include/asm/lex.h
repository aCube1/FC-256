#ifndef _ASM_LEX_H_
#define _ASM_LEX_H_

#include "asm/token.h"

#include <stdio.h>

#define CHAR_EOF '\0'

typedef struct Lexer {
	FILE *in;
	char *buf;
	usize bufsize;
	usize buflen;
	char stack[2];

	Location location;
} Lexer;

void lex_init(Lexer *lex, FILE *in, usize fileid);
void lex_quit(Lexer *lex);
TokenType lex_scan(Lexer *lex, Token *out);

#endif /* _ASM_LEX_H_ */

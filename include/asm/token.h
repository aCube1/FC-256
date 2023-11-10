#ifndef _ASM_TOKEN_H_
#define _ASM_TOKEN_H_

#include "types.h"

typedef enum TokenType {
	/* Keywords */
	TOK_ADD,
	TOK_DEC,
	TOK_DIV,
	TOK_INC,
	TOK_MOV,
	TOK_MUL,
	TOK_PC,
	TOK_RA,
	TOK_RB,
	TOK_RC,
	TOK_RX,
	TOK_RY,
	TOK_RZ,
	TOK_SP,
	TOK_SUB,
	TOK_LAST_KEYWORD = TOK_SUB,

	/* Symbols */
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_COMMA,
	TOK_DOLLAR,
	TOK_COLON,
	TOK_PLUS,
	TOK_MINUS,
	TOK_LAST_SYMBOL = TOK_MINUS,

	/* Data */
	TOK_LITERAL,

	/* Magic */
	TOK_EOF,
	TOK_NONE,
} TokenType;

typedef struct Location {
	usize fileid;
	usize lineno;
	usize colno;
} Location;

typedef struct Token {
	TokenType type;
	Location location;

	union {
		u32 uval;
		s32 sval;
	};
} Token;

#endif /* _ASM_TOKEN_H_ */

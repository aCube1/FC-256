#ifndef _ASM_TOKEN_H_
#define _ASM_TOKEN_H_

#include "types.h"

/* clang-format off */
typedef enum TokenType {
	TOK_NONE, /* Just for error verifying */

	/* Symbols */
	TOK_LEFT_PAREN, TOK_RIGHT_PAREN,
	TOK_COMMA, TOK_DOLLAR, TOK_COLON,
	TOK_PLUS, TOK_MINUS,

	/* Keywords */
	TOK_MOV, TOK_ADD, TOK_SUB, TOK_ADC, TOK_SBC,
	TOK_MUL, TOK_DIV, TOK_INC, TOK_DEC,
	TOK_RA, TOK_RB, TOK_RC,
	TOK_RX, TOK_RY, TOK_RZ,

	/* Literals */
	TOK_BYTE, TOK_WORD,

	/* End-of-file */
	TOK_EOF,
} TokenType;

/* clang-format on */

typedef struct Token {
	TokenType type;
	char *start;
	size_t lenght;
} Token;

typedef struct TokenList {
	Token *data;

	/* Internal Private Data */
	size_t used;
	size_t size;
} TokenList;

void tokenlistCreate(TokenList *list, size_t size);
void tokenlistFree(TokenList *list);

void tokenlistInsert(TokenList *list, Token element);

#endif /* _ASM_TOKEN_H_ */

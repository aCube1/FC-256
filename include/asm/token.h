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
	TOK_CONSTANT,

	/* End-of-file */
	TOK_EOF,
} TokenType;

/* clang-format on */

typedef struct Token {
	TokenType type;
	char *start;
	usize lenght;
} Token;

typedef struct TokenList {
	Token *data;

	/* Internal Private Data */
	usize used;
	usize size;
} TokenList;

/*!
 * Initialize TokenList struct memory.
 *
 * @param list Reference to the TokenList struct.
 * @param size Initial size to the list.
 */
void tokenlistCreate(TokenList *list, usize size);
void tokenlistFree(TokenList *list);

/*!
 * Insert Token element into the list.
 *
 * @param list    Reference to the TokenList struct.
 * @param element Token to insert.
 */
void tokenlistInsert(TokenList *list, Token element);

#endif /* _ASM_TOKEN_H_ */

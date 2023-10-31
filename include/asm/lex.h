#ifndef _ASM_LEX_H_
#define _ASM_LEX_H_

#include "asm/token.h"
#include "common.h"

typedef struct Lexer {
	StreamFile *stream;
	usize index; /* Current stream index */

	TokenList tokens;

	usize line;
	usize col;
} Lexer;

/*!
 * Initialize Lexer struct memory.
 *
 * @param lex    Reference to Lexer struct to initialize.
 * @param stream File stream with the assembly program.
 */
void lexInit(Lexer *lex, StreamFile *stream);
void lexQuit(Lexer *lex);

/*!
 * Scans through the stream file searching for tokens.
 *
 * When a token is found, the lexer will store it at tokens member of the Lexer
 * struct. If a invalid token is found, the Scanner will show a error message
 * and return 0.
 *
 * @param lex Reference to Lexer struct.
 *
 * @return 0 on error, 1 otherwise.
 */
int lexScan(Lexer *lex);

#endif /* _ASM_LEX_H_ */

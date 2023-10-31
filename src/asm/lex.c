#include "asm/lex.h"

#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGHT 1024 + 1

typedef struct KeywordToken {
	char *keyword;
	TokenType type;
} KeywordToken;

typedef struct SingleSymbolToken {
	char symbol;
	TokenType type;
} SingleSymbolToken;

static const KeywordToken s_keywords[] = {
	{ "mov", TOK_MOV }, { "add", TOK_ADD }, { "sub", TOK_SUB }, { "adc", TOK_ADC }, { "sbc", TOK_SBC },
	{ "div", TOK_DIV }, { "inc", TOK_INC }, { "dec", TOK_DEC }, { "ra", TOK_RA },   { "rb", TOK_RB },
	{ "rc", TOK_RC },   { "rx", TOK_RX },   { "ry", TOK_RY },   { "rz", TOK_RZ },   { "\0", TOK_NONE },
};

static const SingleSymbolToken s_single_symbols[] = {
	{ '(', TOK_LEFT_PAREN }, { ')', TOK_RIGHT_PAREN }, { ',', TOK_COMMA }, { '$', TOK_DOLLAR },
	{ ':', TOK_COLON },      { '+', TOK_PLUS },        { '-', TOK_MINUS }, { '\0', TOK_NONE },
};

/* Return true if is a space or tab */
// static inline bool isSpace(char c) {
// 	return c == ' ' || c == '\t';
// }

/* Return true if char is a Letter or a Underline. */
static inline bool isIdentifierInitChar(char c) {
	return isalpha(c) || c == '_';
}

/* Return true if char is a Letter, Underline or Number. */
static inline bool isIdentifierChar(char c) {
	return isIdentifierInitChar(c) || isdigit(c);
}

/* Get character in current + N without changing index */
static inline char peekn(Lexer *lex, usize n) {
	return lex->stream->data[lex->index + n];
}

/* Get index character without changing index */
static inline char peek(Lexer *lex) {
	return peekn(lex, 0);
}

/* Change index to the next character */
static void next(Lexer *lex) {
	if (peekn(lex, 0) == '\0') {
		return; /* Don't go past the Null Terminator */
	}

	lex->index += 1;
	lex->col += 1;
}

static int matchKeyword(Lexer *lex, char *start, usize lenght) {
	char keyword[MAX_IDENTIFIER_LENGHT] = { 0 };
	strncpy(keyword, start, lenght);

	/* Keywords are case insensitive, so we must set all characters to lowercase. */
	for (usize i = 0; i < lenght; i += 1) {
		keyword[i] = tolower(keyword[i]);
	}

	for (usize i = 0; s_keywords[i].type != TOK_NONE; i += 1) {
		if (strncmp(keyword, s_keywords[i].keyword, lenght) == 0) {
			Token token = {
				.type = s_keywords[i].type,
				.start = start,
				.lenght = lenght,
			};

			tokenlistInsert(&lex->tokens, token);
			return 1;
		}
	}

	return 0; /* Seems like it's not a valid keyword */
}

static int matchIdentifier(Lexer *lex) {
	char *start = lex->stream->data + lex->index;
	usize lenght = 0;
	usize start_col = lex->col;
	usize start_line = lex->line;

	/* Get identifier lenght. */
	while (isIdentifierChar(peek(lex))) {
		next(lex);
		lenght += 1;

		if (lenght > MAX_IDENTIFIER_LENGHT) {
			log_error("Identifier exceed 1024 characters lenght - %d: %d", start_line, start_col);
			return 0;
		}
	}

	if (matchKeyword(lex, start, lenght)) {
		return 1; /* The identifier is a keyword */
	}

	char identifier[MAX_IDENTIFIER_LENGHT] = { 0 };
	strncpy(identifier, start, lenght);
	log_error("Unknown identifier \"%s\" - %d:%d", identifier, start_line, start_col);
	return 0;
}

static int matchSymbol(Lexer *lex) {
	char c = peek(lex);

	for (usize i = 0; s_single_symbols[i].symbol != '\0'; i += 1) {
		if (c == s_single_symbols[i].symbol) {
			Token token = {
				.type = s_single_symbols[i].type,
				.start = lex->stream->data + lex->index,
				.lenght = 1,
			};

			tokenlistInsert(&lex->tokens, token);
			return 1;
		}
	}

	log_error("Unknown symbol %c - %d:%d", peek(lex), lex->line, lex->col);
	return 0;
}

void lexInit(Lexer *lex, StreamFile *stream) {
	tokenlistCreate(&lex->tokens, 2);
	if (lex->tokens.data == NULL) {
		log_error("Unable to initialize tokens list");
		return;
	}

	lex->stream = stream;
	lex->index = 0;
	lex->line = 1;
	lex->col = 1;
}

void lexQuit(Lexer *lex) {
	tokenlistFree(&lex->tokens);
}

int lexScan(Lexer *lex) {
	char c = peek(lex);

	while (c != '\0') {
		switch (c) {
		case '\n':
			lex->line += 1;
			lex->col = 0;
			break;
		case ' ':
		case '\t':
			break; /* Just ignore spaces or tabs */
		case ';':
			/* Consume comments */
			while (c != '\n' && c != '\0') {
				next(lex);
				c = peek(lex);
			}
			break;
		default:
			if (isIdentifierInitChar(c)) {
				matchIdentifier(lex);
			} else if (ispunct(c)) {
				matchSymbol(lex);
			} else {
				tokenlistFree(&lex->tokens);
				return 0;
			}

			break;
		}

		next(lex);
		c = peek(lex);
	}

	return 1;
}

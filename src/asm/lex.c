#include "asm/lex.h"

#include "common.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdnoreturn.h>
#include <string.h>

static const char *tokens[] = {
	/* Instructions */
	[TOK_ADD] = "add",
	[TOK_DEC] = "dec",
	[TOK_DIV] = "div",
	[TOK_INC] = "inc",
	[TOK_MOV] = "mov",
	[TOK_MUL] = "mul",
	[TOK_PC] = "pc",
	[TOK_RA] = "ra",
	[TOK_RB] = "rb",
	[TOK_RC] = "rc",
	[TOK_RX] = "rx",
	[TOK_RY] = "ry",
	[TOK_RZ] = "rz",
	[TOK_SP] = "sp",
	[TOK_SUB] = "sub",

	/* Symbols */
	[TOK_LPAREN] = "(",
	[TOK_RPAREN] = ")",
	[TOK_COMMA] = ",",
	[TOK_DOLLAR] = "$",
	[TOK_COLON] = ":",
	[TOK_PLUS] = "+",
	[TOK_MINUS] = "-",
};

static_assert(
	sizeof(tokens) / sizeof(const char *) == TOK_LAST_SYMBOL + 1,
	"Tokens array doesn't have the same size of Tokens Enum."
);

static inline bool isSpace(char c) {
	return c == '\t' || c == '\n' || c == ' ';
}

static noreturn void error(Location loc, const char *fmt, ...) {
	va_list args;

	/* NOLINTBEGIN(cert-err33-c) */
	fprintf(stderr, "%zd - %zd:%zd ", loc.fileid, loc.lineno, loc.colno);

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fprintf(stderr, "\n");
	/* NOLINTEND(cert-err33-c) */

	exit(EXIT_FAILURE);
}

static void appendBuffer(Lexer *lex, const char *buf, usize size) {
	if (lex->buflen + size >= lex->bufsize) {
		lex->bufsize *= 2;
		lex->buf = xrealloc(lex->buf, lex->bufsize);
	}

	memcpy(lex->buf + lex->buflen, buf, size);
	lex->buflen += size;
	lex->buf[lex->buflen] = '\0';
}

static void clearBuffer(Lexer *lex) {
	lex->buflen = 0;
	lex->buf[0] = 0;
}

static void pushStack(Lexer *lex, char c, bool buffer) {
	assert(lex->stack[1] == CHAR_EOF);

	lex->stack[1] = lex->stack[0];
	lex->stack[0] = c;

	if (buffer) {
		lex->buflen -= 1;
		lex->buf[lex->buflen] = '\0'; /* Consume character */
	}
}

static void updateLocation(Location *loc, char c) {
	if (c == '\n') {
		loc->lineno += 1;
		loc->colno = 0;
	} else if (c == '\t') {
		loc->colno += 8;
	} else {
		loc->colno += 1;
	}
}

static char next(Lexer *lex, Location *loc, bool buffer) {
	char c;

	if (lex->stack[0] != CHAR_EOF) {
		c = lex->stack[0];
		lex->stack[0] = lex->stack[1];
		lex->stack[1] = CHAR_EOF;
	} else {
		c = fgetc(lex->in);
		updateLocation(&lex->location, c);

		if (feof(lex->in)) {
			c = CHAR_EOF;
		}
	}

	if (loc != NULL) {
		*loc = lex->location;
		for (usize i = 0; i < 2 && lex->stack[i] != CHAR_EOF; i += 1) {
			updateLocation(&lex->location, lex->stack[i]);
		}
	}

	if (buffer) {
		appendBuffer(lex, &c, 1);
	}

	return c;
}

static char getCharacter(Lexer *lex, Location *loc) {
	char c = next(lex, loc, false);

	while (c != CHAR_EOF && isSpace(c)) {
		c = next(lex, loc, false);
	}

	return c;
}

static void literal(Lexer *lex, Token *out) {
	enum Bases {
		BIN,
		HEX,
		DEC,
	};

	static const char numbers[][24] = {
		[BIN] = "01",
		[DEC] = "0123456789",
		[HEX] = "0123456789abcdefABCDEF",
	};

	enum Bases state = DEC;
	u8 base = 10;
	char c = next(lex, &out->location, true);
	assert(c != CHAR_EOF && isdigit(c));

	if (c == '0') {
		c = next(lex, NULL, true);
		switch (c) {
		case 'b':
			state = BIN;
			base = 2;
			break;
		case 'x':
			state = HEX;
			base = 16;
			break;
		}
	}

	if (state != DEC) {
		c = next(lex, NULL, true);
	}

	while (strchr(numbers[state], c)) {
		c = next(lex, NULL, true);
	}

	out->type = TOK_LITERAL;

	errno = 0;
	out->uval = strtoumax(lex->buf + (base == 10 ? 0 : 2), NULL, base);
	if (errno == ERANGE) {
		error(out->location, "Integer constant overflow");
	}

	clearBuffer(lex);
}

static int keywordCompare(const void *v1, const void *v2) {

	return strcmp(*(const char **)v1, *(const char **)v2);
}

static TokenType keyword(Lexer *lex, Token *out) {
	char c = next(lex, &out->location, true);
	assert(c != CHAR_EOF && (isalpha(c) || c == '_'));

	while (c != CHAR_EOF) {
		if (!isalpha(c) && c != '_') {
			pushStack(lex, c, true);
			break;
		}
		c = next(lex, NULL, true);
	}

	/* Convert buffer to lowercase */
	char *buf = xstrndup(lex->buf, lex->buflen);
	strntolower(buf, lex->buflen);

	void *token = bsearch(&buf, tokens, TOK_LAST_KEYWORD + 1, sizeof(tokens[0]), keywordCompare);
	if (token == NULL) {
		error(out->location, "Unknown keyword %s", lex->buf);
	}

	out->type = (const char **)token - tokens;

	clearBuffer(lex);
	free(buf);
	return out->type;
}

static TokenType comment(Lexer *lex, Token *out) {
	char c = next(lex, NULL, false);

	while (c != CHAR_EOF && c != '\n') {
		c = next(lex, NULL, false);
	}

	return lexScan(lex, out);
}

void lexInit(Lexer *lex, FILE *in, usize fileid) {
	memset(lex, 0, sizeof(*lex));

	lex->in = in;
	lex->bufsize = 128;
	lex->buf = xcalloc(1, lex->bufsize);

	lex->stack[0] = CHAR_EOF;
	lex->stack[1] = CHAR_EOF;

	lex->location.fileid = fileid;
	lex->location.lineno = 1;
	lex->location.colno = 1;
}

void lexQuit(Lexer *lex) {
	fclose(lex->in); /* NOLINT(cert-err33-c) */
	free(lex->buf);
}

TokenType lexScan(Lexer *lex, Token *out) {
	char c = getCharacter(lex, &out->location);

	if (c == CHAR_EOF) {
		out->type = TOK_EOF;
		return out->type;
	}

	if (isdigit(c)) {
		pushStack(lex, c, false);
		literal(lex, out);
		return TOK_LITERAL;
	}

	if (isalpha(c) || c == '_') {
		pushStack(lex, c, false);
		return keyword(lex, out);
	}

	switch (c) {
	case '(':
		out->type = TOK_LPAREN;
		break;
	case ')':
		out->type = TOK_RPAREN;
		break;
	case ',':
		out->type = TOK_COMMA;
		break;
	case '$':
		out->type = TOK_DOLLAR;
		break;
	case ':':
		out->type = TOK_COLON;
		break;
	case '+':
		out->type = TOK_PLUS;
		break;
	case '-':
		out->type = TOK_MINUS;
		break;
	case ';':
		return comment(lex, out);
	default:
		/* NOLINTBEGIN(cert-err33-c) */
		fprintf(
			stderr, "%zd - %zd:%zd: Syntax Error: Unexpected character\n", lex->location.fileid, lex->location.lineno,
			lex->location.colno
		);
		/* NOLINTEND(cert-err33-c) */

		exit(EXIT_FAILURE);
	}

	return out->type;
}

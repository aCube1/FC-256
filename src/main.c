#include "asm/lex.h"
#include "log/log.h"

#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		log_info("Usage: %s <file.asm>", argv[0]);
		return EXIT_FAILURE;
	}

	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		log_fatal("Unable to load test assembly.");
		return EXIT_FAILURE;
	}

	Lexer lexer;
	lexInit(&lexer, file, 0);

	TokenType type = TOK_NONE;
	while (type != TOK_EOF) {
		Token token;

		type = lexScan(&lexer, &token);

		log_debug(
			"%s - %zd:%zd: %d -> %#x", argv[1], token.location.lineno, token.location.colno, token.type, token.uval
		);
		token.uval = 0;
	}

	lexQuit(&lexer);
	return EXIT_SUCCESS;
}

#include "asm/lex.h"
#include "common.h"
#include "log/log.h"

#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		log_info("Usage: %s <file.asm>", argv[0]);
		return EXIT_FAILURE;
	}

	StreamFile stream;
	if (!fileLoad(&stream, argv[1])) {
		log_fatal("Unable to load test assembly.");
		return EXIT_FAILURE;
	}

	Lexer lexer;
	lexInit(&lexer, &stream);

	if (!lexScan(&lexer)) {
		log_fatal("Cannot do lexing");
		fileClose(&stream);
		lexQuit(&lexer);
		return EXIT_FAILURE;
	}

	for (size_t i = 0; i < lexer.tokens.used; i += 1) {
		Token token = lexer.tokens.data[i];

		char *keyword = strndup(token.start, token.lenght);
		log_info("%s", keyword);
		free(keyword);
	}

	lexQuit(&lexer);
	fileClose(&stream);
	return EXIT_SUCCESS;
}

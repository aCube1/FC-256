#include "asm/token.h"

void tokenlistCreate(TokenList *list, usize size) {
	if (size <= 1) {
		list->data = NULL;
		log_error("data list size cannot be less than 2.");
		return;
	}

	list->data = calloc(size, sizeof(Token));
	if (list->data == NULL) {
		log_error("Cannot to allocate data list with size: %z", size);
		return;
	}

	list->used = 0;
	list->size = size;
}

void tokenlistFree(TokenList *list) {
	free(list->data);
	list->data = NULL;
	list->used = 0;
	list->size = 0;
}

void tokenlistInsert(TokenList *list, Token element) {
	if (list->data == NULL) {
		log_error("Tokens list is not valid.");
		return;
	}

	/* When the list reaches the limit, increase the size */
	if (list->used == list->size) {
		list->size *= 2;

		Token *tmp = realloc(list->data, list->size * sizeof(Token));
		if (tmp == NULL) {
			log_error("Cannot increase tokens list memory size.");
			return;
		}

		list->data = tmp;
	}

	list->data[list->used] = element;
	list->used += 1;
}

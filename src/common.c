#include "common.h"

#include "log/log.h"

#include <ctype.h>
#include <limits.h>
#include <string.h>

usize bitGetN(usize data, u8 pos, usize mask) {
	return (data >> pos) & mask;
}

usize bitSetN(usize data, u8 pos, usize mask, bool enable) {
	if (!enable) {
		return data & ~(mask << pos);
	}

	return data | (mask << pos);
}

usize bitGet(usize data, u8 pos) {
	return bitGetN(data, pos, 1);
}

usize bitSet(usize data, u8 pos, bool enable) {
	return bitSetN(data, pos, 1, enable);
}

void *xcalloc(size_t count, size_t size) {
	void *ptr = calloc(count, size);
	if (ptr == NULL && size != 0) {
		log_fatal("Unable to allocate memory!");
		exit(EXIT_FAILURE);
	}

	return ptr;
}

void *xrealloc(void *ptr, size_t size) {
	ptr = realloc(ptr, size);
	if (ptr == NULL && size != 0) {
		log_fatal("Unable to reallocate memory!");
		exit(EXIT_FAILURE);
	}

	return ptr;
}

void strntolower(char *str, usize len) {
	for (usize i = 0; i < len; i += 1) {
		str[i] = tolower(str[i]);
	}
}

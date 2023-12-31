#include "common.h"

#include "log.h"

usize bit_getn(usize data, u8 offset, usize mask) {
	return (data >> offset) & mask;
}

usize bit_setn(usize data, u8 offset, usize mask, bool enable) {
	if (!enable) {
		return data & ~(mask << offset);
	}

	return data | (mask << offset);
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

FILE *xfopen(const char *filename, const char *mode) {
	FILE *file = fopen(filename, mode);
	if (file == NULL) {
		log_fatal("Unable to open file: %s", filename);
		exit(EXIT_FAILURE);
	}

	return file;
}

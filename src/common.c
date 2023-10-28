#include "common.h"

#include "log/log.h"

usize bitsGet(usize data, u8 start, usize mask) {
	return (data >> start) & mask;
}

usize bitsSet(usize data, u8 start, usize mask) {
	return data | (mask << start);
}

usize bitsUnset(usize data, u8 start, usize mask) {
	return data & ~(mask << start);
}

int fileLoad(StreamFile *file, const char *path) {
	FILE *input = fopen(path, "r");
	if (input == NULL) {
		log_error("Unable to open file %s", path);

		file->data = NULL;
		return 0;
	}

	/* NOLINTBEGIN(cert-err33-c) */
	fseek(input, 0, SEEK_END);
	file->lenght = ftell(input);
	fseek(input, 0, SEEK_SET);

	file->data = calloc(file->lenght + 1, sizeof(char));
	fread(file->data, sizeof(char), file->lenght, input);
	fclose(input);
	/* NOLINTEND(cert-err33-c) */

	file->data[file->lenght] = '\0';
	return 1;
}

void fileClose(StreamFile *file) {
	free(file->data);
	file->data = NULL;
}

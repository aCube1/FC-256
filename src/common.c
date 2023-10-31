#include "common.h"

#include "log/log.h"

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
	return bitGetN(data, pos, 0x01);
}

usize bitSet(usize data, u8 pos, bool enable) {
	return bitSetN(data, pos, 0x01, enable);
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

#ifndef _COMMON_H_
#define _COMMON_H_

#include "types.h"

typedef struct StreamFile {
	char *data;
	size_t lenght;
} StreamFile;

usize bitsGet(usize data, u8 start, usize mask);
usize bitsSet(usize data, u8 start, usize mask);
usize bitsUnset(usize data, u8 start, usize mask);

int fileLoad(StreamFile *file, const char *path);
void fileClose(StreamFile *file);

#endif /* _COMMON_H_ */

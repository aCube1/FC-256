#ifndef _COMMON_H_
#define _COMMON_H_

#include "types.h"

#include <stdio.h>

#define bit_get(data, offset)         bit_getn((data), (offset), 0x1)
#define bit_set(data, offset, enable) *(data) = bit_setn(*(data), (offset), 0x1, (enable))

usize bit_getn(usize data, u8 offset, usize mask);
usize bit_setn(usize data, u8 offset, usize mask, bool enable);

void *xcalloc(usize count, usize size);
void *xrealloc(void *ptr, usize size);

FILE *xfopen(const char *filename, const char *mode);

#endif /* _COMMON_H_ */

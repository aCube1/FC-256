#ifndef _COMMON_H_
#define _COMMON_H_

#include "types.h"

usize bit_getn(usize data, u8 pos, usize mask);
usize bit_setn(usize data, u8 pos, usize mask, bool enable);

void *xcalloc(usize count, usize size);
void *xrealloc(void *ptr, usize size);

#endif /* _COMMON_H_ */

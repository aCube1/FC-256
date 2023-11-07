#ifndef _COMMON_H_
#define _COMMON_H_

#include "types.h"

usize bitGetN(usize data, u8 pos, usize mask);
usize bitSetN(usize data, u8 pos, usize mask, bool enable);

inline usize bitGet(usize data, u8 pos);
inline usize bitSet(usize data, u8 pos, bool enable);

void *xcalloc(size_t count, size_t size);
void *xrealloc(void *ptr, size_t size);

#endif /* _COMMON_H_ */

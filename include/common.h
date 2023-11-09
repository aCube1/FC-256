#ifndef _COMMON_H_
#define _COMMON_H_

#include "types.h"

usize bitGetN(usize data, u8 pos, usize mask);
usize bitSetN(usize data, u8 pos, usize mask, bool enable);

inline usize bitGet(usize data, u8 pos);
inline usize bitSet(usize data, u8 pos, bool enable);

void *xcalloc(usize count, usize size);
void *xrealloc(void *ptr, usize size);

#endif /* _COMMON_H_ */

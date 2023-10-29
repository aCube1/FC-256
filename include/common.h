#ifndef _COMMON_H_
#define _COMMON_H_

#include "types.h"

usize bitGetN(usize data, u8 pos, usize n);
usize bitSetN(usize data, u8 pos, usize n, bool enable);

inline usize bitGet(usize data, u8 pos);
inline usize bitSet(usize data, u8 pos, bool enable);

#endif /* _COMMON_H_ */

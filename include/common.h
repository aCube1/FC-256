#ifndef _COMMON_H_
#define _COMMON_H_

#include "types.h"

usize bitsGet(usize data, u8 start, usize mask);
usize bitsSet(usize data, u8 start, usize mask);
usize bitsUnset(usize data, u8 start, usize mask);

#endif /* _COMMON_H_ */

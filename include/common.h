#ifndef _COMMON_H_
#define _COMMON_H_

#include "types.h"

/*!
 * Get N bits.
 *
 * @param data Value to get bits of.
 * @param pos  Bits start position.
 * @param mask Bits count.
 *
 * @return Bits gotten.
 */
usize bitGetN(usize data, u8 pos, usize mask);

/*!
 * Set N bits.
 *
 * @param data   Value to set bits.
 * @param pos    Bits start position.
 * @param mask   Bits count.
 * @param enable Set or Unset given bits.
 *
 * @return Data copy with the set/unset bits
 */
usize bitSetN(usize data, u8 pos, usize mask, bool enable);

inline usize bitGet(usize data, u8 pos);
inline usize bitSet(usize data, u8 pos, bool enable);

#endif /* _COMMON_H_ */

#include "common.h"

usize bitGetN(usize data, u8 pos, usize n) {
	return (data >> pos) & n;
}

usize bitSetN(usize data, u8 pos, usize n, bool enable) {
	if (!enable) {
		return data & ~(n << pos);
	}

	return data | (n << pos);
}

usize bitGet(usize data, u8 pos) {
	return bitGetN(data, pos, 0x01);
}

usize bitSet(usize data, u8 pos, bool enable) {
	return bitSetN(data, pos, 0x01, enable);
}

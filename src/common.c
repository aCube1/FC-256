#include "common.h"

usize bitsGet(usize data, u8 start, usize mask) {
	return (data >> start) & mask;
}

usize bitsSet(usize data, u8 start, usize mask) {
	return data | (mask << start);
}

usize bitsUnset(usize data, u8 start, usize mask) {
	return data & ~(mask << start);
}

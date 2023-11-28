#include "emu/cpu.h"
#include "log/log.h"

#include <stdlib.h>

int main(void) {
	Cpu cpu;
	cpu_powerup(&cpu);
	ram_write16(&cpu, VECTOR_ADDR | VEC_STACK, 0x0000);
	ram_write16(&cpu, VECTOR_ADDR | VEC_STACK + 2, 0x0020);

	cpu_reset(&cpu);

	log_trace("%#x", cpu.stack_pointer);
	stack_push(&cpu, 0x4269);
	stack_push(&cpu, 0x6924);
	u16 data = stack_pop(&cpu);
	log_trace("%#x -> %#x", cpu.stack_pointer, data);
	data = stack_pop(&cpu);
	log_trace("%#x -> %#x", cpu.stack_pointer, data);

	cpu_shutdown(&cpu);
	return EXIT_SUCCESS;
}

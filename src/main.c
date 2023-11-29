#include "emu/cpu.h"
#include "log.h"

#include <stdlib.h>

#define DEBUG_BUF_SIZE 1024

void cpu_debug(Cpu *cpu) {
	char buf[DEBUG_BUF_SIZE] = { 0 };

	/* NOLINTNEXTLINE(cert-err33-c) */
	snprintf(
		buf, DEBUG_BUF_SIZE,
		"\tr0-r3 -> %#x | %#x | %#x | %#x \n"
		"\tr4-r7 -> %#x | %#x | %#x | %#x \n"
		"\trA-rD -> %#x | %#x | %#x | %#x \n"
		"\trE-rY -> %#x | %#x | %#x | %#x",
		cpu->regs[REG_0], cpu->regs[REG_1], cpu->regs[REG_2], cpu->regs[REG_3],
		cpu->regs[REG_4], cpu->regs[REG_5], cpu->regs[REG_6], cpu->regs[REG_7],
		cpu->regs[REG_A], cpu->regs[REG_B], cpu->regs[REG_C], cpu->regs[REG_D],
		cpu->regs[REG_E], cpu->regs[REG_F], cpu->regs[REG_X], cpu->regs[REG_Y]
	);

	log_debug("PC -> %#x | SP -> %#x\n%s", cpu->program_counter, cpu->stack_pointer, buf);
}

int main(void) {
	Cpu cpu;
	cpu_powerup(&cpu);
	ram_write16(&cpu, VECTOR_ADDR | VEC_STACK, 0x0000);
	ram_write16(&cpu, VECTOR_ADDR | VEC_STACK + 2, 0x0020);

	cpu_reset(&cpu);

	cpu_debug(&cpu);

	cpu_shutdown(&cpu);
	return EXIT_SUCCESS;
}

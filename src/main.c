#include "cpu.h"

#include <stdlib.h>

int main(void) {
	CPU cpu = { 0 };
	cpuPowerUp(&cpu, "");
	cpuMemWrite(&cpu, 0x400000, 0x00);
	cpuMemWrite(&cpu, 0x400001, 0x80);
	cpuMemWrite(&cpu, 0x400002, 0xff);

	cpuReset(&cpu);

	log_debug("PC: %#x BB: %#x", cpu.regs[REG_PC], cpu.program_bank);

	cpuShutdown(&cpu);
	return EXIT_SUCCESS;
}

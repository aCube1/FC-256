#include "emu/cpu.h"

#include <stdlib.h>

int main(void) {
	CPU cpu = { 0 };
	cpuPowerUp(&cpu);

	cpuMemWrite24(&cpu, VEC_RESET, 0xff8000);

	cpuMemWrite16(&cpu, 0xff8000, 0x1080); /* MOV rX, 0x8000 */
	cpuMemWrite16(&cpu, 0xff8002, 0x8000);

	cpuMemWrite16(&cpu, 0xff8004, 0x8900); /* MOV rC, rX */

	cpuMemWrite16(&cpu, 0xff8006, 0x10c4); /* DEC rX */
	cpuMemWrite16(&cpu, 0xff8008, 0x10c3); /* INC rX */

	cpuReset(&cpu);

	/* TODO: Remove later. */
	char status_msg[9] = "***-----";

	while (cpu.actual_pc <= 0xff8008 || cpu.cycles != 0) {
		cpuClock(&cpu);

		if (cpu.cycles == 0) {
			/* TODO: Remove later. */
			status_msg[3] = bitGet(cpu.status, STATUS_INTERRUPT) ? 'I' : '-';
			status_msg[4] = bitGet(cpu.status, STATUS_OVERFLOW) ? 'O' : '-';
			status_msg[5] = bitGet(cpu.status, STATUS_CARRY) ? 'C' : '-';
			status_msg[6] = bitGet(cpu.status, STATUS_NEGATIVE) ? 'N' : '-';
			status_msg[7] = bitGet(cpu.status, STATUS_ZERO) ? 'Z' : '-';

			log_debug("PC: %#x -> rC: %#x | rX: %#x ", cpu.actual_pc, cpu.regs[REG_C], cpu.regs[REG_X]);
			log_debug("^ Status: %#x -> %s", cpu.status, status_msg);
		}
	}

	cpuShutdown(&cpu);
	return EXIT_SUCCESS;
}

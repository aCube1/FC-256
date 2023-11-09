#include "emu/cpu.h"

#include <stdlib.h>

int main(void) {
	CPU cpu = { 0 };
	cpuPowerUp(&cpu);

	cpuMemWrite24(&cpu, VEC_RESET, 0xff8000);

	cpuMemWrite16(&cpu, 0xff8000, 0x1080); /* MOV rX, 0x8000 */
	cpuMemWrite16(&cpu, 0xff8002, 0x8000);

	cpuMemWrite16(&cpu, 0xff8004, 0x8900); /* MOV rC, rX */

	cpuMemWrite16(&cpu, 0xff8006, 0x1082); /* SUB rX, 0x0001 */
	cpuMemWrite16(&cpu, 0xff8008, 0x0001);

	cpuReset(&cpu);

	/* TODO: Remove later. */
	char status_rep[9] = { 0 };
	status_rep[0] = '*';
	status_rep[1] = '*';
	status_rep[2] = '*';

	while (cpu.actual_pc <= 0xff8008 || cpu.cycles != 0) {
		cpuClock(&cpu);

		if (cpu.cycles == 0) {
			/* TODO: Remove later. */
			status_rep[3] = bitGet(cpu.status, STATUS_INTERRUPT) ? 'I' : '-';
			status_rep[4] = bitGet(cpu.status, STATUS_OVERFLOW) ? 'O' : '-';
			status_rep[5] = bitGet(cpu.status, STATUS_CARRY) ? 'C' : '-';
			status_rep[6] = bitGet(cpu.status, STATUS_NEGATIVE) ? 'N' : '-';
			status_rep[7] = bitGet(cpu.status, STATUS_ZERO) ? 'Z' : '-';

			log_debug("PC: %#x -> rC: %#x | rX: %#x ", cpu.actual_pc, cpu.regs[REG_C], cpu.regs[REG_X]);
			log_debug("^ Status: %#x -> %s", cpu.status, status_rep);
		}
	}

	cpuShutdown(&cpu);
	return EXIT_SUCCESS;
}

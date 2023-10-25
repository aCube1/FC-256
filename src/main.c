#include "cpu.h"

#include <stdlib.h>

int main(void) {
	CPU cpu = { 0 };
	cpuPowerUp(&cpu);

	cpuMemWrite24(&cpu, VEC_RESET, 0xff8000);

	cpuMemWrite16(&cpu, 0xff8000, 0x1080); /* MOV rX, 0x6942 */
	cpuMemWrite16(&cpu, 0xff8002, 0x6942);

	cpuMemWrite16(&cpu, 0xff8004, 0x8900); /* MOV rC, rX */

	cpuMemWrite16(&cpu, 0xff8006, 0x1081); /* ADD rX, 0x0042 */
	cpuMemWrite16(&cpu, 0xff8008, 0x0042);

	cpuReset(&cpu);

	while (cpu.actual_pc <= 0xff8008 || cpu.cycles != 0) {
		cpuClock(&cpu);

		if (cpu.cycles == 0) {
			log_debug("PC: %#x -> rC: %#x | rX: %#x ", cpu.actual_pc, cpu.regs[REG_C], cpu.regs[REG_X]);
		}
	}

	cpuShutdown(&cpu);
	return EXIT_SUCCESS;
}

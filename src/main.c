#include "emu/cpu.h"
#include "emu/opcode.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_BUF_SIZE 1024

static char debug_buf[DEBUG_BUF_SIZE] = { 0 };

void cpu_debug(Cpu *cpu) {
	Opcode opcode = op_table[cpu->current_opcode & 0x00ff];
	u16 data = cpu->operand.src;

	/* NOLINTNEXTLINE(cert-err33-c) */
	snprintf(
		debug_buf, DEBUG_BUF_SIZE,
		"\tr0-r3 -> %#x | %#x | %#x | %#x \n"
		"\tr4-r7 -> %#x | %#x | %#x | %#x \n"
		"\trA-rD -> %#x | %#x | %#x | %#x \n"
		"\trE-rY -> %#x | %#x | %#x | %#x",
		cpu->regs[REG_0], cpu->regs[REG_1], cpu->regs[REG_2], cpu->regs[REG_3],
		cpu->regs[REG_4], cpu->regs[REG_5], cpu->regs[REG_6], cpu->regs[REG_7],
		cpu->regs[REG_A], cpu->regs[REG_B], cpu->regs[REG_C], cpu->regs[REG_D],
		cpu->regs[REG_E], cpu->regs[REG_F], cpu->regs[REG_X], cpu->regs[REG_Y]
	);

	log_debug(
		"PC: %#x | SP: %#x | ST: %#x -> %s %#x\n"
		"%s\n"
		"================",
		cpu->program_counter, cpu->stack_pointer, cpu->status, opcode.name, data,
		debug_buf
	);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		log_info("usage: ./%s <rom.fc>", argv[0]);
		return EXIT_FAILURE;
	}

	Cpu cpu;
	cpu_powerup(&cpu, argv[1]);
	cpu_reset(&cpu);

	char c = '\0';
	while (c != 'q') {
		c = getchar();

		switch (c) {
		case '\n':
			cpu_step(&cpu);
			cpu_debug(&cpu);
			break;
		}
	}

	cpu_shutdown(&cpu);
	return EXIT_SUCCESS;
}

/*
 * mtime.c
 *
 *  Created on: Sep 19, 2023
 *      Author: yon
 */
#include "mtime.h"
#include "main.h"
#include "gpio.h"

__attribute__ ((interrupt)) void mtime_int_handler() {
	unsigned int mcause;
	__asm__ volatile ("csrr %0, mcause":"=r"(mcause)::);
	if (mcause >> 31) {
		unsigned long *mtime_reg = (unsigned long*)MTIMECMP_REG;
		*mtime_reg = (*mtime_reg) + DELAY;
		gpio_output_toggle_c(LED_BLUE);
	}
}

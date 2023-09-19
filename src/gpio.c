/*
 * gpio.c
 *
 *  Created on: Sep 18, 2023
 *      Author: yon
 */

#include "gpio.h"

void gpio_output_enable_c(unsigned int pin_number) {
	gpio_registers_t *GPIO = (gpio_registers_t*)GPIO_BASE;

	int mask = 1 << pin_number;
	char is_enabled = GPIO->output_enable & mask;
	if (is_enabled) {
		GPIO->output_enable &= ~mask;
	}
	else {
		GPIO->output_enable |= mask;
	}
	return;
}

void gpio_output_set_c(unsigned int pin_number, unsigned int value) {
	gpio_registers_t *GPIO = (gpio_registers_t*)GPIO_BASE;

	int mask = 1 << pin_number;
	GPIO->output_value &= ~mask;
	if (value) {
		GPIO->output_value |= mask;
	}
	return;
}

void gpio_output_toggle_c(unsigned int pin_number) {
	gpio_registers_t *GPIO = (gpio_registers_t*)GPIO_BASE;

	int mask = 1 << pin_number;
	int previous_value = GPIO->output_value & mask;

	if (previous_value) {
		gpio_output_set_c(pin_number, 0);
	}
	else {
		gpio_output_set_c(pin_number, 1);
	}

	return;
}

/*
 * main.c
 *
 *  Created on: Sep 18, 2023
 *      Author: yon
 */
#include "main.h"
#include "gpio.h"
#include "mtime.h"

int main(void) {
	register_handler(*vector_table, MODE_VECTOR);
	enable_timer_interrupts();
	enable_global_interrupts();
	set_time_cmp(64000);

	gpio_output_enable_c(LED_GREEN);
	gpio_output_enable_c(LED_RED);
	gpio_output_enable_c(LED_BLUE);

	gpio_output_set_c(LED_RED, LED_OFF);
	gpio_output_set_c(LED_GREEN, LED_OFF);
	gpio_output_set_c(LED_BLUE, LED_OFF);
	while (1) {}
	gpio_output_set_s(LED_GREEN, LED_ON);
	gpio_output_set_s(LED_GREEN, LED_OFF);
	gpio_output_enable_s(LED_GREEN);
	gpio_output_enable_s(LED_GREEN);
	gpio_output_set_s(LED_GREEN, LED_ON);
	gpio_output_set_s(LED_GREEN, LED_OFF);
	gpio_output_set_s(LED_GREEN, LED_ON);
	gpio_output_set_s(LED_GREEN, LED_OFF);
	gpio_output_set_s(LED_GREEN, LED_OFF);
	gpio_output_set_s(LED_GREEN, LED_OFF);
	gpio_output_set_s(LED_GREEN, LED_ON);
	gpio_output_set_s(LED_GREEN, LED_ON);
	gpio_output_set_s(LED_GREEN, LED_ON);
	return 0;
}

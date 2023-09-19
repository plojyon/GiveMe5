/*
 * main.c
 *
 *  Created on: Sep 18, 2023
 *      Author: yon
 */
#include "main.h"
#include "gpio.h"

int main(void) {
	gpio_output_enable_s(LED_GREEN);
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

/*
 * gpio.h
 *
 *  Created on: Sep 18, 2023
 *      Author: yon
 */

#ifndef GPIO_H_
#define GPIO_H_

#define LED_GREEN 19
#define LED_BLUE 21
#define LED_RED 22

#define LED_ON 0
#define LED_OFF 1

#define GPIO_BASE 0x10012000

typedef struct {
	volatile unsigned int input_value;
	volatile unsigned int input_enable;
	volatile unsigned int output_enable;
	volatile unsigned int output_value;
} gpio_registers_t;

void gpio_output_enable_s(unsigned int pin_number);
void gpio_output_enable_c(unsigned int pin_number);
void gpio_output_set_s(unsigned int pin_number, unsigned int value);
void gpio_output_set_c(unsigned int pin_number, unsigned int value);
void gpio_output_toggle_c(unsigned int pin_number);

#endif /* GPIO_H_ */

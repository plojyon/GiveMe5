#include <stdio.h>
//#include <metal/cpu.h>
//#include <metal/led.h>
//#include <metal/button.h>
//#include <metal/switch.h>

#include "main.h"
#include "cgpio.h"

//struct metal_led *led0_red, *led0_green, *led0_blue;

GPIO_Registers_t *GPIO = (GPIO_Registers_t*) GPIO_BASEADDR;


int main (void)
{

	gpio_output_en(22);
	register_handler(_vector_table, INT_MODE_VECTORED);
	enable_global_interrupts();
	enable_mtimer_interrupt();
	set_timer_compare(16384);

	while(1) {}


	//GPIO->GPIO_OUTPUT_EN |= (0x01 << 19);
	//GPIO->GPIO_OUTPUT_VAL ^= (0x01 << 19);

	while(1) {
		gpio_toggle_pin(19);
		gpio_toggle_pin(19);
		gpio_toggle_pin(19);
		gpio_toggle_pin(19);
	}

	// return
	return 0;
}

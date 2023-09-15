#include <stdio.h>
#include "main.h"
#include "mtime.h"
#include "cgpio.h"
#include "uart.h"

unsigned char string[] = "Pa3cio, Give Me Five! \n \0";


GPIO_Registers_t *GPIO = (GPIO_Registers_t*) GPIO_BASEADDR;
UART_Registers_t *UART0 = (UART_Registers_t*) UART0_BASEADDR;
//UART_Registers_t *UART1 = (UART_Registers_t*) UART1_BASEADDR;

long cpufreq;
struct metal_cpu *cpu;

int main (void)
{
	init_uart(UART0, UART_1_STOP_BIT);

	gpio_output_en(19);
	gpio_output_en(21);
	gpio_output_en(22);
	register_handler(_vector_table, INT_MODE_VECTORED);
	enable_global_interrupts();
	enable_mtimer_interrupt();
	set_timer_compare(16384);



	while(1) {
		mtime_delay(200);
		gpio_toggle_pin(19);
		uart_printf(UART0, string);
		mtime_delay(200);
		gpio_toggle_pin(21);
		mtime_delay(200);
		gpio_toggle_pin(22);
	}

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

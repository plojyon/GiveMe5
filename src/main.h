/*
 * main.h
 *
 *  Created on: Sep 18, 2023
 *      Author: yon
 */

#ifndef MAIN_H_
#define MAIN_H_

#define MODE_DIRECT 0
#define MODE_VECTOR 1

#define DELAY 32000

void register_handler(void* vector_table, unsigned int mode);
void enable_global_interrupts();
void enable_timer_interrupts();
void set_time_cmp(unsigned int delay);

void vector_table();

#endif /* MAIN_H_ */

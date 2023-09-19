/*
 * mtime.h
 *
 *  Created on: Sep 19, 2023
 *      Author: yon
 */

#ifndef MTIME_H_
#define MTIME_H_

#define MTIME_REG		0x0200bff8
#define MTIMECMP_REG	0x02004000

void mtime_int_handler();

#endif /* MTIME_H_ */

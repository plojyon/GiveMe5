#ifndef MAIN_H
#define MAIN_H

#define CLINT_BASE                	0x02000000
#define CLINT_MTIME               	0x0200bff8
#define CLINT_MTIME_CMP         	0x02004000

unsigned int *pMTime 	= (unsigned int *)CLINT_MTIME;
unsigned int *pMTimeCmp = (unsigned int *)CLINT_MTIME_CMP;

__attribute__ ((interrupt ("machine"))) void mtime__handler(void) ;

void mtime_delay(unsigned int miliseconds);

#endif

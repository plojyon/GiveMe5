#ifndef CGPIO_H_
#define CGPIO_H_


#define GPIO_BASEADDR     0x10012000

typedef struct
{
	volatile int GPIO_INPUT_VAL;
	volatile int GPIO_INPUT_EN;
	volatile int GPIO_OUTPUT_EN;
	volatile int GPIO_OUTPUT_VAL;
}GPIO_Registers_t;




#endif

/*
 * gpio.S
 *
 *  Created on: Sep 18, 2023
 *      Author: yon
 *
 */

.section .text
.option norvc // no compressed code

.equ GPIO_BASE, 0x10012000
.equ GPIO_OE, 0x08 // out_enable
.equ GPIO_OV, 0x0C // out_value

// :param: a0 - pin number
.align 2                            // Align to 4 (=2^2) bytes boundary == .balign 4
.global gpio_output_enable_s          // Emit functgion_name to symbol table (scope GLOBAL)
.type gpio_output_enable_s, @function // Not needed
gpio_output_enable_s:
    # prologue
    addi sp, sp, -16                # Allocate the routine stack frame
    sw ra, 12(sp)                   # Save the return address
    sw fp, 8(sp)                    # Save the frame pointer
    sw s1, 4(sp)
    sw s2, 0(sp)
    addi fp, sp, 16                 # Set the framepointer

	la t0, GPIO_BASE
	lw t1, GPIO_OE(t0)
	li t2, 19
	li t3, 0x01
	sll t3, t3, t2
	or t1, t1, t3
	sw t1, GPIO_OE(t0)

    # epilogue
    lw s2, 0(sp)
    lw s1, 4(sp)
    lw fp, 8(sp)                    # restore the frame pointer
    lw ra, 12(sp)                   # restore the return address from the stack frame
    addi sp, sp, 16                 # de-allocate the routine stack frame
    ret




// :param: a0 - pin number
// :param: a1 - enable/disable
.align 2
.global gpio_output_set_s
.type gpio_output_set_s, @function
gpio_output_set_s:
    # prologue
    addi sp, sp, -16                # Allocate the routine stack frame
    sw ra, 12(sp)                   # Save the return address
    sw fp, 8(sp)                    # Save the frame pointer
    sw s1, 4(sp)
    sw s2, 0(sp)
    addi fp, sp, 16                 # Set the framepointer


	la t0, GPIO_BASE // t0 <- GPIO_BASE
	lw t1, GPIO_OV(t0) // t1 <- value[GPIO_BASE]

	sll a1, a1, a0 // a1 << a0

	li t3, 0x01
	sll t3, t3, a0 // t3 <- 2^a0
	not t4, t3 // t4 <- ~t3

	and t1, t1, t4 // t1 &= ~2^a0
	or t1, t1, a1 // t1 |= 2^a1
	sw t1, GPIO_OV(t0)


    # epilogue
    lw s2, 0(sp)
    lw s1, 4(sp)
    lw fp, 8(sp)                    # restore the frame pointer
    lw ra, 12(sp)                   # restore the return address from the stack frame
    addi sp, sp, 16                 # de-allocate the routine stack frame
    ret





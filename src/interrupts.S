/*
 * interrupts.S
 *
 *  Created on: Sep 19, 2023
 *      Author: yon
 */

.section .text
.option norvc // no compressed code

.equ DELAY, 32768

.balign 64
.global vector_table
.type vector_table, @function
vector_table:
	j default_handler
	j default_handler
	j default_handler
	j swi_handler
	j default_handler
	j default_handler
	j default_handler
	j mtime_int_handler
	j default_handler
	j default_handler
	j default_handler
	j exti_handler
	j default_handler

.balign 4
.weak swi_handler
.global swi_handler
.type swi_handler, @function
swi_handler:
	mret


.balign 4
.weak mtime_int_handler
.global mtime_int_handler
.type mtime_int_handler, @function
mtime_int_handler:
	csrr t0, mcause // control
	bgez t0, 1f // branch if greater or equal to zero

    li t0, 0x0200bff8               # load the mtime address
    lw t1, 0(t0)                    # load mtime (LO)
    lw t2, 4(t0)                    # load mtime (HI)
    li t3, DELAY
    add t3, t1, t3                  # increment lower bits by DELAY cycles
    sltu t1, t3, t1                 # generate carry-out (set 1 if less than, unsigned)
    add t2, t2, t1                  # add carry to upper bits

    li t0, 0x02004000
    sw t3, 0(t0)                    # update mtimecmp (LO)
    sw t2, 4(t0)                    # update mtimecmp (HI)

    # toggle green led:
    li a0, 19
    jal gpio_output_toggle_c

1:
	mret

.balign 4
.weak exti_handler
.global exti_handler
.type exti_handler, @function
exti_handler:
	mret

.balign 4
.weak default_handler
.global default_handler
.type default_handler, @function
default_handler:
	mret

.balign 4
.global _panic_handler
.type _panic_handler, @function
_panic_handler:
    j _panic_handler


.equ MSTATUS_MIE_BIT_MASK,  0x00000008  # bit 3
.equ MIE_MTIE_BIT_MASK,     0x00000080  # bit 7
.equ MIE_MEIE_BIT_MASK,     0x00000800  # bit 11

.balign 4
.global enable_global_interrupts
.type enable_global_interrupts, @function
enable_global_interrupts:
    addi sp, sp, -16                # Allocate the routine stack frame
    sw ra, 12(sp)                   # Save the return address
    sw fp, 8(sp)                    # Save the frame pointer
    sw s1, 4(sp)
    sw s2, 0(sp)
    addi fp, sp, 16                 # Set the framepointer

    li t0, MSTATUS_MIE_BIT_MASK     # load the mask for MIE
    csrs mstatus, t0                #  set the MIE bit in mstatus

    lw s2, 0(sp)
    lw s1, 4(sp)
    lw fp, 8(sp)                    # restore the frame pointer
    lw ra, 12(sp)                   # restore the return address from the stack frame
    addi sp, sp, 16                 # de-allocate the routine stack frame
    ret


.balign 4
.global enable_timer_interrupts
.type enable_timer_interrupts, @function
enable_timer_interrupts:
    addi sp, sp, -16                # Allocate the routine stack frame
    sw ra, 12(sp)                   # Save the return address
    sw fp, 8(sp)                    # Save the frame pointer
    sw s1, 4(sp)
    sw s2, 0(sp)
    addi fp, sp, 16                 # Set the framepointer

    li t0, MIE_MTIE_BIT_MASK
    csrs mie, t0

    lw s2, 0(sp)
    lw s1, 4(sp)
    lw fp, 8(sp)                    # restore the frame pointer
    lw ra, 12(sp)                   # restore the return address from the stack frame
    addi sp, sp, 16                 # de-allocate the routine stack frame
    ret


.balign 4
.global set_time_cmp
.type set_time_cmp, @function
set_time_cmp:
    addi sp, sp, -16                # Allocate the routine stack frame
    sw ra, 12(sp)                   # Save the return address
    sw fp, 8(sp)                    # Save the frame pointer
    sw s1, 4(sp)
    sw s2, 0(sp)
    addi fp, sp, 16                 # Set the framepointer

	la t0, 0x02004000
	sw a0, 0(t0)					# save into mtimecmp
	sw x0, 4(t0)

    lw s2, 0(sp)
    lw s1, 4(sp)
    lw fp, 8(sp)                    # restore the frame pointer
    lw ra, 12(sp)                   # restore the return address from the stack frame
    addi sp, sp, 16                 # de-allocate the routine stack frame
    ret


// Register the base address for vector table in mtvec
// a0 - interrupt vector table base address
// a1 - interrupt processing mode (0x0 - direct, 0x1 - vectored)
.balign 4
.global register_handler
.type register_handler, @function
register_handler:
    addi sp, sp, -16                # Allocate the routine stack frame
    sw ra, 12(sp)                   # Save the return address
    sw fp, 8(sp)                    # Save the frame pointer
    sw s1, 4(sp)
    sw s2, 0(sp)
    addi fp, sp, 16                 # Set the framepointer

	# mtvec: ..............base............xx <- mode
    or a0, a0, a1
    csrw mtvec, a0

    lw s2, 0(sp)
    lw s1, 4(sp)
    lw fp, 8(sp)                    # restore the frame pointer
    lw ra, 12(sp)                   # restore the return address from the stack frame
    addi sp, sp, 16                 # de-allocate the routine stack frame
    ret


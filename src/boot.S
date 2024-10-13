#include "test_define.h"
#include "reg_offset.h"
#include "mm.h"

    .section ".text.boot"

.global _start
_start:
    mrs x0, mpidr_el1
    and x0, x0, #0xFF // check processor id

    cbz x0, e12_entry // set interrupt table

    b proc_main

e11_entry:
	/* 设置异常向量表基地址到vbar寄存器 */
	ldr     x5, =vectors
	msr     vbar_el1, x5
	isb

	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero // bss mem zero
    
    mov	sp, #LOW_MEMORY // set sp

    b kernel_main
    b proc_main

proc_main:
    b proc_main

e12_entry:

    ldr x0, =HCR_RW
    msr hcr_el2, x0
    ldr x0, =SCTLR_VALUE_MMU_DISABLE
    msr sctlr_el1, x0
    ldr x0, =SPSR_EL1h
    msr spsr_el2, x0
    adr x0, e11_entry
    msr elr_el2, x0
    eret

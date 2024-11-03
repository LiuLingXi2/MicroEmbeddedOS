.align
.global cpu_switch_to
cpu_switch_to:
    // prec -> cpu_context
    add x8, x0, #THREAD_CPU_CONTEXT
    mov x9, sp
	stp     x19, x20, [x8], #16
	stp     x21, x22, [x8], #16
	stp     x23, x24, [x8], #16
	stp     x25, x26, [x8], #16
	stp     x27, x28, [x8], #16
	stp     x29, x9, [x8], #16
	str     lr, [x8]

    // cpu_context -> next
	add     x8, x1, #THREAD_CPU_CONTEXT
	ldp     x19, x20, [x8], #16
	ldp     x21, x22, [x8], #16
	ldp     x23, x24, [x8], #16
	ldp     x25, x26, [x8], #16
	ldp     x27, x28, [x8], #16
	ldp     x29, x9, [x8], #16
	ldr     lr, [x8]
	mov     sp, x9
    ret


.align 2
.global ret_from_fork
ret_from_fork:
    cbz x19, 1f // kernel thread (x19 != 0) ?
    mov x0, x20
    blr x19

1:
    b ret_to_user



.global ret_user
ret_user:
    // set the sp register address to return to user mode
    // x0=sp_el0 from alloc_page()
    msr sp_el0, x0
    // set the pc register address to return to user mode
    ldr x1, =while_user
    msr elr_el1, x1
    // el0t: el0 && sp_el0
    mov x2, #0x0
    msr spsr_el1, x2
    eret

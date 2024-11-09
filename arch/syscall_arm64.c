#include <asm/syscall.h>
#include <irq.h>

long __arm64_sys_open(struct pt_regs *regs)
{
    return sys_open((const char *)regs->regs[0], regs->regs[1]);
}

long __arm64_sys_close(struct pt_regs *regs)
{
    return 0;
}

long __arm64_sys_read(struct pt_regs *regs)
{
    return 0;
}

long __arm64_sys_write(struct pt_regs *regs)
{
    return 0;
}

long __arm64_sys_clone(struct pt_regs *regs)
{
    return 0;
}

long __arm64_sys_malloc(struct pt_regs *regs)
{
    return 0;
}
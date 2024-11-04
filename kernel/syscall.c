#include "asm/syscall.h"
#include "irq.h"
#include "syscall_arm64.h"

typedef long (*syscall_fn_t)(struct pt_regs *regs);

#define __SYSCALL(nr, sym) [nr] = (syscall_fn_t)__arm64_##sym,

const syscall_fn_t syscall_table[__NR_syscalls] = {
    __SYSCALL(__NR_open, sys_open)
    __SYSCALL(__NR_open, sys_close)
    __SYSCALL(__NR_open, sys_read)
    __SYSCALL(__NR_open, sys_write)
    __SYSCALL(__NR_open, sys_clone)
    __SYSCALL(__NR_open, sys_malloc)
};

unsigned long open(const char *file_name, int flags)
{
    return syscall(__NR_open, file_name, flags);
}

static void el0_syscall_common(struct pt_regs *regs, int syscall_no, int syscall_nr, const syscall_fn_t syscall_table[])
{
    long ret;
    syscall_fn_t fn;
    if (syscall_no < syscall_nr) {
        fn = syscall_table[syscall_no];
        ret = fn(regs);
    }

    regs->regs[0] = ret;
}

void el0_svc_handle(struct pt_regs *regs)
{
    return el0_syscall_common(regs, regs->regs[8], __NR_syscalls, syscall_table);
}

long sys_open(const char *reg0, int reg1)
{
    return 0;
}
#ifndef __ASM_SYSCALL_H__

#define __ASM_SYSCALL_H__

#include "irq.h"

#define __NR_open     0
#define __NR_close    1
#define __NR_read     2
#define __NR_write    3
#define __NR_clone    4
#define __NR_malloc   5
#define __NR_syscalls 6

unsigned long open(const char *file_name, int flags);

void el0_svc_handle(struct pt_regs *regs);

extern int syscall(int num, ...);
long sys_open(const char *reg0, int reg1);

#endif //!__ASM_SYSCALL_H__
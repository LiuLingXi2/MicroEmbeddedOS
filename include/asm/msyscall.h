#ifndef __ASM_SYSCALL_H__

#define __ASM_SYSCALL_H__

#include <irq.h>

#define __NR_open     0
#define __NR_close    1
#define __NR_read     2
#define __NR_write    3
#define __NR_clone    4
#define __NR_malloc   5
#define __NR_chdir    6  // there is no need to save the context at this point
#define __NR_syscalls 7

unsigned long open(const char *file_name, int flags);
int chdir(const char *path);

void el0_svc_handle(struct pt_regs *regs);

extern int syscall(int num, ...);

long sys_open(const char *reg0, int reg1);
int sys_chdir(const char *reg0);

#endif //!__ASM_SYSCALL_H__
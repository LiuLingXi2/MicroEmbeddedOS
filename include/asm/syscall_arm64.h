#ifndef __ARCH_SYSCALL_H__
#define __ARCH_SYSCALL_H__

long __arm64_sys_open(struct pt_regs *regs);
long __arm64_sys_close(struct pt_regs *regs);
long __arm64_sys_read(struct pt_regs *regs);
long __arm64_sys_write(struct pt_regs *regs);
long __arm64_sys_malloc(struct pt_regs *regs);
long __arm64_sys_clone(struct pt_regs *regs);

#endif //!__ARCH_SYSCALL_H__
#ifndef __INCLUDE_ASM_SYSTEM_H__

#define __INCLUDE_ASM_SYSTEM_H__

#define PSR_MODE_EL1h	0x00000005

#define DEFINE(sym, val) \
    asm volatile("\n.global " #sym "\n" #sym " = %0\n" : : "i" (val))

#define OFFSET(sym, str, mem) DEFINE(sym, offsetof(struct str, mem))

#define offsetof(TYPE, MEMBER)	((long)&((TYPE *)0)->MEMBER)

#endif //!__INCLUDE_ASM_SYSTEM_H__
#ifndef ASM_BARRIER_H
#define ASM_BARRIER_H

#ifndef __ASSEMBLY__
#define isb()		asm volatile("isb" : : : "memory")
#define dsb(opt)	asm volatile("dsb " #opt : : : "memory")
#endif

#endif /*ASM_BARRIER_H*/

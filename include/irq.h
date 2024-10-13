#ifndef __INCLUDE_IRQ_H__
#define __INCLUDE_IRQ_H__

struct pt_regs {
	unsigned long regs[31];
	unsigned long sp;
	unsigned long pc;
	unsigned long pstate;
};

#define GENERIC_TIMER_IRQ 30
#define SYSTEM_TIMER0_IRQ 96
#define SYSTEM_TIMER1_IRQ 97

#define ARM_LOCAL_BASE 0xff800000

#define TIMER_CNTRL0 (ARM_LOCAL_BASE + 0x40)
#define TIMER_CNTRL1 (ARM_LOCAL_BASE + 0x44)
#define TIMER_CNTRL2 (ARM_LOCAL_BASE + 0x48)
#define TIMER_CNTRL3 (ARM_LOCAL_BASE + 0x4c)

#define CNT_PS_IRQ (1 << 0)
/* Nonsecure Physical Timer Event for IRQ */
#define CNT_PNS_IRQ (1 << 1)
/* Hypervisor Physical Timer Event for IRQ */
#define CNT_HP_IRQ (1 << 2)
/* Virtual Timer Event for IRQ */
#define CNT_V_IRQ (1 << 3)
/* Secure Physical Timer Event for FIQ */
#define CNT_PS_IRQ_FIQ (1 << 4)
/* Nonsecure Physical Timer Event for FIQ */
#define CNT_PNS_IRQ_FIQ (1 << 5)
/* Hypervisor Physical Timer Event for FIQ */
#define CNT_HP_IRQ_FIQ (1 << 6)
/* Virtual Timer Event for FIQ */
#define CNT_V_IRQ_FIQ (1 << 7)

static inline void arch_local_irq_enable(void)
{
	asm volatile(
		"msr daifclr, #2"
		:
		:
		: "memory");
}

static inline void arch_local_irq_disable(void)
{
	asm volatile(
		"msr daifset, #2"
		:
		:
		: "memory");
}

#define raw_local_irq_disable()	arch_local_irq_disable()
#define raw_local_irq_enable()	arch_local_irq_enable()

#endif // !__INCLUDE_IRQ_H__
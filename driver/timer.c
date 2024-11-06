#include "irq.h"
#include "io.h"
#include "gic.h"
#include "std/printk.h"
#include "timer.h"

#define HZ 250
#define NSEC_PER_SEC    1000000000L

static unsigned int val = NSEC_PER_SEC / HZ;
static unsigned int stimer_val = 0;
static unsigned int sval = 200000;

static int generic_timer_init(void)
{
	asm volatile(
		"mov x0, #1\n"
		"msr cntp_ctl_el0, x0"
		:
		:
		: "memory");

	return 0;
}

static int generic_timer_reset(unsigned int val)
{
    /* Set comparison register */
	asm volatile(
		"msr cntp_tval_el0, %x[timer_val]"
		:
		: [timer_val] "r" (val)
		: "memory");

	return 0;
}

// static void enable_timer_interrupt(void)
// {
// 	writel(CNT_PNS_IRQ, TIMER_CNTRL0);
// }

void local_timer_init(void)
{
    (void)generic_timer_init();

    (void)generic_timer_reset(val);

    gicv2_unmask_irq(GENERIC_TIMER_IRQ);

	// conventiental interrupt controller
    // enable_timer_interrupt();
}

void system_timer_init(void)
{
	stimer_val = readl(TIMER_CLO);
	stimer_val += sval;
	writel(stimer_val, TIMER_C1);

	gicv2_unmask_irq(SYSTEM_TIMER1_IRQ);
}

void handle_timer_irq(void)
{
	generic_timer_reset(val);
	// 进程调度
	printk("Core0 Local Timer interrupt received\r\n");
}

void handle_stimer_irq(void)
{
	stimer_val += sval;
	writel(stimer_val, TIMER_C1);
	writel(TIMER_CS_M1, TIMER_CS);
	printk("Sytem Timer interrupt \n");
}
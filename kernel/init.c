
#include "pl_uart.h"
#include "std/printk.h"
#include "gic.h"
#include "irq.h"
#include "timer.h"
#include "io.h"
#include "test/test.h"
#include "mm/mm.h"
#include "mm/mmu.h"
#include "asm/system.h"
#include "proc/sche.h"

extern char _text_boot[], _etext_boot[];
extern char _text[], _etext[];
extern char _rodata[], _erodata[];
extern char _data[], _edata[];
extern char _bss[], _ebss[];

static void pmem_layout(void)
{
	printk("Image layout:\n");
	printk("  .text.boot: 0x%08lx - 0x%08lx (%6ld B)\n",
			(unsigned long)_text_boot, (unsigned long)_etext_boot,
			(unsigned long)(_etext_boot - _text_boot));
	printk("       .text: 0x%08lx - 0x%08lx (%6ld B)\n",
			(unsigned long)_text, (unsigned long)_etext,
			(unsigned long)(_etext - _text));
	printk("     .rodata: 0x%08lx - 0x%08lx (%6ld B)\n",
			(unsigned long)_rodata, (unsigned long)_erodata,
			(unsigned long)(_erodata - _rodata));
	printk("       .data: 0x%08lx - 0x%08lx (%6ld B)\n",
			(unsigned long)_data, (unsigned long)_edata,
			(unsigned long)(_edata - _data));
	printk("        .bss: 0x%08lx - 0x%08lx (%6ld B)\n\n",
			(unsigned long)_bss, (unsigned long)_ebss,
			(unsigned long)(_ebss - _bss));
}

static void define_offsetof(void)
{
	DEFINE(THREAD_CPU_CONTEXT, offsetof(struct task_struct, cpu_context));
	DEFINE(TI_PREEMPT,  offsetof(struct task_struct, preempt_count));
	DEFINE(NEED_RESCHED, offsetof(struct task_struct, need_resched));
}

static const char * const bad_mode_handler[] = {
	"Sync Abort",
	"IRQ",
	"FIQ",
	"SError"
};

void bad_mode(struct pt_regs *regs, int reason, unsigned int esr)
{
	printk(RED"Bad mode for %s handler detected, far:0x%x esr:0x%x\n" NONE,
			bad_mode_handler[reason], read_sysreg(far_el1),
			esr);
}

void kernel_thread1(void)
{
	while (1) {
		delay(50000000);
		printk("%s: %s\n", __func__, "10");
	}
	exit(1);
}

void kernel_thread2(void)
{
	while (1) {
		delay(10000000);
		printk("%s: %s\n", __func__, "5");
	}
	exit(1);
}

void kernel_main(void)
{
	// define_offsetof();
	uart_init();
    printk_init();

	printk(GREEN"Welcome MicroEmbeddedOS v0.1 (2024 10-15)\n\n" NONE);

    printk(GREEN" /\\_/\\      /\\_/\\      /\\_/\\\n"NONE);
    printk(GREEN"( o.o )    ( o.o )    ( o.o )\n"NONE);
    printk(GREEN" > ^ <      > ^ <      > ^ <\n\n"NONE);

	pmem_layout();

	printk("microembeeded os loading address: 0x%08lx\n", (unsigned long)_text_boot);
	
	mem_init((unsigned long)_ebss, TOTAL_MEMORY);
	sched_init();
	// setup_arch();

	int pid;
	pid = do_fork(PF_KTHREAD, (unsigned long)&kernel_thread1, 0, 10);
	if (pid < 0) {
		printk("create thread fail\n");
	}

	pid = do_fork(PF_KTHREAD, (unsigned long)&kernel_thread2, 0, 5);
	if (pid < 0) {
		printk("create thread fail\n");
	}

	// test_access_map_address();
	// test_access_unmap_address();

	gic_init(0, GIC_DISPATCH, GIC_CPU);

	local_timer_init();

	// system_timer_init();

	raw_local_irq_enable();

	// alloc_page();
	// int pid;

	// pid = do_fork(PF_KTHREAD, (unsigned long)&kernel_thread1, 0, 10);
	// if (pid < 0) {
	// 	printk("create thread fail\n");
	// }

	// pid = do_fork(PF_KTHREAD, (unsigned long)&kernel_thread2, 0, 5);
	// if (pid < 0) {
	// 	printk("create thread fail\n");
	// }

	schedule();

	while (1) {
		uart_send(uart_recv());
	}
}
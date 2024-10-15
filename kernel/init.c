
#include "pl_uart.h"
#include "printk.h"
#include "gic.h"
#include "irq.h"
#include "timer.h"
#include "io.h"
#include "test.h"
#include "mm.h"

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

void kernel_main(void)
{
	uart_init();
    printk_init();

	printk(GREEN"Welcome MicroEmbeddedOS v0.1 (2024 10-15)\n\n" NONE);

    printk(GREEN" /\\_/\\      /\\_/\\      /\\_/\\\n"NONE);
    printk(GREEN"( o.o )    ( o.o )    ( o.o )\n"NONE);
    printk(GREEN" > ^ <      > ^ <      > ^ <\n\n"NONE);

	pmem_layout();

	printk("microembeeded os loading address: 0x%08lx\n", (unsigned long)_text_boot);
	
	// mem_init();
	setup_arch();
	
	test_access_map_address();
	test_access_unmap_address();

	gic_init(0, GIC_DISPATCH, GIC_CPU);

	// local_timer_init();

	// system_timer_init();

	// raw_local_irq_enable();

	while (1) {
		uart_send(uart_recv());
	}
}
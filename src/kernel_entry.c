
#include "pl_uart.h"

extern void trigger_alignment(void);

#define read_sysreg(reg) ({ \
		unsigned long _val; \
		asm volatile("mrs %0," #reg \
		: "=r"(_val)); \
		_val; \
})

#define write_sysreg(val, reg) ({ \
		unsigned long _val = (unsigned long)val; \
		asm volatile("msr " #reg ", %x0" \
		:: "rZ"(_val)); \
})

static const char * const bad_mode_handler[] = {
	"Sync Abort",
	"IRQ",
	"FIQ",
	"SError"
};

void bad_mode(struct pt_regs *regs, int reason, unsigned int esr)
{
	printk("Bad mode for %s handler detected, far:0x%x esr:0x%x\n",
			bad_mode_handler[reason], read_sysreg(far_el1),
			esr);
    uart_send_string("Welcome BenOS!\r\n");
}

int kernel_main()
{
	uart_init(); // init pl0
    init_printk_done();

	uart_send_string("Welcome BenOS!\r\n");

    printk("printk init done\n");

    // trigger_alignment();

	while (1) {
		uart_send(uart_recv());
	}

    return 0;
}
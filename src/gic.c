#include "gic.h"
#include "irq.h"
#include "printk.h"
#include "io.h"
#include "timer.h"

#define ARM_GIC_MAX_NR 1

static struct gic_chip_data gic_data[ARM_GIC_MAX_NR];

static unsigned long gic_get_dist_base(void)
{
	struct gic_chip_data *gic = &gic_data[0];

	return gic_dist_base(gic);
}

static void gic_set_irq(int irq, unsigned int offset)
{
	unsigned int mask = 1 << (irq % 32);

	writel(mask, gic_get_dist_base() + offset + (irq / 32) * 4);
}

static unsigned long gic_get_cpu_base(void)
{
	struct gic_chip_data *gic = &gic_data[0];

	return gic_cpu_base(gic);
}

void gicv2_mask_irq(int irq)
{
	gic_set_irq(irq, GICD_ICENABLER);
}

void gicv2_unmask_irq(int irq)
{
	gic_set_irq(irq, GICD_ISENABLER);
}

static unsigned int gic_get_cpumask(struct gic_chip_data *gic)
{
	unsigned long base = gic_dist_base(gic);
	unsigned int mask, i;

	for (i = mask = 0; i < 32; i += 4) {
		mask = readl(base + GICD_ITARGETSR + i);
		mask |= mask >> 16;
		mask |= mask >> 8;

		if (mask) {
			break;
        }
	}

	return mask;
}

static void gic_dist_init(struct gic_chip_data *gic)
{
	unsigned long base = gic_dist_base(gic);
	unsigned int cpumask;
	unsigned int gic_irqs = gic->gic_irqs;
	int i;

    writel(0x0, base + GICD_CTLR); // cli

    /**
     * The first 32 interrupt fixes are written into the hardware,
     * thus indicating that these processors can handle interrupts,
     * and SPI uses these processors as usual
     */
	cpumask = gic_get_cpumask(gic);
	cpumask |= cpumask << 8;
	cpumask |= cpumask << 16;

	for (i = 32; i < gic_irqs; i += 4)
		writel(cpumask, base + GICD_ITARGETSR + i * 4 / 4);

	/* Set all global interrupts to be level triggered, active low */
	for (i = 32; i < gic_irqs; i += 16) {
		writel(0, base + GICD_ICFGR + i / 4);
    }

    /* Deactivate and disable all 中断（SGI， PPI， SPI）. */
	for (i = 0; i < gic_irqs; i += 32) {
		writel(0xffffffff, base +
				GICD_ICACTIVER + i / 8);
		writel(0xffffffff, base +
				GICD_ICENABLER + i / 8);
	}

	/*The interrupt register was enabled SGI: 0-15*/
	writel(0x0000ffff, base + GICD_ISENABLER);

    writel(0x1, base + GICD_CTLR); // sti
}

void gic_cpu_init(struct gic_chip_data *gic)
{
	int i;
	unsigned long base = gic_cpu_base(gic);
	unsigned long dist_base = gic_dist_base(gic);

    // Set the interrupt priority of SGI and PPI to a0
	for (i = 0; i < 32; i += 4) {
		writel(0xa0a0a0a0, dist_base + GICD_IPRIORITYR + i * 4 / 4);
    }

    /**
     * The Cortex-A7 selects 32 priorities, the GICC_PMR register, 
     * which is used to determine how many priorities to use, 
     * the GICC_PMR register is only valid for the lower 8 bits, 
     * which can set up to 256 priorities
     */
	writel(0xf0, base + GICC_PMR);

	writel(0x1, base + GICC_CTRL);
}

static void gicv2_eoi_irq(int irq)
{
	writel(irq, gic_get_cpu_base() + GICC_EOIR);
}

void gic_handle_irq(void)
{
	struct gic_chip_data *gic = &gic_data[0];
	unsigned long base = gic_cpu_base(gic);
	unsigned int irqstat, irqnr;

	// do {
	// 	irqstat = readl(base + GICC_IAR); // read interrupt id
	// 	irqnr = irqstat & 0x3ff;

	// 	if (irqnr == GENERIC_TIMER_IRQ)
	// 		handle_timer_irq();

	// } while (0)

	irqstat = readl(base + GICC_IAR); // read interrupt id
	irqnr = irqstat & 0x3ff;

	switch (irqnr) {
		case GENERIC_TIMER_IRQ:
			handle_timer_irq();
			break;
		case SYSTEM_TIMER0_IRQ:
			handle_stimer_irq();
			break;
		case SYSTEM_TIMER1_IRQ:
			handle_stimer_irq();
			break;
		default:
			printk("This Interrupt is not implement!\n");
			break;
	}

	gicv2_eoi_irq(irqnr);
}

void gic_init(int chip, unsigned long dist_base, unsigned long cpu_base)
{
    struct gic_chip_data *gic;

	int gic_irqs;

	gic = &gic_data[chip];

	gic->raw_cpu_base = cpu_base; // set cpu base
	gic->raw_dist_base = dist_base; // set distribute base

	/* readout how many interrupts are supported*/
	gic_irqs = readl(gic_dist_base(gic) + GICD_TYPER) & 0x1f; // [4:0] ITLinesNumber
	gic_irqs = (gic_irqs + 1) * 32;
	if (gic_irqs > 1020) {
		gic_irqs = 1020;
    }

	gic->gic_irqs = gic_irqs;

	printk("gic_init [ cpu_base:0x%x, dist_base:0x%x, gic_irqs:%d ]\n", cpu_base, dist_base, gic->gic_irqs);

	gic_dist_init(gic); // dist init
	gic_cpu_init(gic); // cpu init
}
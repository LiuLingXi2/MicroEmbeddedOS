#ifndef __INCLUDE_INTR_H__

#define __INCLUDE_INTR_H__

#define GIC_BASE_ADDR (0xFF840000)

// Conventional Interrupt Controller

// GIC V2
#define GIC_DISPATCH     (GIC_BASE_ADDR + 0x1000)
#define GIC_CPU          (GIC_BASE_ADDR + 0x2000)
#define GIC_VIRT_CONTROL (GIC_BASE_ADDR + 0x5000)
#define GIC_VIRT_CPU     (GIC_BASE_ADDR + 0x6000)

#define GICD_CTLR       (0x000)
#define GICD_TYPER      (0x004)
#define GICD_IIDR       (0x008)
#define GICD_IGROUPR    (0x080)
#define GICD_ISENABLER  (0x100)
#define GICD_ICENABLER  (0x180)
#define GICD_ISPENDR    (0x200)
#define GICD_ICPENDR    (0x280)
#define GICD_ISACTIVER  (0x300)
#define GICD_ICACTIVER  (0x380)
#define GICD_IPRIORITYR (0x400)
#define GICD_ITARGETSR  (0x800)
#define GICD_ICFGR      (0xC00)
#define GICD_SGIR       (0xF00)
#define GICD_CPENDSGIR  (0xF10)
#define GICD_SPENDSGIR  (0xF20)

#define GICC_CTRL       (0x000)
#define GICC_PMR        (0x004)
#define GICC_BPR        (0x008)
#define GICC_IAR        (0x00C)
#define GICC_EOIR       (0x010)
#define GICC_RPR        (0x014)
#define GICC_HPPIR      (0x018)
#define GICC_APR        (0x0D0)
#define GICC_IIDR       (0x0FC)

struct gic_chip_data {
	unsigned long raw_dist_base;
	unsigned long raw_cpu_base;
	struct irq_domain *domain;
	struct irq_chip *chip;
	unsigned int gic_irqs;
};

#define gic_dist_base(d) ((d)->raw_dist_base)
#define gic_cpu_base(d) ((d)->raw_cpu_base)

void gicv2_unmask_irq(int irq);
void gicv2_mask_irq(int irq);
void gic_handle_irq(void);
void gic_init(int chip, unsigned long dist_base, unsigned long cpu_base);

#endif // !__INCLUDE_INTR_H__
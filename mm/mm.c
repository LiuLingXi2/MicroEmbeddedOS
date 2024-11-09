#include <mm/mm.h>
#include <std/printk.h>

#define NR_PAGES (TOTAL_MEMORY / PAGE_SIZE)

static unsigned short mem_map[NR_PAGES] = {0,};

static unsigned long phy_start_address;

void mem_init(unsigned long start_mem, unsigned long end_mem)
{
	unsigned long nr_free_pages = 0;
	unsigned long free;

	start_mem = PAGE_ALIGN(start_mem);
	phy_start_address = start_mem;
	end_mem &= PAGE_MASK;
	free = end_mem - start_mem;

	// printk("start_mem: 0x%08lx, end_mem: 0x%08lx\n", start_mem, end_mem);

	/* The start_mem address is _ebss */
	while (start_mem < end_mem) {
		nr_free_pages++;
		start_mem += PAGE_SIZE;
	}

	printk("memory: %uKB available, %u free pages\n", free/1024, nr_free_pages);
}

/**
 * @brief Notice that the physical allocation page here starts at LOW_MEMORY, 0x00400000
 */
unsigned long alloc_page(void)
{
	int i;

	for (i = 0; i < NR_PAGES; i++) {
		if ((i == 0) && (mem_map[0] == 0)) {
			printk("mem_map address: 0x%08lx\n", LOW_MEMORY);
		}
		if (mem_map[i] == 0) {
			mem_map[i] = 1;
			// printk("%s: allocate page address: 0x%08lx\n", __FUNCTION__, LOW_MEMORY + i * PAGE_SIZE);
			return LOW_MEMORY + i * PAGE_SIZE;
		}
	}
	return 0;
}

void free_page(unsigned long p)
{
	mem_map[(p - LOW_MEMORY)/PAGE_SIZE] = 0;
}

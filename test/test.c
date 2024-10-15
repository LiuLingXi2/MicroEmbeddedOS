#include "mm/mm.h"
#include "printk.h"
#include "test.h"

void test_access_map_address(void)
{
    unsigned long address = TOTAL_MEMORY - (1 << PAGE_SHIFT);
    *(unsigned long *) address = 0x55;
    printk(BLUE"%s: [ access 0x%x done ]\n" NONE, __func__, address);
}

void test_access_unmap_address(void)
{
    unsigned long address = TOTAL_MEMORY + (1 << PAGE_SHIFT);
    *(unsigned long *) address = 0x55;
    printk(BLUE"%s: [ access 0x%x done ]\n" NONE, __func__, address);
}
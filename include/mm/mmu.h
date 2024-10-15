#ifndef __INCLUDE_MMU_H__

#define __INCLUDE_MMU_H__

void setup_arch(void);
unsigned long alloc_page(void);
void free_page(unsigned long p);
void mem_init(unsigned long start_mem, unsigned long end_mem);

#endif //!__INCLUDE_MMU_H__
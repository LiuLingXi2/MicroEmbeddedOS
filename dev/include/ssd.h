#ifndef __INCLUDE_SSD_H__

#define __INCLUDE_SSD_H__

#include <std/type.h>

#define SSD_SIZE (128 * 1024) // 128KB

#define SSD_BLOCK_SIZE 4096 // block:  4KB

#define MAX_BLOCKS (SSD_SIZE / SSD_BLOCK_SIZE)

#define BITMAP_SIZE     ((MAX_BLOCKS + 7) / 8) // 4B = 32b(32 * Block)


void ssd_init(void);

int allocate_block();
void free_block(int block_num);
int ssd_read_block(int block_num, unsigned char *buffer);
int ssd_write_block(int block_num, const unsigned char *data);

#endif // !__INCLUDE_SSD_H__
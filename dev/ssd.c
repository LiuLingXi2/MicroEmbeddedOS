


#include <ssd.h>
#include <std/printk.h>
#include <std/memset.h>

unsigned char ssd_memory[SSD_SIZE] = {'\0'};

unsigned char block_bitmap[BITMAP_SIZE] = {'\0'};

static void init_block_bitmap(void)
{
    memset(block_bitmap, 0, BITMAP_SIZE);
}

void ssd_init(void)
{
    for (int i = 0; i < SSD_SIZE; i ++) {
        ssd_memory[i] = 0xff;
    }
    init_block_bitmap();

    printk("ssd_memory sram address: 0x%08lx\n", ssd_memory);
    printk("ssd_memory end sram address: 0x%08lx\n", &ssd_memory[SSD_SIZE - 1]); // 0x1FFF
}

static void set_block_allocated(int block_num)
{
    block_bitmap[block_num / 8] |= (1 << (block_num % 8));
}

static void set_block_free(int block_num) {
    block_bitmap[block_num / 8] &= ~(1 << (block_num % 8));
}

int allocate_block()
{
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if ((block_bitmap[i / 8] & (1 << (i % 8))) == 0) {
            block_bitmap[i / 8] |= (1 << (i % 8));
            set_block_allocated(i);
            return i;
        }
    }
    return -1;
}

void free_block(int block_num)
{
    set_block_free(block_num);
}

/**
 * @brief block allocation
 * @param block_num
 * @param buffer
 * 
 * @return int
 */
int ssd_read_block(int block_num, unsigned char *buffer)
{
    if (block_num * SSD_BLOCK_SIZE > SSD_SIZE) {
        printk(RED"%s: read block will exceed limit!\n" NONE, __FUNCTION__);
        return -1;
    }
    for (int i = 0; i < SSD_BLOCK_SIZE; i++) {
        buffer[i] = ssd_memory[block_num * SSD_BLOCK_SIZE + i];
    }
    return 0;
}

/**
 * @brief block write
 */
int ssd_write_block(int block_num, const unsigned char *data)
{
    if (block_num * SSD_BLOCK_SIZE >= SSD_SIZE) {
        printk(RED"%s: write block will exceed limit!\n" NONE, __FUNCTION__);
        return -1;
    }
    
    for (int i = 0; i < SSD_BLOCK_SIZE; i++) {
        ssd_memory[block_num * SSD_BLOCK_SIZE + i] = data[i];
    }
    return 0;
}
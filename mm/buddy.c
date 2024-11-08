// /**
//  * @brief buddy system allocator
//  */

// #include "mm/buddy.h"
// #include "std/type.h"

// typedef struct Block {
//     struct Block *next;
//     int order;
//     int is_free;
// } Block;

// Block *free_list[MAX_ORDER_SIZE + 1];

// void buddy_init(void)
// {
//     int max_block_size = 1 << MAX_ORDER_SIZE;

//     Block* block = (Block*)malloc(max_block_size * sizeof(Block));

//     block->order = MAX_ORDER_SIZE;
//     block->is_free = 1;
//     block->next = NULL;

//     free_list[MAX_ORDER_SIZE] = block;
// }

// Block* get_buddy(Block* block) {
//     size_t buddy_addr = ((size_t)block ^ (1 << block->order));
//     return (Block*)buddy_addr;
// }

// void* buddy_alloc(int order) {
//     if (order > MAX_ORDER_SIZE) {
//         return NULL;
//     }

//     int current_order = order;
//     // find the smallest allocable free linked list
//     while ((current_order <= MAX_ORDER_SIZE) && (free_list[current_order] == NULL)) {
//         current_order++;
//     }

//     if (current_order > MAX_ORDER_SIZE) {
//         return NULL;
//     }

//     Block* block = free_list[current_order];
//     free_list[current_order] = block->next;

//     while (current_order > order) {
//         current_order--;
//         Block* buddy = (Block*)((char*)block + (1 << current_order));

//         buddy->order = current_order;
//         buddy->is_free = 1;
//         buddy->next = free_list[current_order];

//         free_list[current_order] = buddy;
//     }

//     block->order = order;
//     block->is_free = 0;

//     return (void*)block;
// }

// void buddy_free(void* ptr) {
//     Block* block = (Block*)ptr;
//     block->is_free = 1;

//     while (block->order < MAX_ORDER_SIZE) {
//         Block* buddy = get_buddy(block);
//         if (!buddy->is_free || buddy->order != block->order) {
//             break;
//         }

//         Block** prev = &free_list[block->order];
//         while (*prev && *prev != buddy) {
//             prev = &(*prev)->next;
//         }
//         if (*prev) {
//             *prev = buddy->next;
//         }

//         if (block > buddy) {
//             Block* temp = block;
//             block = buddy;
//             buddy = temp;
//         }
//         block->order++;
//     }

//     block->next = free_list[block->order];
//     free_list[block->order] = block;
// }

// void buddy_print() {
//     printf("Buddy System Status:\n");
//     for (int i = 0; i <= MAX_ORDER_SIZE; i++) {
//         printf("Order %d: ", i);
//         Block* current = free_list[i];
//         while (current) {
//             printf("[Block %p, size %d] -> ", current, 1 << i);
//             current = current->next;
//         }
//         printf("NULL\n");
//     }
// }
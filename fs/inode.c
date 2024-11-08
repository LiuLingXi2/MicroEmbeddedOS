// #include "std/type.h"

// typedef struct inode {
//     char name[32];
//     int is_dir;
//     char content[1024];
//     struct inode *parent;
//     struct inode *child;
//     struct inode  *sibling;
// } inode;

// static char *my_strncpy(char *dest, const char *src, size_t n) {
//     size_t i;

//     // 逐字符复制，直到达到 n 或 src 结束
//     for (i = 0; i < n && src[i] != '\0'; i++) {
//         dest[i] = src[i];
//     }

//     // 如果 src 的长度小于 n，用 '\0' 填充 dest 的剩余空间
//     for (; i < n; i++) {
//         dest[i] = '\0';
//     }

//     return dest;
// }

// inode* create_node(const char* name, int is_directory, inode* parent) {
//     inode* node = (inode*)malloc(sizeof(inode));
//    strncpy(node->name, name, 32);
//     node->is_dir = is_directory;
//     node->parent = parent;
//     node->child = NULL;
//     node->sibling = NULL;
//     return node;
// }

// inode* init_fs()
// {
//     return create_node("/", 1, NULL);
// }
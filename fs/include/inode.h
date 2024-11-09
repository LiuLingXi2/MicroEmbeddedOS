#ifndef __INCLUDE_INODE_H__

#define __INCLUDE_INODE_H__

#define MAX_INODE_ENTRIES 16 // a directory has a maximum of 16 files/subdirectories

typedef struct INode{
    int id;
    int size;
    int blocks[10]; // The maximum ssd capacity is 32 blocks. Each inode node allocates a maximum of 10 blocks
    int type;
    char name[32];
    struct INode *entries[MAX_INODE_ENTRIES];
} INode;

int create_inode(int type, const char* name);
int add_inode_to_directory(INode* dir, INode* inode);
INode* find_inode_by_name(INode *parent, const char *name);

#endif // !__INCLUDE_INODE_H__
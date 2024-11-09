#ifndef __INCLUDE_FFS_H__

#define __INCLUDE_FFS_H__

#include "inode.h"

struct file_operation {
    void (*fs_init)(void);
    int  (*sys_create)(INode *parent, const char *name, int type);
    int  (*sys_read)(INode* parent, const char* name);
    int  (*sys_remove)(INode* parent, const char* name);
    int  (*sys_ftruncate)(INode* parent, const char* name);
};

extern struct file_operation global_fs;

void fs_init(void);
void sys_create(INode *parent, const char *name, int type);
void sys_remove(INode* parent, const char* name);

#endif // !__INCLUDE_FFS_H__
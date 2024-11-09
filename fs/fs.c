#include "fs.h"

#include "ext2fs.h"

struct file_operation global_fs = {
    .fs_init = ext2fs_init,
    .sys_create = ext2fs_create,
    .sys_remove = ext2fs_delete,
    .sys_ftruncate = NULL,
    .sys_read = NULL,
};

void fs_init(void)
{
    global_fs.fs_init();
}

void sys_create(INode *parent, const char *name, int type)
{
    global_fs.sys_create(parent, name, type);
}

void sys_remove(INode* parent, const char* name)
{
    global_fs.sys_remove(parent, name);
}
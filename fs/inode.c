#include "std/type.h"
#include "inode.h"
#include "fs.h"
#include "std/string.h"

int create_inode(int type, const char* name)
{
    for (int i = 0; i < MAX_INODES; i++) {
        if (inode_table[i].id == 0) {
            inode_table[i].id = i + 1;
            inode_table[i].size = 0;
            inode_table[i].type = type;
            strncpy(inode_table[i].name, name, 32);
            return i + 1;
        }
    }
    return -1;
}

int add_inode_to_directory(INode* dir, INode* inode)
{
    for (int i = 0; i < MAX_INODE_ENTRIES; i++) {
        if (dir->entries[i] == NULL) {
            dir->entries[i] = inode;
            return 0;
        }
    }
    return -1;
}

INode* find_inode_by_name(INode *parent, const char *name)
{
    if ((parent == NULL) || (name == NULL)) {
        return NULL;
    }

    for (int i = 0; i < MAX_INODE_ENTRIES; i++) {
        INode* entry = parent->entries[i];
        if (entry != NULL && strncmp(entry->name, name, 32) == 0) {
            return entry;
        }
    }

    return NULL;
}
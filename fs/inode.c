#include <std/type.h>
#include <inode.h>
#include <ext2fs.h>
#include <std/string.h>
#include <std/printk.h>

int create_inode(int type, const char* name)
{
    // by default, the 0th inode is not used
    for (int i = 1; i < MAX_INODES; i++) {
        if (inode_table[i].id == 0) {
            inode_table[i].id = i;
            inode_table[i].size = 0;
            inode_table[i].type = type;
            strncpy(inode_table[i].name, name, 32);
            return i;
        }
    }
    return -1;
}

int add_inode_to_directory(INode* dir, INode* inode)
{
    inode->parent = dir;
    
    // There is only one case, the root directory
    if (dir == NULL) {
        printk(RED"%s: parent dir is root?\n" NONE, __FUNCTION__);
        return 0;
    }

    for (int i = 0; i < MAX_INODE_ENTRIES; i++) {
        if (dir->entries[i] == NULL) {
            dir->entries[i] = inode;
            return 0;
        }
    }
    return -1;
}

// todo
INode* find_inode_by_name(const char* name)
{
    for (int i = 0; i < MAX_INODES; i++) {
        if ((inode_table[i].id != 0) && (strcmp(inode_table[i].name, name) == 0)) {
            return &inode_table[i];
        }
    }
    return NULL;
}
#include <ext2fs.h>
#include <ssd.h>
#include <std/memset.h>
#include <std/printk.h>
#include <std/string.h>

SuperBlock superBlock;

INode inode_table[MAX_INODES];

INode *current_inode;

void ls2(void)
{
    for (int i = 0; i < MAX_INODE_ENTRIES; i ++) {
        if (current_inode->entries[i] != NULL) {
            printk("%s\n", current_inode->entries[i]->name);
        }
    }
}

void ext2fs_init(void)
{
    superBlock.total_blocks = MAX_BLOCKS;
    superBlock.total_inodes = MAX_INODES;
    superBlock.free_blocks  = MAX_BLOCKS;
    superBlock.free_inodes  = MAX_INODES;
    // the inode table starts with index 1
    superBlock.inode_table_start = 1;

    // memset(inode_table, 0, INODE_TABLE_SIZE);
    for (int i = 0; i < MAX_INODES; i++) {
        inode_table[i].id = 0;
        inode_table[i].size = 0;
        for (int j = 0; j < 10; j++) {
            inode_table[i].blocks[j] = -1;
        }
        inode_table[i].type = -1;
        inode_table[i].entries[0] = NULL;
        // inode_table[i].name
    }

    printk("\n\n");

    // create root directory
    (void)ext2fs_create(NULL, "/", DIR_T);
    current_inode = find_inode_by_name("/");
    printk("create root dir success:  %s\n", current_inode->name);

    (void)ext2fs_create(current_inode, "home", DIR_T);
    (void)ext2fs_create(current_inode, "tmp", DIR_T);
    (void)ext2fs_create(current_inode, "usr", DIR_T);
    (void)ext2fs_create(current_inode, "var", DIR_T);
    (void)ext2fs_create(current_inode, "root", DIR_T);
    (void)ext2fs_create(current_inode, "boot", DIR_T);
    (void)ext2fs_create(current_inode, "sys", DIR_T);

    ls2();

    // pwd(current_inode);

    printk("fs has initialized!\n");
}

int ext2fs_create(INode *parent, const char *name, int type)
{
    int inode_id = create_inode(type, name);
    if (inode_id == -1) {
        printk(RED "Failed to create inode for file/dir: %s\n" NONE, name);
        return -1;
    }

    INode* new_inode = &inode_table[inode_id];

    if (type == FILE_T) {
        int block_num = allocate_block();
        if (block_num == -1) {
            printk(RED "Failed to allocate block for file: %s\n" NONE, name);
            return -1;
        }
        new_inode->blocks[0] = block_num;
    } else if (type == DIR_T) {
        for (int i = 0; i < MAX_INODE_ENTRIES; i++) {
            new_inode->entries[i] = NULL;
        }
    }

    // adds the created node to the entries array of its parent node
    if (add_inode_to_directory(parent, new_inode) != 0) {
        printk(RED "Failed to add inode to parent directory: %s\n" NONE, name);
        return -1;
    }

    return inode_id;
}

int ext2fs_delete(INode* parent, const char* name)
{
    INode* inode_to_delete = find_inode_by_name(name);
    if (inode_to_delete == NULL) {
        printk(RED "File or directory not found: %s\n" NONE, name);
        return -1;
    }

    for (int i = 0; i < 10; i++) {
        if (inode_to_delete->blocks[i] != -1) {
            free_block(inode_to_delete->blocks[i]);
            inode_to_delete->blocks[i] = -1;
        }
    }

    for (int i = 0; i < MAX_INODE_ENTRIES; i++) {
        if (parent->entries[i] == inode_to_delete) {
            parent->entries[i] = NULL;
            break;
        }
    }

    inode_to_delete->id = 0;
    return 0;
}

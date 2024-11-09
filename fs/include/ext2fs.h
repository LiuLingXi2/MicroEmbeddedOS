#ifndef __INCLUDE_FS_H__

#define __INCLUDE_FS_H__

#include <ssd.h>
#include <inode.h>

#define MAX_INODES 1024

#define INODE_TABLE_SIZE (MAX_INODES * sizeof(INode))

enum INODE_TYPE {
    FILE_T = 0,
    DIR_T = 1 << 0
};

typedef struct {
    // total block count
    int total_blocks;   
    // total inodes  
    int total_inodes;      
    // number of usable blocks 
    int free_blocks;
    // number of available inodes        
    int free_inodes;        
    // location of the inode table
    int inode_table_start;
} SuperBlock;


extern SuperBlock superBlock;
extern INode inode_table[MAX_INODES];

extern INode *current_inode;

void ext2fs_init(void);

int ext2fs_create(INode *parent, const char *name, int type);
int ext2fs_delete(INode* parent, const char* name);

#endif // !__INCLUDE_FS_H__
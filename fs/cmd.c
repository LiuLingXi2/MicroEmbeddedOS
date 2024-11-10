#include <shell.h>
#include <cmd.h>
#include <fs.h>
#include <ext2fs.h>
#include <std/string.h>
#include <std/printk.h>
#include <asm/msyscall.h>

static char full_path[32] = {"\0"};

char arg[10] = {"\0"};

static void pwd(void)
{
	char cur_path[32] = {"\0"};
	char tmp_path[32] = {"\0"};
    while (current_inode != NULL) {
        if (current_inode->parent != NULL) {
            strcpy(tmp_path, "/");
            strcat(tmp_path, current_inode->name);
			strcat(tmp_path, cur_path);
			strcpy(cur_path, tmp_path);
        } else { // root
			strcat(tmp_path, "/");
			break;
		}
        current_inode = current_inode->parent;
    }
	printk("%s\n", tmp_path);
}

static void ls(void)
{
    for (int i = 0; i < MAX_INODE_ENTRIES; i ++) {
        if (current_inode->entries[i] != NULL) {
            if (current_inode->entries[i]->type == DIR_T) {
                printk("%s/ ", current_inode->entries[i]->name);
            } else {
                printk("%s ", current_inode->entries[i]->name);
            }
        }
    }
    printk("\n");
}

static void mkdir(void)
{
    (void)sys_create(current_inode, arg, DIR_T);
}

static void user_chdir(void)
{
    for (int i = 0; i < MAX_INODE_ENTRIES; i ++) {
        if (current_inode->entries[i] != NULL) {
            if (strcmp(arg, current_inode->entries[i]->name) == 0) {
                current_inode = current_inode->entries[i];
            }
        }
    }
}

static void touch(void)
{

}

struct cmd_t built_in_cmds[] = {
    {.cmd_str = "pwd", .cmd_func = pwd},
    {.cmd_str = "ls", .cmd_func = ls},
    {.cmd_str = "mkdir", .cmd_func = mkdir},
    {.cmd_str = "cd", .cmd_func = user_chdir},
    {.cmd_str = "touch", .cmd_func = touch},
};
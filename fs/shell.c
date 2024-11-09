#include <shell.h>
#include <ext2fs.h>
#include <std/type.h>
#include <std/string.h>
#include <std/printk.h>

char full_path[32] = {"\0"};

struct cmd_t {
    char cmd_str[10];
    void (*cmd_func)(void);
};

void pwd(void)
{
    // while (inode != NULL) {
    //     if (inode->parent != NULL) {
    //         char tmp_path[32];
    //         strcpy(tmp_path, "/");
    //         strcat(tmp_path, inode->name);
    //         strcat(full_path, tmp_path);
    //     } else { // root
	// 		strcpy(full_path, "/");
	// 		break;
	// 	}
    //     inode = inode->parent;
    // }
    printk("asdasd\n");
}

void ls(void)
{
    for (int i = 0; i < MAX_INODE_ENTRIES; i ++) {
        if (current_inode->entries[i] != NULL) {
            printk("%s\n", current_inode->entries[i]->name);
        }
    }
}

struct cmd_t built_in_cmds[] = {
    {.cmd_str = "pwd", .cmd_func = pwd},
    {.cmd_str = "ls", .cmd_func = ls},
};

char *my_strtok(char *str, const char *delim) {
    static char *s = NULL;
    char *start;

    if (str != NULL) {
        s = str;
    }

    if (s == NULL) {
        return NULL;
    }

    while (*s != '\0') {
        int is_delim = 0;
        for (int i = 0; delim[i] != '\0'; i++) {
            if (*s == delim[i]) {
                is_delim = 1;
                break;
            }
        }
        if (is_delim) {
            s++; 
        } else {
            break;
        }
    }

    if (*s == '\0') {
        s = NULL;
        return NULL;
    }

    start = s;

    while (*s != '\0') {
        int is_delim = 0;
        for (int i = 0; delim[i] != '\0'; i++) {
            if (*s == delim[i]) {
                is_delim = 1;
                break;
            }
        }
        if (is_delim) {
            *s = '\0';
            s++;
            break;
        } else {
            s++;
        }
    }

    return start;
}

int split(char *input, char *args[]) 
{
    int i = 0;
    char *token = my_strtok(input, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = my_strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    return i;
}

void parse_command(char *cmd)
{
    for (int i = 0; i < 2; i++) {
        if (strcmp(cmd, built_in_cmds[i].cmd_str) == 0) {
            built_in_cmds[i].cmd_func(); // call
        }
    }
    return ;
}
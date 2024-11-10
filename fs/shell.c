#include <shell.h>
#include <ext2fs.h>
#include <fs.h>
#include <cmd.h>
#include <std/type.h>
#include <std/string.h>
#include <std/printk.h>


static char *tmp_strtok(char *str, const char *delim) {
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

int split_cmd(char *input, char *args[]) 
{
    int i = 0;
    char *token = tmp_strtok(input, " \t");
    while (token != NULL) {
        args[i++] = token;
        strcpy(arg, token);
        token = tmp_strtok(NULL, " \t");
    }
    args[i] = NULL;
    return i;
}

void parse_command(char *cmd)
{
    for (int i = 0; i < 4; i++) {
        if (strcmp(cmd, built_in_cmds[i].cmd_str) == 0) {
            built_in_cmds[i].cmd_func(); // call
            return ;
        }
    }
    printk("unrecognized command\n");
    return ;
}
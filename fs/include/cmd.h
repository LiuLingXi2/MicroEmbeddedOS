#ifndef __INCLUDE_CMD_H__

#define __INCLUDE_CMD_H__

struct cmd_t {
    char cmd_str[10];
    void (*cmd_func)(void);
};

extern char arg[10];

extern struct cmd_t built_in_cmds[];

#endif // !__INCLUDE_CMD_H__
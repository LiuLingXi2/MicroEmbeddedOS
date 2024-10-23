#ifndef __INCLUDE_SCHE_H__

#define __INCLUDE_SCHE_H__

#include "mm/mm.h"

#define THREAD_SIZE  (1 * PAGE_SIZE)

#define __init_task_data __attribute__((__section__(".data.init_task")))

enum task_state {
    TASK_RUNNING = 0,
    TASK_INTERRUPTIBLE = 1,
    TASK_UNINTERRUPTIBLE = 2,
    TASK_ZOMBIE = 3,
    TASK_STOPPED = 4,
};

enum task_flags {
    PF_KTHREAD = 1 << 0,
};

struct proc_context {
	unsigned long x19;
	unsigned long x20;
	unsigned long x21;
	unsigned long x22;
	unsigned long x23;
	unsigned long x24;
	unsigned long x25;
	unsigned long x26;
	unsigned long x27;
	unsigned long x28;
	unsigned long fp;
	unsigned long sp;
	unsigned long pc;
};

struct task_struct {
	enum task_state state;
	enum task_flags flags;
	long count;
	int priority;
	int pid;
	struct proc_context cpu_context;
};

union task_union {
	struct task_struct task;
	unsigned long stack[THREAD_SIZE/sizeof(long)];
};

#define INIT_TASK(task) \
{                      \
	.state = 0,     \
	.priority = 1,   \
	.flags = PF_KTHREAD,   \
	.pid = 0,     \
}

union task_union init_task_union __init_task_data = {INIT_TASK(task)};

#endif //!__INCLUDE_SCHE_H__
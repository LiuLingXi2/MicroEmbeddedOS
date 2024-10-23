#include "asm/sche.h"
#include "mm/mmu.h"
#include "std/printk.h"

#define NR_TASK 128

// 定义一个全局PCB
struct task_struct *g_pcb[NR_TASK] = {
    &init_task_union.task,
};

static int find_empty_task(void)
{
	int i;

	for (i = 0 ; i < NR_TASK; i++) {
		if (!g_pcb[i])
			return i;
	}

	return -1;
}

int do_fork(unsigned long flags, unsigned long fn, unsigned long args)
{
    struct task_struct *ts;
    int pid;

    ts = (struct task_struct *)alloc_page();
    if (!ts) {
        printk(RED"%s: Failing to Alloc Memory!\n" NONE, __FUNCTION__);
        goto error;
    }
    pid = find_empty_task();
    if (pid < 0) {
        printk(RED"%s: Failing to Alloc Pid!\n" NONE, __FUNCTION__);
        goto error;
    }

    ts->state = TASK_RUNNING;
    ts->pid = pid;
    g_pcb[pid] = ts;

    return pid;
error:
    return -1;
}

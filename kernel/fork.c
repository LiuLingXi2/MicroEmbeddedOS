#include "proc/sche.h"
#include "mm/mmu.h"
#include "std/printk.h"
#include "irq.h"
#include "std/memset.h"
#include "asm/system.h"

#define NR_TASK 128

// global PCB
struct task_struct *g_pcb[NR_TASK] = {
    &init_task_union.task,
};

// static struct task_struct *current = &init_task_union.task;

static int find_empty_task(void)
{
	int i;

	for (i = 0 ; i < NR_TASK; i++) {
		if (!g_pcb[i])
			return i;
	}

	return -1;
}

static struct pt_regs *task_pt_regs(struct task_struct *tsk)
{
	unsigned long p;

    /**
     * function calling stack
     * the stack grows from high to low
     * size: 4KB
     */
	p = (unsigned long)tsk + THREAD_SIZE - sizeof(struct pt_regs);

	return (struct pt_regs *)p;
}

static int copy_thread(unsigned long flags, unsigned long fn, unsigned long args, struct task_struct *p)
{
    struct pt_regs *child_regs;

    child_regs = task_pt_regs(p);

    memset(child_regs,  0, sizeof(struct pt_regs));
    memset(&p->cpu_context, 0, sizeof(struct cpu_context));

    if (flags && PF_KTHREAD) {
        child_regs->pstate = PSR_MODE_EL1h;
        p->cpu_context.x19 = fn;
        p->cpu_context.x20 = args;
    }
    
    p->cpu_context.pc = (unsigned long)ret_from_fork;
    p->cpu_context.sp = (unsigned long)child_regs;
    return 0;
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

    if (copy_thread(flags, fn, args, ts)) {
        goto error;
    }

    ts->state = TASK_RUNNING;
    ts->pid = pid;
    g_pcb[pid] = ts;

    return pid;
error:
    return -1;
}

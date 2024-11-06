#ifndef __INCLUDE_SCHE_H__

#define __INCLUDE_SCHE_H__

#include "mm/mm.h"
#include "proc/list.h"
#include "proc/queue.h"

#define THREAD_SIZE  (1 * PAGE_SIZE)
#define THREAD_START_SP (THREAD_SIZE - 8)

#define DEF_COUNTER (250 / 10)  /* 100ms time slice */

#define __init_task_data __attribute__((__section__(".data.init_task")))

enum task_state {
	TASK_INIT_STATUS = 0,
    TASK_READY = TASK_INIT_STATUS,
	TASK_RUNNING,
    TASK_BLOCK,
    TASK_ZOMBIE,
    TASK_STOPPED,
};

enum task_flags {
    PF_KTHREAD = 1 << 0,
};

struct cpu_context {
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
	int pid;
	struct cpu_context cpu_context;
	struct list_head run_list;
	int counter;
	int priority;
	int need_resched;
	int preempt_count;
	struct task_struct *next_task;
	struct task_struct *prev_task;
};

union task_union {
	struct task_struct task;
	unsigned long stack[THREAD_SIZE/sizeof(long)]; // 内核栈 底部存储用户态到内核态的寄存器
};

#define INIT_TASK(task) \
{                      \
	.state = TASK_READY,     \
	.priority = 20,   \
	.counter = DEF_COUNTER, \
	.flags = PF_KTHREAD,   \
	.pid = 0,     \
	.preempt_count = 0, \
	.need_resched = 1, \
	.next_task = NULL, \
	.prev_task = NULL, \
}

// union task_union init_task_union __init_task_data = {INIT_TASK(init_task_union.task)};
extern union task_union init_task_union;


struct sched_class {
	const struct sched_class *next;

	void (*task_fork)(struct task_struct *p);
	void (*enqueue_task)(struct run_queue *rq, struct task_struct *p);
	void (*dequeue_task)(struct run_queue *rq, struct task_struct *p);
	void (*task_tick)(struct run_queue *rq, struct task_struct *p);
	struct task_struct * (*pick_next_task)(struct run_queue *rq,
			struct task_struct *prev);
};

#define init_task (init_task_union.task)

#define for_each_task(p) \
	for (p = &init_task; (p = p->next_task) != &init_task; )

extern const struct sched_class kernel_sched_class;

register unsigned long current_stack_pointer asm ("sp");

static inline struct task_struct *get_current(void)
{
	return (struct task_struct *)
		(current_stack_pointer & ~(THREAD_SIZE - 1));
}

#define current get_current()

#define preempt_count() (current->preempt_count)

#define in_atomic_preempt_off() \
	(preempt_count() != 1)

#define need_resched() (current->need_resched == 1)

#define SET_LINKS(p) do { \
	(p)->next_task = &init_task; \
	(p)->prev_task = init_task.prev_task; \
	init_task.prev_task->next_task = (p); \
	init_task.prev_task = (p); \
	} while (0)

void sched_init(void);
void schedule(void);
void exit(int n);
struct task_struct * switch_to(struct task_struct *prev, struct task_struct *next);

void dequeue_task(struct run_queue *rq, struct task_struct *p);

extern void ret_from_fork(void);
extern struct task_struct *cpu_switch_to(struct task_struct *prev, struct task_struct *next);
void wake_up_process(struct task_struct *p);
int do_fork(unsigned long flags, unsigned long fn, unsigned long args, int pri);

extern struct run_queue g_rq;

#endif //!__INCLUDE_SCHE_H__
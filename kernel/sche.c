#include "proc/sche.h"
#include "proc/queue.h"
#include "std/printk.h"
#include "irq.h"

struct run_queue g_rq;

union task_union init_task_union __init_task_data = {INIT_TASK(init_task_union.task)};

static struct task_struct *ret_task;

struct task_struct *pick_next_task(struct run_queue *rq,
		struct task_struct *prev)
{
	const struct sched_class *class = &kernel_sched_class;

	return class->pick_next_task(rq, prev);
}

void dequeue_task(struct run_queue *rq, struct task_struct *p)
{
	const struct sched_class *class = &kernel_sched_class;

	return class->dequeue_task(rq, p);
}

void enqueue_task(struct run_queue *rq, struct task_struct *p)
{
	const struct sched_class *class = &kernel_sched_class;

	return class->enqueue_task(rq, p);
}

void task_tick(struct run_queue *rq, struct task_struct *p)
{
	const struct sched_class *class = &kernel_sched_class;

	return class->task_tick(rq, p);
}

struct task_struct * switch_to(struct task_struct *prev, struct task_struct *next)
{
	if (prev == next) {
		return NULL;
	}
	return cpu_switch_to(prev, next);
}

void schedule_tail(struct task_struct *prev)
{
	raw_local_irq_enable();
}

void tick_handle_periodic(void)
{
	struct run_queue *rq = &g_rq;

	task_tick(rq, current);
}

static void schedule_debug(struct task_struct *p)
{
	if (in_atomic_preempt_off())
		printk("BUG: scheduling while atomic: %d, 0x%x\n",
				p->pid, preempt_count());
}

static void clear_task_resched(struct task_struct *p)
{
	p->need_resched = 0;
}

static void __schedule(void)
{
	struct task_struct *prev, *next, *last;
	struct run_queue *rq = &g_rq;
	prev = current;
	ret_task = prev;

	schedule_debug(prev);

	// raw_local_irq_disable(); // cli

	// place the current process in the ready queue
	if (prev->state == TASK_RUNNING) {
		prev->state = TASK_READY;
		enqueue_task(rq, prev);
	}
	// select the next process to run
	next = pick_next_task(rq, prev);
	// clears some states of the current process
	clear_task_resched(prev);
	if (next != prev) {
		rq->nr_switches++;
		rq->curr = current;
		// next->priority = 1;
		last = switch_to(prev, next); // ?
	}
	printk("yesyes\n");
	// schedule_tail(last); //sti
}

static void preempt_disable(void)
{
	current->preempt_count++;
}

static void preempt_enable(void)
{
	current->preempt_count--;
}

void schedule(void)
{
	preempt_disable();
	__schedule();
	preempt_enable();
}

void preempt_schedule_irq(void)
{
	/* this must be preemptible now*/
	if (preempt_count())
		printk("BUG: %s incorrect preempt count: 0x%x\n",
				__func__, preempt_count());
	printk("test\n");
	preempt_disable();

	// raw_local_irq_enable();
	__schedule();
	// raw_local_irq_disable();
	preempt_enable();
}

void wake_up_process(struct task_struct *p)
{
	struct run_queue *rq = &g_rq;

	p->state = TASK_READY;

	enqueue_task(rq, p);
}

void sched_init(void)
{
	struct run_queue *rq = &g_rq;

	INIT_LIST_HEAD(&rq->rq_head);
	rq->nr_running = 0;
	rq->nr_switches = 0;
	rq->curr = NULL;
}

/**
 * @brief actively exit, set it to TASK_STOPPED, and schedule it again
 */
void exit(int n)
{
	current->state = TASK_STOPPED;
	schedule();
}
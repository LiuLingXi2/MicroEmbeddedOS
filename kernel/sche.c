#include "proc/sche.h"
#include "proc/queue.h"
#include "std/printk.h"
#include "irq.h"

struct run_queue g_rq;

union task_union init_task_union __init_task_data = {INIT_TASK(init_task_union.task)};

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
	if (prev == next)
		return NULL;

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

	schedule_debug(prev);

	raw_local_irq_disable(); // cli

	if (prev->state == TASK_RUNNING) {
		dequeue_task(rq, prev);
    }

	next = pick_next_task(rq, prev);
	clear_task_resched(prev);
	if (next != prev) {
		last = switch_to(prev, next);
		rq->nr_switches++;
		rq->curr = current;
	}

	schedule_tail(last);
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

	preempt_disable();

	raw_local_irq_enable();
	__schedule();
	raw_local_irq_disable();
	preempt_enable();
}

void wake_up_process(struct task_struct *p)
{
	struct run_queue *rq = &g_rq;

	p->state = TASK_RUNNING;

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

#include <proc/sche.h>
#include <proc/queue.h>
#include <std/printk.h>
#include <irq.h>

static void dequeue_task_kernel(struct run_queue *rq, struct task_struct *p)
{
	rq->nr_running--;
	list_del(&p->run_list);
}

static void enqueue_task_kernel(struct run_queue *rq, struct task_struct *p)
{
	list_add(&p->run_list, &rq->rq_head);
	rq->nr_running++;
	// printk("nr_running: %d\n", g_rq.nr_running);
}

static int goodness(struct task_struct *p)
{
	int weight;

	weight = p->priority;

	return weight;
}

static void reset_score(void)
{
	struct task_struct *p;

	for_each_task(p) {
		p->counter = DEF_COUNTER + p->priority;
		printk("%s, pid=%d, count=%d\n", __func__, p->pid, p->counter);
	}
}

/**
 * @brief the priority scheduling policy is adopted
 */
static struct task_struct *pick_next_task_kernel(struct run_queue *rq, struct task_struct *prev)
{
	struct task_struct *p, *next;
	struct list_head *tmp;
	int weight;
	int c;

	if (rq->nr_running == 0U) {
		// printk("idle-----------\n");
		return &init_task_union.task;
	}
repeat:
	c = -1;
	list_for_each(tmp, &rq->rq_head) {
		p = list_entry(tmp, struct task_struct, run_list);
		weight = goodness(p);
		if (weight > c) {
			c = weight;
			next = p;
		}
	}

	// if (!c) { // all clock end
	// 	reset_score();
	// 	goto repeat;
	// }

	// remove from the ready queue
	dequeue_task(&g_rq, next);
	next->state = TASK_RUNNING;

	printk("%s: pick next thread (pid %d)\n", __func__, next->pid);

	return next;
}

static void task_tick_kernel(struct run_queue *rq, struct task_struct *p)
{
	if (--p->counter <= 0) { // clock end
		p->counter = 0;
		p->need_resched = 1; // sched
		printk("pid %d need_resched\n", p->pid);
	}
}

const struct sched_class kernel_sched_class = {
	.next = NULL,
	.dequeue_task = dequeue_task_kernel,
	.enqueue_task = enqueue_task_kernel,
	.task_tick = task_tick_kernel,
	.pick_next_task = pick_next_task_kernel,
};
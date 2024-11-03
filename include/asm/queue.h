#ifndef __INCLUDE_ASM_QUEUE_H__

#define __INCLUDE_ASM_QUEUE_H__

#include "sche.h"
#include "std/type.h"
#include "list.h"

struct run_queue {
	struct list_head rq_head;
	unsigned int nr_running;
	u64 nr_switches;
	struct task_struct *curr;
};

#endif // !__INCLUDE_ASM_QUEUE_H__
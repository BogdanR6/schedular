#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>
#include "task.h"

struct rq {
    unsigned int        nr_running;
    struct task_struct  *curr; // current task running in the rq
		struct task_struct	*head; // head of the task_struct linked list
    struct task_struct  *idle; // task to use when nothing else is to run
    uint64_t            rq_clock;
};

struct sched_class {
    void (*enqueue_task)(struct rq *rq, struct task_struct *p);

    struct task_struct *(*pick_next_task)(struct rq *rq, struct task_struct *prev);

    void (*put_prev_task)(struct rq *rq, struct task_struct *p);
};

#endif // SCHEDULER_H_

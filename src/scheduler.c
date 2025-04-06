#include <stdio.h>
#include <stdlib.h>
#include "../include/scheduler.h"

struct rq* init_runqueue() {
	struct rq* new_rq = (struct rq*)malloc(sizeof(struct rq));
	if (!new_rq) {
		perror("Failed to allocate runqueue");
		exit(1);
	}
	
	new_rq->nr_running = 0;
	new_rq->curr = NULL;
	new_rq->head = NULL;
	new_rq->idle = NULL;
	new_rq->rq_clock = 0;
	
	return new_rq;
}

void enqueue_task(struct rq *rq, struct task_struct *p) {
	if (!rq || !p) return;

	p->next = NULL;
	
	// If queue is empty
	if (rq->nr_running == 0) {
		rq->curr = p;
		rq->head = p;
	} else {
		p->next = rq->head;
		rq->head = p;
	}
	
	rq->nr_running++;
	printf("Task %d added to runqueue (duration: %d)\n", p->id, p->duration);
}

struct task_struct* pick_next_task(struct rq *rq, struct task_struct *prev) {
	if (!rq || rq->nr_running == 0) {
		rq->curr = rq->idle;  // Return idle task if no tasks are running
		return rq->curr;
	}
	
	// If no previous task, return the first task
	if (!prev || prev->next == NULL) {
		rq->curr = rq->head;
	} else
		rq->curr = prev->next;

	return rq->curr;
}

void put_prev_task(struct rq *rq, struct task_struct *p) {
	if (!rq || !p) return;
	
	p->duration--;
	
	// If task is complete, remove it from the queue
	if (p->duration <= 0) {
		printf("Task %d completed\n", p->id);
		
		// only one task in the queue
		if (rq->nr_running == 1) {
			free(rq->curr);
			rq->curr = NULL;
			rq->head = NULL;
		} else {
			struct task_struct *prev = rq->head;
			while (prev->next != NULL && prev->next != p) {
				prev = prev->next;
			}

			if (prev->next == NULL) {
				rq->head = rq->head->next;
			} else {
				prev->next = p->next;
			}

			rq->curr = prev;
			free(p);
		}
		
		rq->nr_running--;
	}
}

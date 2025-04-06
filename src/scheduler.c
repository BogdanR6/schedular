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
	new_rq->idle = NULL;
	new_rq->clock = 0;
	
	return new_rq;
}

// (circular linked list)
void enqueue_task(struct rq *rq, struct task_struct *p) {
	if (!rq || !p) return;

	p->next = NULL;
	
	// If queue is empty
	if (rq->nr_running == 0) {
		rq->curr = p;
		rq->tail = p;
		p->next = p;  // create circular list
	} else {
		struct task_struct *last = rq->tail;
		p->next = last->next;  
		last->next = p;      
	}
	
	rq->nr_running++;
	printf("Task %d added to runqueue (duration: %d)\n", p->id, p->duration);
}

struct task_struct* pick_next_task(struct rq *rq, struct task_struct *prev) {
	if (!rq || rq->nr_running == 0) {
		return rq->idle;  // Return idle task if no tasks are running
	}
	
	// If no previous task, return the first task
	if (!prev) {
		return rq->tail->next;
	}
	
	return prev->next;
}

void put_prev_task(struct rq *rq, struct task_struct *p) {
	if (!rq || !p) return;
	
	p->duration--;
	
	// If task is complete, remove it from the queue
	if (p->duration <= 0) {
		printf("Task %d completed\n", p->id);
		
		// only one task in the queue
		if (rq->nr_running == 1) {
			// free(rq->curr);
			rq->curr = NULL;
		} else {
			struct task_struct *prev = rq->tail;
			while (prev->next != p) {
				prev = prev->next;
			}
			prev->next = p->next;
			// free(p);
		}
		
		rq->nr_running--;
	}
}

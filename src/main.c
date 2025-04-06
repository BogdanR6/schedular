#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/task.h"
#include "../include/scheduler.h"

void start_task_scheduling_simulation();
struct rq* init_runqueue();
void enqueue_task(struct rq *rq, struct task_struct *p);
struct task_struct* pick_next_task(struct rq *rq, struct task_struct *prev);
void put_prev_task(struct rq *rq, struct task_struct *p);


void start_task_scheduling_simulation() {
    // get the mock processes 
    FILE *input_file = fopen("input", "r");
    if (input_file == NULL) {
        perror("Can't open input file\n");
        exit(1);
    }
    
    struct rq *runqueue = init_runqueue();
    char *task_data = NULL;
    size_t size = 0;
    ssize_t nread;
    
    while((nread = getline(&task_data, &size, input_file)) != -1) {
        int pid;
        int duration;
        if (sscanf(task_data, "%d %d", &pid, &duration) != 2) {
            printf("Fatal: Format of input is wrong!\n");
            free(task_data);
            fclose(input_file);
            exit(1);
        }
        
        struct task_struct *task = (struct task_struct *)malloc(sizeof(struct task_struct));
        task->id = pid;
        task->duration = duration;
				task->next = NULL;
				enqueue_task(runqueue, task);
    }
    
    free(task_data);
    fclose(input_file);
    
    
    // run the scheduler simulation
    printf("\nStarting Round Robin scheduling simulation...\n");
    printf("------------------------------------------------\n");
    
    // define time quantum for round robin
    const int time_quantum = 1;
    
    while (runqueue->nr_running > 0) {
        struct task_struct *current = pick_next_task(runqueue, runqueue->curr);
        runqueue->curr = current;
        
        // Simulate task execution for one time quantum
        printf("Time %lu: Running task %d (remaining time: %d)\n", 
               runqueue->rq_clock, current->id, current->duration);
        
        runqueue->rq_clock += time_quantum;
        
        // Mark task as having run, update its state
        put_prev_task(runqueue, current);
    }
    
    printf("------------------------------------------------\n");
    printf("All tasks completed at time %lu\n", runqueue->rq_clock);
    
    free(runqueue); // the tasks are freed once they are complete 
    
    return;
}


int main() {
    start_task_scheduling_simulation();
    return 0;
}

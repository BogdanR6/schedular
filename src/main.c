#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/task.h"


void start_task_scheduling_simulation() {
	

	// get the mock processes 
	FILE *input_file = fopen("input", "r");
	if (input_file == NULL) {
		perror("Can't open input file\n");
		exit(1);
	}
	struct task_struct **task_arr = (struct task_struct **)malloc(100 * sizeof(struct task_struct *));
	size_t ta_size = 0;

	char *task_data = NULL;
	size_t size = 0;
	ssize_t nread;
	while((nread = getline(&task_data, &size, input_file)) != -1) {
		int pid;
		int duration;

		if (sscanf(task_data, "%d %d", &pid, &duration) != 2) {
			printf("Fatal: Foramt of input is wrong!\n");
			free(task_data);
			fclose(input_file);
			exit(1);
		}
		struct task_struct *task = (struct task_struct *)malloc(sizeof(struct task_struct));
		task->id = pid;
		task->duration = duration;
		task_arr[ta_size++] = task;

	}
	free(task_data);
	fclose(input_file);


	// give the processes to the sheduler
	
	// free the task_arr
	for (int i = 0; i < ta_size; ++i) {
		free(task_arr[i]);
	}
	free(task_arr);
	return;
}

int main() {
	start_task_scheduling_simulation();
	return 0;
}

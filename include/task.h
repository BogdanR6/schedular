#ifndef TASK_H_
#define TASK_H_

struct task_struct {
    int id;
    int duration; // time that the task will take in quantums
    struct task_struct *next;
};

#endif // TASK_H_

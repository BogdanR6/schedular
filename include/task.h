#ifndef TASK_H_
#define TASK_H_

#include <setjmp.h>

struct task_struct {
    int id;
    int duration; // time that the task will take in quantums
};

#endif // TASK_H_

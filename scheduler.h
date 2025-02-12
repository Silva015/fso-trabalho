#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include <stdint.h>

typedef enum
{
    SCHED_FIFO,
    SCHED_SJF,
    SCHED_RR
} sched_policy_t;

extern sched_policy_t current_policy;
extern int next_sch_pid, curr_sch_pid;
extern process_t *next_process;

void scheduler_init();
void set_scheduling_policy(sched_policy_t policy);
process_t *get_next_process();
void scheduler(uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t);
void run_next_process();

#endif

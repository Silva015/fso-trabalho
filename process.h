#ifndef PROCESS_H
#define PROCESS_H

typedef enum process_state
{
    READY,
    RUNNING,
    TERMINATED
} process_state_t;

typedef struct process_context
{
    int eax, ecx, edx, ebx, esp, ebp, esi, edi, eip;
} process_context_t;

typedef struct process
{
    int pid;
    process_context_t context;
    process_state_t state;
    int *base_address;
    int burst_time;
    int remaining_time;
} process_t;

extern process_t *processes[15];
extern int process_count, curr_pid;

void process_init();
process_t *create_process(int *base_address, int burst_time);

#endif

#include "process.h"
#include "heap.h"

process_t *processes[15];
int process_count = 0;
int curr_pid = 0;

void process_init()
{
    process_count = 0;
    curr_pid = 0;
}

process_t *create_process(int *base_address, int burst_time)
{
    // kalloc retorna um "ponteiro" mockado (na verdade um int convertido para ponteiro)
    process_t *process = (process_t *)kalloc(sizeof(process_t));

    process->pid = curr_pid++;

    process->context.eax = 0;
    process->context.ebx = 0;
    process->context.ecx = 0;
    process->context.edx = 0;
    process->context.esp = 0;
    process->context.ebp = 0;
    process->context.esi = 0;
    process->context.edi = 0;
    process->context.eip = (int)base_address;

    process->state = READY;
    process->base_address = base_address;
    process->burst_time = burst_time;
    process->remaining_time = burst_time;

    processes[process->pid] = process;
    ++process_count;

    return process;
}

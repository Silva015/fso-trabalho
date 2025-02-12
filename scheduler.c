#include "scheduler.h"
#include "screen.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

sched_policy_t current_policy = SCHED_RR;
int next_sch_pid = 0;
int curr_sch_pid = 0;
process_t *next_process = NULL;
int time_quantum = 4;
int rr_quantum_counter = 0; // Contador global para o quantum do Round Robin

void scheduler_init()
{
    next_sch_pid = 0;
    curr_sch_pid = 0;
    rr_quantum_counter = 0;
}

// Implementação da função que define a política de escalonamento
void set_scheduling_policy(sched_policy_t policy)
{
    current_policy = policy;
    rr_quantum_counter = 0; // Reinicia o contador de quantum
}

process_t *get_next_process()
{
    process_t *next = NULL;
    int i;

    switch (current_policy)
    {
    case SCHED_RR:
        // Se o processo atual ainda está em execução e o quantum não foi atingido, continua
        if (processes[curr_sch_pid] != NULL &&
            processes[curr_sch_pid]->state == RUNNING &&
            rr_quantum_counter < time_quantum)
        {
            rr_quantum_counter++;
            next = processes[curr_sch_pid];
        }
        else
        {
            // Reinicia o contador e busca o próximo processo disponível
            rr_quantum_counter = 1; // reinicia para contar o tick atual
            for (i = 1; i <= process_count; i++)
            {
                int idx = (curr_sch_pid + i) % process_count;
                if (processes[idx]->state != TERMINATED)
                {
                    next = processes[idx];
                    break;
                }
            }
            // Se nenhum processo não terminado for encontrado, mantém o atual
            if (next == NULL)
            {
                next = processes[curr_sch_pid];
            }
        }
        break;

    case SCHED_FIFO:
        for (i = 0; i < process_count; i++)
        {
            if (processes[i]->state != TERMINATED)
            {
                next = processes[i];
                break;
            }
        }
        break;

    case SCHED_SJF:
    {
        int shortest = -1;
        for (i = 0; i < process_count; i++)
        {
            if (processes[i]->state == TERMINATED)
                continue;

            // Se o processo já está rodando, mantém-o
            if (processes[i]->state == RUNNING)
            {
                next = processes[i];
                break;
            }

            if (shortest == -1 ||
                processes[i]->remaining_time < processes[shortest]->remaining_time)
            {
                shortest = i;
            }
        }
        if (next == NULL && shortest != -1)
        {
            next = processes[shortest];
        }
    }
    break;
    }

    // Fallback: se nenhum processo foi encontrado ou o escolhido está terminado, procura o primeiro processo ativo
    if (next == NULL || next->state == TERMINATED)
    {
        for (i = 0; i < process_count; i++)
        {
            if (processes[i]->state != TERMINATED)
            {
                next = processes[i];
                break;
            }
        }
    }

    if (next != NULL)
        curr_sch_pid = next->pid;

    return next;
}

void scheduler(uintptr_t eip, uintptr_t edi, uintptr_t esi, uintptr_t ebp, uintptr_t esp, uintptr_t ebx,
               uintptr_t edx, uintptr_t ecx, uintptr_t eax)
{
    process_t *curr_process = processes[curr_sch_pid];

    if (curr_process && curr_process->state == RUNNING)
    {
        // Salva o contexto do processo atual
        curr_process->context.eax = eax;
        curr_process->context.ebx = ebx;
        curr_process->context.ecx = ecx;
        curr_process->context.edx = edx;
        curr_process->context.esp = esp;
        curr_process->context.ebp = ebp;
        curr_process->context.esi = esi;
        curr_process->context.edi = edi;
        curr_process->context.eip = eip;

        // Simula a execução do processo: decrementa o tempo restante
        curr_process->remaining_time--;
        if (curr_process->remaining_time <= 0)
        {
            curr_process->state = TERMINATED;
            print("Process ");
            printi(curr_process->pid);
            print(" finished!");
            println();
        }
    }

    process_t *next_proc = get_next_process();
    if (!next_proc || next_proc->state == TERMINATED)
    {
        // Nenhum processo disponível
        print("No available process to schedule.\n");
        return;
    }

    // Se houver troca de contexto, atualiza os estados
    if (curr_process != next_proc)
    {
        if (curr_process && curr_process->state != TERMINATED)
            curr_process->state = READY;
        next_proc->state = RUNNING;
        curr_sch_pid = next_proc->pid;
    }

    next_process = next_proc;

    // Simula a troca de contexto (o código em assembly foi removido)
    print("Context switch to process ");
    printi(next_process->pid);
    println();
}

void run_next_process()
{
    // Simula a execução do próximo processo
    print("Running process ");
    printi(next_process->pid);
    println();
}

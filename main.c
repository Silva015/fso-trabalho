#include <stdio.h>
#include <stdbool.h>
#include "process.h"
#include "scheduler.h"
#include "screen.h" // Mock
#include "heap.h"   // Mock
#include <stdint.h>

// Função para permitir a adição interativa de processos
void add_processes()
{
    char choice;
    int burst;
    // Limite máximo de processos definido em process.h (ou em heap.h, MAX_PROCESSES)
    while (process_count < MAX_PROCESSES)
    {
        printf("Deseja adicionar um novo processo? (S/N): ");
        scanf(" %c", &choice);
        if (choice == 'S' || choice == 's')
        {
            printf("Digite o burst time do processo: ");
            scanf("%d", &burst);
            // Gera um valor "mock" para base_address:
            // Por exemplo, 0x1000 + (process_count * 0x1000)
            int *base_addr = (int *)((uintptr_t)0x1000 + process_count * 0x1000);
            create_process(base_addr, burst);
        }
        else
        {
            break;
        }
    }
}

// Função para escolher a política de escalonamento
void choose_policy()
{
    int op;
    printf("\nEscolha a política de escalonamento:\n");
    printf("1 - FIFO\n");
    printf("2 - SJF\n");
    printf("3 - RR\n");
    printf("Digite sua escolha: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        set_scheduling_policy(SCHED_FIFO);
        break;
    case 2:
        set_scheduling_policy(SCHED_SJF);
        break;
    case 3:
        set_scheduling_policy(SCHED_RR);
        break;
    default:
        printf("Opção inválida. Usando SCHED_FIFO como padrão.\n");
        set_scheduling_policy(SCHED_FIFO);
        break;
    }
}

// Função que executa o scheduler até que todos os processos estejam finalizados
void run_scheduler_until_completion()
{
    int tick = 0;
    while (true)
    {
        scheduler(0, 0, 0, 0, 0, 0, 0, 0, 0); // Chamada mockada do scheduler
        run_next_process();
        printf("Tick %d\n", tick);
        tick++;

        // Verifica se todos os processos foram finalizados
        bool allTerminated = true;
        for (int i = 0; i < process_count; i++)
        {
            if (processes[i]->state != TERMINATED)
            {
                allTerminated = false;
                break;
            }
        }
        if (allTerminated)
        {
            printf("Todos os processos foram finalizados.\n");
            break;
        }
    }
}

int main()
{
    screen_init();  // Inicializa o mock da tela
    heap_init();    // Inicializa o mock da heap
    process_init(); // Inicializa a estrutura dos processos

    add_processes();
    if (process_count == 0)
    {
        printf("Nenhum processo foi adicionado. Encerrando.\n");
        return 0;
    }
    choose_policy();
    run_scheduler_until_completion();
    return 0;
}

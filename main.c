#include "process.h"
#include "scheduler.h"
#include "screen.h" // Mock
#include "heap.h"   // Mock

void mock_processes()
{
    heap_init(); // Inicializa o mock da heap
    process_init();

    // Cria processos mockados: base_address (apenas um valor mock) e burst_time
    create_process((int *)0x1000, 5); // PID 0, burst 5
    create_process((int *)0x2000, 3); // PID 1, burst 3
    create_process((int *)0x3000, 8); // PID 2, burst 8
}

void test_scheduler()
{
    // Para testar, altere a política para SCHED_SJF, SCHED_FIFO ou SCHED_RR
    set_scheduling_policy(SCHED_SJF); // Exemplo: testando SJF

    // Simula ticks do relógio
    for (int i = 0; i < 10; i++)
    {
        scheduler(0, 0, 0, 0, 0, 0, 0, 0, 0); // Chamada mockada do scheduler
        run_next_process();
        print("Tick ");
        printi(i);
        println();
    }
}

int main()
{
    screen_init(); // Inicializa o mock da tela
    mock_processes();
    test_scheduler();
    return 0;
}

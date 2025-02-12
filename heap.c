#include "heap.h"
#include "process.h" // Necessário para usar sizeof(process_t)

#define MAX_PROCESSES 15
#define PROCESS_SIZE sizeof(process_t) // Garante o tamanho correto para cada processo

static unsigned char mock_heap[MAX_PROCESSES * PROCESS_SIZE]; // Heap simulada
static int heap_index = 0;

void heap_init()
{
    heap_index = 0;
}

int kalloc(int bytes)
{
    if (heap_index + bytes > sizeof(mock_heap))
    {
        return -1; // Simula falha na alocação
    }
    int allocated_index = heap_index;
    heap_index += bytes;
    return (int)&mock_heap[allocated_index]; // Retorna um ponteiro mockado
}

#include "heap.h"
#include "process.h" // Necessário para usar sizeof(process_t)
#include <stddef.h>  // Necessário para definir NULL

#define MAX_PROCESSES 15
#define PROCESS_SIZE sizeof(process_t) // Garante o tamanho correto para cada processo

static unsigned char mock_heap[MAX_PROCESSES * PROCESS_SIZE]; // Heap simulada
static int heap_index = 0;

void heap_init()
{
    heap_index = 0;
}

void *kalloc(int bytes)
{
    if (heap_index + bytes > sizeof(mock_heap))
    {
        return NULL; // Simula falha na alocação
    }
    int allocated_index = heap_index;
    heap_index += bytes;
    return (void *)&mock_heap[allocated_index]; // Retorna um ponteiro mockado
}

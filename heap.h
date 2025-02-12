#ifndef HEAP_H
#define HEAP_H

#define MAX_PROCESSES 15

// Simula a alocação de memória usando um array estático
void heap_init();
void *kalloc(int bytes); // Retorna um ponteiro no array estático

#endif

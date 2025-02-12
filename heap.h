#ifndef HEAP_H
#define HEAP_H

#define MAX_PROCESSES 15

// Simula a alocação de memória usando um array estático
void heap_init();
int kalloc(int bytes); // Retorna um "ponteiro" (na verdade um inteiro) no array estático

#endif

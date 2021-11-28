#include "deque.h"


void deque_create(Deque *deque, uint32_t size, uint32_t start)
{
    deque->stack = malloc(size * sizeof(int32_t));
    deque->size  = size;
    deque->index = start;
    memset(deque->stack, 0, size * sizeof(int32_t));
}

void deque_free(Deque *deque)
{
    free(deque->stack);
}

void deque_next(Deque *deque)
{
    deque->index++;
}

void deque_prev(Deque *deque)
{
    deque->index--;
}

int32_t *deque_get(Deque *deque)
{
    return deque->stack+deque->index;
}

void deque_print(Deque *deque)
{
    printf("\n");
    for (uint32_t i=0; i < deque->size; i++) {
        printf("%d ", *(deque->stack+i));
    }
    printf("\n");
}


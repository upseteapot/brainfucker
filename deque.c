#include "deque.h"


void deque_create(Deque *deque, uint32_t size)
{
    deque->stack = malloc(size * sizeof(uint32_t));
    deque->size  = size;
    deque->index = size / 2;
    memset(deque->stack, 0, size * sizeof(uint32_t));
}

void deque_free(Deque *deque)
{
    free(deque->stack);
}

void deque_front(Deque *deque)
{
    if (++deque->index == deque->size) {
        deque->stack = realloc(deque->stack, deque->size * 2 * sizeof(uint32_t));
        memset(deque->stack + deque->size, 0, deque->size * sizeof(uint32_t));
        deque->size *= 2;
    }
}

void deque_back(Deque *deque)
{
    if (deque->index == 0) {
        deque->stack = realloc(deque->stack, deque->size * 2 * sizeof(uint32_t));
        memmove(deque->stack + deque->size, deque->stack, deque->size * sizeof(uint32_t));
        memset(deque->stack, 0, deque->size * sizeof(uint32_t));
        deque->index = deque->size - 1;
        deque->size *= 2;
    } else {
        deque->index--;
    }
}

uint32_t *deque_get(Deque *deque)
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


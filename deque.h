#ifndef __DEQUE
#define __DEQUE

#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

typedef struct
{
    uint32_t *stack;
    uint32_t size;
    uint32_t index;
} Deque;

void      deque_create(Deque *, uint32_t);
void      deque_free(Deque *);
void      deque_front(Deque *);
void      deque_back(Deque *);
uint32_t *deque_get(Deque *);
void      deque_print(Deque *);

#endif


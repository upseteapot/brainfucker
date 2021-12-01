#ifndef __DEQUE
#define __DEQUE

#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

typedef struct
{
    int32_t *stack;
    uint32_t size;
    uint32_t index;
} Deque;

void      deque_create(Deque *, uint32_t, uint32_t);
void      deque_free(Deque *);
void      deque_next(Deque *);
void      deque_prev(Deque *);
int32_t  *deque_get(Deque *);
void      deque_print(Deque *);

#endif


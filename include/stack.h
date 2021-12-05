#ifndef __ARRAY
#define __ARRAY

#include "stdint.h"
#include "stdlib.h"

typedef struct 
{
  size_t *data;
  size_t  size;
  size_t  current;
} IndexStack;

void   idxstack_create(IndexStack *stack, size_t size);
void   idxstack_free(IndexStack *stack);
size_t idxstack_pop(IndexStack *stack);
size_t idxstack_get_last(IndexStack *stack);
void   idxstack_push(IndexStack *stack, size_t index);

#endif 


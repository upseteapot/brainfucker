#include "stack.h"


void idxstack_create(IndexStack *stack, size_t size)
{
  stack->data    = malloc(size * sizeof(size_t));
  stack->size    = size;
  stack->current = 0;
}

void idxstack_free(IndexStack *stack)
{
  free(stack->data);
}

size_t idxstack_pop(IndexStack *stack)
{
  return stack->data[--stack->current]; 
}

size_t idxstack_get_last(IndexStack *stack)
{
  return stack->data[stack->current - 1];
}

void idxstack_push(IndexStack *stack, size_t index)
{
  if (stack->current == stack->size) {
    stack->size *= 2;
    stack->data  = realloc(stack->data, stack->size * sizeof(size_t));
  } 
  stack->data[stack->current++] = index;
}


#include "stack.h"


void stack_create(Stack *stack, uint32_t size)
{
  stack->data    = malloc(size * sizeof(uint32_t));
  stack->size    = size;
  stack->current = 0;
}

void stack_free(Stack *stack)
{
  free(stack->data);
}

uint32_t stack_pop(Stack *stack)
{
  return stack->data[--stack->current]; 
}

uint32_t stack_get_last(Stack *stack)
{
  return stack->data[stack->current - 1];
}

void stack_push(Stack *stack, uint32_t index)
{
  if (stack->current == stack->size) {
    stack->size *= 2;
    stack->data  = realloc(stack->data, stack->size * sizeof(uint32_t));
  } 
  stack->data[stack->current++] = index;
}


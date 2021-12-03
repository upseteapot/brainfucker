#ifndef __ARRAY
#define __ARRAY
#include "stdint.h"
#include "stdlib.h"


typedef struct 
{
  uint32_t *data;
  uint32_t  size;
  uint32_t  current;
} Stack;

void     stack_create(Stack *stack, uint32_t size);
void     stack_free(Stack *stack);
uint32_t stack_pop(Stack *stack);
uint32_t stack_get_last(Stack *stack);
void     stack_push(Stack *stack, uint32_t index);


#endif 


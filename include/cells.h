#ifndef __CELLS
#define __CELLS

#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

typedef struct
{
  int32_t *buffer;
  uint32_t size;
  uint32_t index;
} Deque;

void      cells_create(Deque *, uint32_t, uint32_t);
void      cells_free(Deque *);
void      cells_next(Deque *);
void      cells_prev(Deque *);
int32_t  *cells_get(Deque *);
void      cells_print(Deque *);

#endif


#ifndef __CELLS
#define __CELLS

#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

typedef struct
{
  int32_t *buffer;
  size_t size;
  size_t index;
} Cells;

void      cells_create(Cells *, size_t, size_t);
void      cells_free(Cells *);
void      cells_next(Cells *);
void      cells_prev(Cells *);
int32_t  *cells_get(Cells *);
int32_t  *cells_get_at(Cells *, size_t index);
void      cells_print(Cells *);

#endif


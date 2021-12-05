#include "cells.h"


void cells_create(Cells *cells, size_t size, size_t start)
{
  cells->buffer = (int32_t *)malloc(size * sizeof(int32_t));
  cells->size  = size;
  cells->index = start;
  memset(cells->buffer, 0, size * sizeof(int32_t));
}

void cells_free(Cells *cells)
{
  free(cells->buffer);
}

void cells_next(Cells *cells)
{
  cells->index++;
}

void cells_prev(Cells *cells)
{
  cells->index--;
}

int32_t *cells_get(Cells *cells)
{
  return cells->buffer+cells->index;
}

void cells_print(Cells *cells)
{
  printf("\n");
  for (size_t i=0; i < cells->size; i++) {
    printf("%d ", *(cells->buffer+i));
  }
  printf("\n");
}


#include "cells.h"


void cells_create(Deque *cells, uint32_t size, uint32_t start)
{
    cells->buffer = (int32_t *)malloc(size * sizeof(int32_t));
    cells->size  = size;
    cells->index = start;
    memset(cells->buffer, 0, size * sizeof(int32_t));
}

void cells_free(Deque *cells)
{
    free(cells->buffer);
}

void cells_next(Deque *cells)
{
    cells->index++;
}

void cells_prev(Deque *cells)
{
    cells->index--;
}

int32_t *cells_get(Deque *cells)
{
    return cells->buffer+cells->index;
}

void cells_print(Deque *cells)
{
    printf("\n");
    for (uint32_t i=0; i < cells->size; i++) {
        printf("%d ", *(cells->buffer+i));
    }
    printf("\n");
}


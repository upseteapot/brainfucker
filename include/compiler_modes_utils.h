#ifndef __COMPILER_MODES_UTILS
#define __COMPILER_MODES_UTILS

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "cells.h"
#include "stack.h"

char *format_file(const char *file_path);
int interpret_code(const char *formatted_file, Cells *cells);
void get_cells_info(char *formatted_file, size_t *size, size_t *start);
int generate_assembly(char *file_name, char *formatted_file, size_t size, size_t start);
int run_echoed_command(char *command);
int execute_commands(char *name, char *exe_name); 

#endif


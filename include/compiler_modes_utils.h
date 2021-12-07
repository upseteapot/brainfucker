#ifndef __COMPILER_MODES_UTILS
#define __COMPILER_MODES_UTILS

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "cells.h"
#include "stack.h"

char *format_file(const char *);
int interpret_code(const char *, Cells *);
int generate_assembly(char *, char *, size_t, size_t);
int run_echoed_command(char *);
int execute_commands(char *, char *); 

#endif


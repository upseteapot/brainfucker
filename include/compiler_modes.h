#ifndef __COMPILER_MODES
#define __COMPILER_MODES

#include "compiler_modes_utils.h"

int simulate(char *file);
int format(char *file, char *output);
int assemble(char *file, char *output);
int compile(char *file, char *output);

#endif


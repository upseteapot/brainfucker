#include "compiler_modes.h"


int simulate(char *file)
{
  printf("[NOTE]: Formatting '%s'.\n", file);
  char *formatted_file = format_file(file);
  if (formatted_file == NULL) {
    printf("[NOTE]: Formatation failed.\n");
    return -1;
  }
  printf("[NOTE]: Interpreting code.\n");
  Cells cells;
  cells_create(&cells, 2048, 2048 / 2);
  if (interpret_code(formatted_file, &cells)) {
    printf("[NOTE]: Interpretation failed.\n");
    cells_free(&cells);
    free(formatted_file);
    return -1;
  }
  printf("\n[NOTE]: Exiting.\n");
  cells_free(&cells);
  free(formatted_file);
  return 0;
}

int format(char *file, char *output) 
{
  printf("[NOTE]: Formatting '%s'.\n", file);
  char *formatted_file = format_file(file);
  if (formatted_file == NULL) {
    printf("[NOTE]: Formatation failed.\n");
    return -1;
  }
  FILE *new_file = fopen(output, "w");
  if (new_file == NULL) {
    printf("[NOTE]: Could not open '%s'.\n", output); 
    return -1;
  }
  fprintf(new_file, formatted_file);
  fclose(new_file);
  free(formatted_file);
  return 0;
}

int assemble(char *file, char *output)
{    
  printf("[NOTE]: Formatting '%s'.\n", file);
  char *formatted_file = format_file(file);
  if (formatted_file == NULL) {
    printf("[NOTE]: Formatation failed.\n");
    return -1;
  }
  printf("[NOTE]: Generating assembly code to '%s'.\n", output);
  if (generate_assembly(output, formatted_file, 2048, 2048 / 2) == -1) {
    printf("[NOTE]: Assembly generation failed.\n");
    return -1;
  }
  free(formatted_file);
  return 0;
}

int compile(char *file, char *output)
{
  printf("[NOTE]: Formatting '%s'.\n", file);
  char *formatted_file = format_file(file);
  if (formatted_file == NULL) {
    printf("[NOTE]: Formatation failed.\n");
    return -1;
  }
  char *asm_file = malloc(strlen(file) + 5);
  sprintf(asm_file, "%s.asm", file);
  printf("[NOTE]: Generating assembly code to '%s'.\n", asm_file);
  if (generate_assembly(asm_file, formatted_file, 2048, 2048 / 2) == -1) {
    printf("[NOTE]: Assembly generation failed.\n");
    return -1;

  }
  char *wildcard_index = strchr(file, '.');
  size_t name_size = wildcard_index - file;
  char *name = malloc(name_size + 1);
  memcpy(name, file, name_size);
  name[name_size] = '\0';
  if (execute_commands(name, output) == -1) {
    return -1;
  }
  free(name);    
  free(asm_file);
  return 0;
}


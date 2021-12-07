#include "compiler_modes.h"


void print_usage()
{
  printf("./brainfucker [mode] [files]\n");
  printf("               sim    file\n");
  printf("               com    file  output\n");
  printf("               asm    file  output\n");
  printf("               for    file  output\n");
}

void assert_argc(char *mode, int argc, int expected)
{
  if (argc - 2 != expected) {
    fprintf(stderr, "[ERROR]: '%s' expects %d argument(s). %d provided.\n", mode, expected, argc - 2);
    exit(EXIT_FAILURE);
  }
}

void assert_mode(char *mode, int callback)
{
  if (callback < 0) {
    fprintf(stderr, "[ERROR]: '%s' failed.\n", mode);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char **argv)
{
  if (argc == 1) {
    fprintf(stderr, "[ERROR]: Please provide a mode.\n");
    return -1;
  } else {
    if (strcmp(argv[1], "sim") == 0) {
      assert_argc("sim", argc, 1);
      assert_mode("sim", simulate(argv[2]));
    } 

    else if (strcmp(argv[1], "com") == 0) {
      assert_argc("com", argc, 2);
      assert_mode("com", compile(argv[2], argv[3]));
    } 

    else if (strcmp(argv[1], "asm") == 0) {
      assert_argc("asm", argc, 2);
      assert_mode("asm", assemble(argv[2], argv[3]));
    } 

    else if (strcmp(argv[1], "for") == 0) {
      assert_argc("for", argc, 2);
      assert_mode("for", format(argv[2], argv[3]));
    }
    else {
      fprintf(stderr, "[ERROR]: Unknow mode '%s'.\n", argv[1]);
      return -1;
    }
  }
  return 0;
}


#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "deque.h"


char *format_file(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Could not open '%s'.\n", file_path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    uint32_t size = ftell(file);
    char *formatted_file = malloc(size + 1);
    rewind(file);
    int delete = 0;
    uint32_t index = 0;
    char current;
    while ((current = fgetc(file)) != EOF) {
        if (current == '#') {
            delete = 1;
        } else if (current == '\n') {
            delete = 0;
        } else if (!delete && current != ' ') {
            formatted_file[index++] = current;
        }
    }
    formatted_file[size] = '\0';
    fclose(file);
    return formatted_file;
}

int interpret_code(const char *formatted_file, Deque *deque)
{
    uint32_t *current;
    uint32_t loop_start;
    for (uint32_t i=0; i < strlen(formatted_file); i++) {
        switch (formatted_file[i]) {
            case '+':
                current = deque_get(deque);
                (*current)++;
                break;
            case '-':
                current = deque_get(deque);
                (*current)--;
                break;
            case '>':
                deque_front(deque);
                break;
            case '<':
                deque_back(deque);
                break;
            case '.':
                printf("%c", *deque_get(deque));
                break;
            case '[':
                loop_start = i;
                break;
            case ']':
                if (*deque_get(deque) != 0) { 
                    i = loop_start;
                }
                break;
            case ',':
                *deque_get(deque) = fgetc(stdin);
                break;
            default:
                printf("Unknow instruction '%c'.\n", formatted_file[i]);
                return -1;
                break;
        }
    }
    return 0;
}


void print_usage()
{
    printf("./brainfucker [mode] [files]          [options]\n");
    printf("               sim    file             -d (initial deque size)\n");
    printf("               com    file\n");
    printf("               for    file  new_file\n");
}

int simulate(int argc, char **argv)
{
    printf("Formating '%s'.\n", argv[2]);
    char *formatted_file = format_file(argv[2]);
    if (formatted_file == NULL) {
        printf("Formatation failed.\n");
        return -1;
    }
    printf("Interpreting code.\n");
    Deque deque;
    deque_create(&deque, 5);
    if (interpret_code(formatted_file, &deque)) {
        printf("Interpretation failed.\n");
        deque_free(&deque);
        free(formatted_file);
        return -1;
    }
    printf("\nExiting.\n");
    deque_free(&deque);
    free(formatted_file);
    return 0;
}

int format(int argc, char **argv) 
{
    printf("Formating '%s'.\n", argv[2]);
    char *formatted_file = format_file(argv[2]);
    if (formatted_file == NULL) {
        printf("Formatation failed.\n");
        return -1;
    }
    FILE *new_file = fopen(argv[3], "w");
    if (new_file == NULL) {
        printf("Could not open '%s'.\n", argv[3]); 
        return -1;
    }
    fprintf(new_file, formatted_file);
    fclose(new_file);
    return 0;
}


// TODO: Implement a better input system
int main(int argc, char **argv)
{
    if (strcmp(argv[1], "sim") == 0) {
        if (simulate(argc, argv) == -1) {
            fprintf(stderr, "[ERROR]: Simulation failed.\n");
            return -1;
        }
    } 
    else if (strcmp(argv[1], "for") == 0) {
        if (format(argc, argv) == -1) {
            fprintf(stderr, "[ERROR]: Formatation failed.\n");
            return -1;
        }
    }
    else if (strcmp(argv[1], "--help") == 0) {
        print_usage();
    }
    else {
        fprintf(stderr, "[ERROR]: Unknow command '%s'\n", argv[1]);
        print_usage();
        return -1;
    }
    return 0;
}


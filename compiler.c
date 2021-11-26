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
    printf("%d\n", size);
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
        } else if (!delete) {
            formatted_file[index++] = current;
        }
    }
    formatted_file[size] = '\0';
    fclose(file);
    return formatted_file;
}

int simulate(const char *formatted_file)
{
    Deque deque;
    deque_create(&deque, 5);
    uint32_t *current;
    uint32_t loop_start;
    for (uint32_t i=0; i < strlen(formatted_file); i++) {
        switch (formatted_file[i]) {
            case '+':
                current = deque_get(&deque);
                (*current)++;
                break;
            case '-':
                current = deque_get(&deque);
                (*current)--;
                break;
            case '>':
                deque_front(&deque);
                break;
            case '<':
                deque_back(&deque);
                break;
            case '.':
                printf("%c", *deque_get(&deque));
                break;
            case '[':
                loop_start = i;
                break;
            case ']':
                if (*deque_get(&deque) != 0) { 
                    i = loop_start;
                }
                break;
            case ',':
                *deque_get(&deque) = fgetc(stdin);
                break;
            default:
                printf("Unknow instruction '%c'.\n", formatted_file[i]);
                deque_free(&deque);
                return -1;
                break;
        }
    }
    deque_free(&deque);
    return 0;
}

void print_usage()
{
    
}


int main(int argc, char **argv)
{
    if (argc != 3) { 
        fprintf(stderr, "[ERROR]: Wrong number of arguments provided.\n");
        print_usage();
        return -1;
    } else {
        if (strcmp(argv[1], "sim") == 0) {
            char *formatted_file = format_file(argv[2]);
            if (formatted_file == NULL) {
                fprintf(stderr, "[ERROR]: Formatting the file failed.\n");
                return -1;
            }
            printf("%s\n", formatted_file);
            if (simulate(formatted_file)) {
                fprintf(stderr, "Simulation failed.");
                return -1;
            }
            free(formatted_file);
        } else if (strcmp(argv[1], "com") == 0) {
            fprintf(stderr, "[ERROR]: Compilation not implemented.\n");
            return -1;
        } else {
            fprintf(stderr, "[ERROR]: Unknow command '%s'\n", argv[1]);
            print_usage();
            return -1;
        }
    }

    return 0;
}


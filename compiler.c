#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "deque.h"


char *format_file(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("[NOTE]: Could not open '%s'.\n", file_path);
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
    int32_t *current;
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
                deque_next(deque);
                break;
            case '<':
                deque_prev(deque);
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
                printf("[NOTE]: Unknow instruction '%c'.\n", formatted_file[i]);
                return -1;
                break;
        }
    }
    return 0;
}

void get_deque_info(char *formatted_file, uint32_t *size, uint32_t *start)
{
    int32_t current = 0;
    int32_t max     = 0;
    int32_t min     = 0;
    for (uint32_t i=0; i < strlen(formatted_file); i++) {
        if (formatted_file[i] == '>') {
            current++;
            if (current > max) {
                max = current;
            }
        } else if (formatted_file[i] == '<') {
            current--;
            if (current < min) {
                min = current;
            }
        }
    }
    *size = max - min + 1;
    *start = -min;
}

int generate_assembly(char *file_name, char *formatted_file, uint32_t size, uint32_t start)
{
    FILE *file = fopen(strcat(file_name, ".asm"), "w");
    if (file == NULL) {
        printf("[NOTE]: Could not create '%s'.\n", strcat(file_name, ".asm"));
        return -1;
    }
    fprintf(file, "section .data\n");
    fprintf(file, "  x dd 0\n");
    fprintf(file, "  buffer times %d dd 0\n", size);
    fprintf(file, "section .text\n");
    fprintf(file, "  global _start\n");
    fprintf(file, "_printecx:\n");
    fprintf(file, "  mov [x], ecx\n");
    fprintf(file, "  mov rax, 1\n");
    fprintf(file, "  mov rdi, 1\n");
    fprintf(file, "  mov rsi, x\n");
    fprintf(file, "  mov rdx, 1\n");
    fprintf(file, "  syscall\n");
    fprintf(file, "  ret\n");
    fprintf(file, "_start:\n");
    int32_t sum = 0;
    int32_t index = start;
    uint32_t loop_count = 0;
    char prev_char = ' ';
    char curr_char = ' ';
    for (uint32_t i=0; i < strlen(formatted_file); i++) {
        curr_char = formatted_file[i];
        if ((prev_char == '+' || prev_char == '-') &&
            (curr_char != '+' && curr_char != '-')) {
            if (sum > 0) {
                fprintf(file, "  add dword buffer[%d], %d\n", index, sum);
            } else if (sum < 0) {
                fprintf(file, "  sub dword buffer[%d], %d\n", index, -sum);
            }
            sum = 0;
        }
        switch (curr_char) {
            case '+':
                sum++;
                break;
            case '-':
                sum--;
                break;
            case '>':
                index++;
                break;
            case '<':
                index--;
                break;
            case '.':
                fprintf(file, "  mov ecx, dword buffer[%d]\n", index);
                fprintf(file, "  call _printecx\n");
                break;
            case '[':
                loop_count++;
                fprintf(file, "loop%d:\n", loop_count);
                break;
            case ']':
                fprintf(file, "  cmp dword buffer[%d], 0\n", index);
                fprintf(file, "  jne loop%d\n", loop_count);
                break;
            case ',':
                break;
            default:
                printf("[NOTE]: Unknow instruction '%c'.\n", formatted_file[i]);
                return -1;
                break;
        }
        prev_char = curr_char;
    }
    fprintf(file, "  mov rax, 60\n");
    fprintf(file, "  mov rdi, 0\n");
    fprintf(file, "  syscall\n");
    return 0;
}


void print_usage()
{
    printf("./brainfucker [mode] [files]          [options]\n");
    printf("               sim    file             -d (initial deque size)\n");
    printf("               for    file  new_file\n");
    printf("               asm    file\n");
    printf("               com    file  output\n");
}

int simulate(int argc, char **argv)
{
    printf("[NOTE]: Formatting '%s'.\n", argv[2]);
    char *formatted_file = format_file(argv[2]);
    if (formatted_file == NULL) {
        printf("[NOTE]: Formatation failed.\n");
        return -1;
    }
    printf("[NOTE]: Interpreting code.\n");
    uint32_t size, start;
    get_deque_info(formatted_file, &size, &start);
    Deque deque;
    deque_create(&deque, size, start);
    if (interpret_code(formatted_file, &deque)) {
        printf("[NOTE]: Interpretation failed.\n");
        deque_free(&deque);
        free(formatted_file);
        return -1;
    }
    printf("\n[NOTE]: Exiting.\n");
    deque_free(&deque);
    free(formatted_file);
    return 0;
}

int format(int argc, char **argv) 
{
    printf("[NOTE]: Formatting '%s'.\n", argv[2]);
    char *formatted_file = format_file(argv[2]);
    if (formatted_file == NULL) {
        printf("[NOTE]: Formatation failed.\n");
        return -1;
    }
    FILE *new_file = fopen(argv[3], "w");
    if (new_file == NULL) {
        printf("[NOTE]: Could not open '%s'.\n", argv[3]); 
        return -1;
    }
    fprintf(new_file, formatted_file);
    fclose(new_file);
    return 0;
}

int assemble(int argc, char **argv)
{    
    printf("[NOTE]: Formatting '%s'.\n", argv[2]);
    char *formatted_file = format_file(argv[2]);
    if (formatted_file == NULL) {
        printf("[NOTE]: Formatation failed.\n");
        return -1;
    }
    uint32_t size, start;
    get_deque_info(formatted_file, &size, &start);
    printf("[NOTE]: Generating assembly code to '%s.asm'.\n", argv[2]);
    if (generate_assembly(argv[2], formatted_file, size, start) == -1) {
        printf("[NOTE]: Assembly generation failed.\n");
        return -1;
    }
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
    
    else if (strcmp(argv[1], "asm") == 0) {
        if (assemble(argc, argv) == -1) {
            fprintf(stderr, "[ERROR]: Assembling process failed.\n");
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


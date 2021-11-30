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
    char *formatted_file = (char *)malloc(size + 1);
    rewind(file);
    int delete_flag = 0;
    uint32_t index = 0;
    char current;
    while ((current = fgetc(file)) != EOF) {
        if (current == '#') {
            delete_flag = 1;
        } else if (current == '\n') {
            delete_flag = 0;
        } else if (!delete_flag && current != ' ') {
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
    char *new_file_name = (char *)malloc(strlen(file_name) + 5);
    sprintf(new_file_name, "%s.asm", file_name);
    FILE *file = fopen(new_file_name, "w");
    if (file == NULL) {
        printf("[NOTE]: Could not create '%s'.\n", strcat(file_name, ".asm"));
        return -1;
    }
    fprintf(file, "section .data\n");
    fprintf(file, "  current db 0\n");
    fprintf(file, "  input times 2 db 0\n");
    fprintf(file, "  buffer times %d dd 0\n", size);
    fprintf(file, "section .text\n");
    fprintf(file, "  global _start\n");
    fprintf(file, "_input:\n");
    fprintf(file, "  mov rax, 0\n");
    fprintf(file, "  mov rdi, 0\n");
    fprintf(file, "  mov rsi, input\n");
    fprintf(file, "  mov rdx, 2\n");
    fprintf(file, "  syscall\n");
    fprintf(file, "  mov cl, input[0]\n");
    fprintf(file, "  ret\n");
    fprintf(file, "_print:\n");
    fprintf(file, "  mov [current], cl\n");
    fprintf(file, "  mov rax, 1\n");
    fprintf(file, "  mov rdi, 1\n");
    fprintf(file, "  mov rsi, current\n");
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
                fprintf(file, "  mov cl, byte buffer[%d]\n", index);
                fprintf(file, "  call _print\n");
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
                fprintf(file, "  call _input\n");
                fprintf(file, "  mov byte buffer[%d], cl\n", index);
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
    fclose(file);
    free(new_file_name);
    return 0;
}

int run_echoed_command(char *command)
{
    printf("[NOTE]: %s\n", command);
    return system(command);
}

int execute_commands(char *name, char *exe_name) 
{
    char *nasm_command = malloc(27 + 2 * strlen(name) + 1);
    char *ld_command = malloc(11 + 2 * strlen(name) + 1);
    char *clean_command = malloc(20 + 2 * strlen(name) + 1);
    sprintf(nasm_command, "nasm -felf64 -o %s.b.o %s.b.asm", name, name);
    sprintf(ld_command, "ld -o %s %s.b.o", exe_name, name);
    sprintf(clean_command, "rm %s.b.asm && rm %s.b.o", name, name);
    if (run_echoed_command(nasm_command) != 0) {
        printf("[NOTE]: Failed to summon 'nasm'.\n");
        return -1;
    }
    if (run_echoed_command(ld_command) != 0) {
        printf("[NOTE]: Failed to summon 'ld'.\n");
        return -1;
    }
    if (run_echoed_command(clean_command) != 0) {
        printf("[NOTE]: Failed to remove build files.\n");
        return -1;
    }
    free(nasm_command);
    free(ld_command);
    free(clean_command);
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
    free(formatted_file);
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
    free(formatted_file);
    return 0;
}

int compile(int argc, char **argv)
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
    char *wildcard_index = strchr(argv[2], '.');
    size_t name_size = wildcard_index - argv[2];
    char *name = malloc(name_size + 1);
    memcpy(name, argv[2], name_size);
    name[name_size] = '\0';
    if (execute_commands(name, argv[3]) == -1) {
        return -1;
    }
    free(name);    
    return 0;
}


// TODO: Implement a better input system
// TODO: Check if provided is input is one byte long
// TODO: Refactor / clean code
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
    
    else if (strcmp(argv[1], "com") == 0) {
        if (compile(argc, argv) == -1) {
            fprintf(stderr, "[ERROR]: Compilation failed.\n");
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


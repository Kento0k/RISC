#ifndef RISC_RISCEMULATORLIBRARY_H
#define RISC_RISCEMULATORLIBRARY_H

// C default library
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>

//instruction structure
struct instruction;
typedef struct instruction instruction;

//Еrror processing functions
void error_processing(int code);

//File parsing functions
int parse_file(FILE *in, char *name, int *args);
void text_parameters(FILE* in, int *maxPC, int *num_of_commands);
//Writing program to memory
void memory_write(int memory[65536][16], instruction command);

//program execution
void exec_program(FILE *in, FILE *out, int reg[8][16], int memory[4096][16]);

//program_debugging
void debug_program(FILE *in, FILE *out, int reg[8][16], int memory[4096][16]);
//operations
void run_instruction(int reg[8][16], int memory[4096][16], int *PC);
#endif //RISC_RISCEMULATORLIBRARY_H

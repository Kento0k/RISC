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


//program execution
void exec_program(FILE *in, int *reg, int *memory);

//operations
void run_instruction(instruction step, int*reg, int*memory);
#endif //RISC_RISCEMULATORLIBRARY_H

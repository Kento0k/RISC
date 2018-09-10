#ifndef RISC_RISCEMULATORLIBRARY_H
#define RISC_RISCEMULATORLIBRARY_H

// C default library
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
//Еrror processing functions
void error_processing(int code);

//File parsing functions
void parse_file(FILE *in);


//instruction structure
struct instruction;
#endif //RISC_RISCEMULATORLIBRARY_H

#include"RISCEmulatorLibrary.h"
#include"instruction.c"
void exec_program(FILE *in, int *reg, int *memory){
    int maxPC=0, num_of_commands=0, command_count=0;
    text_parameters(in, &maxPC, &num_of_commands);
    printf("max adress=%d num of commands=%d\n", maxPC, num_of_commands);
    instruction *program= (instruction*)malloc(num_of_commands * sizeof(instruction));
    for(int i=0; i<=maxPC; i++){
        parse_file(in, program[command_count]);
        run_instruction(program[command_count], reg, memory);
    }
}


#include"RISCEmulatorLibrary.h"
#include"instruction.c"
void exec_program(FILE *in, int *reg, int *memory){
    int maxPC=0, num_of_commands=0, command_count=0;
    text_parameters(in, &maxPC, &num_of_commands);
    printf("max adress=%d num of commands=%d\n", maxPC, num_of_commands);
    instruction *program= (instruction*)malloc(num_of_commands * sizeof(instruction));
    for(int i=0; i<=maxPC; i++){
        parse_file(in, program[command_count].name, program[command_count].args);
        //printf("%d %d %d\n", program[command_count].args[0], program[command_count].args[1], program[command_count].args[2]);
        run_instruction(program[command_count], reg, memory);
        for(int z=0; z<8;z++) {
            printf("register[%d]= %d ", z, reg[z]);
            printf("\n");
        }
        command_count++;
    }
}


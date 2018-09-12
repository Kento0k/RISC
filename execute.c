#include"RISCEmulatorLibrary.h"
#include"instruction.c"
void exec_program(FILE *in, FILE *out, int *reg, int *memory){
    int maxPC=0, num_of_commands=0, command_count=0, PC[1];
    PC[0]=0;
    text_parameters(in, &maxPC, &num_of_commands);
    printf("max adress=%d num of commands=%d\n", maxPC, num_of_commands);
    instruction *program= (instruction*)malloc(num_of_commands * sizeof(instruction));
    int flag[num_of_commands];
    for(int i=0; i<=maxPC; i++) {
        flag[i]= parse_file(in, program[command_count].name, program[command_count].args);
        printf("flag= %d\n", flag[i]);
        if(flag[i]==1)
            program[command_count].adress=i;
        command_count++;
    }
       while(PC[0]<=maxPC) {
           printf("PC= %d\n", PC[0]);
           if(flag[PC[0]]!=0) {
               //printf("%d %d %d\n", program[PC[0]].args[0], program[PC[0]].args[1], program[PC[0]].args[2]);
               run_instruction(program[PC[0]], reg, memory, PC, maxPC);
               printf("adress= %d\n", program[PC[0]].adress);
               printf("\n");
           }
           PC[0]++;
           // printf("PC= %d\n", PC[0]);
       }
    for (int z = 0; z < 8; z++) {
        printf("register[%d]= %d \n", z, reg[z]);
    }
    for (int z = 0; z < 8; z++) {
        fprintf(out, "register[%d]= %d\n", z, reg[z]);
    }
}

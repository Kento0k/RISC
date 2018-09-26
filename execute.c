#include"RISCEmulatorLibrary.h"
#include"instruction.c"
void exec_program(FILE *in, FILE *out, int *reg, int memory[1024][16]){
    int maxLine=0, num_of_commands=0, command_count=0, line[1], address=1;
    printf("in");
    line[0]=0;
    text_parameters(in, &maxLine, &num_of_commands);
    //Создаем массив команд
    instruction *program= (instruction*)malloc(num_of_commands * sizeof(instruction));
    int flag[num_of_commands];
    //Заполняем массив команд, присваиваем командам параметры
    for(int i=0; i<=maxLine; i++) {
        flag[i]= parse_file(in, program[command_count].name, program[command_count].args);
        if(flag[i]==1) {
            program[command_count].adress = address;
            address++;
        }
        command_count++;
    }
    for(int i=0; i<8;i++){
        for(int k=0; k<16; k++)
            printf("e %d", memory[i][k]);
        printf("\n");
    }
    //Выполняем программу
       /*while(PC[0]<=maxPC) {
           if(flag[PC[0]]!=0) {
               run_instruction(program[PC[0]], reg, memory, PC, maxPC);
           }
           PC[0]++;
       }
    for (int z = 0; z < 8; z++) {
        printf("register[%d]= %d \n", z, reg[z]);
    }
    for (int z = 0; z < 8; z++) {
        fprintf(out, "register[%d]= %d\n", z, reg[z]);
    }*/
}

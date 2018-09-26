#include"RISCEmulatorLibrary.h"
#include"instruction.c"
void exec_program(FILE *in, FILE *out, int reg[8][16], int memory[4096][16]){
    int maxLine=0, num_of_commands=0, command_count=0, line[1], address=1, PC=1, maxPC=4096;
    line[0]=0;
    text_parameters(in, &maxLine, &num_of_commands);
    //Создаем массив команд
    instruction *program= (instruction*)malloc(num_of_commands * sizeof(instruction));
    int flag[num_of_commands];
    //Заполняем массив команд, присваиваем командам параметры, записываем программу в память
    for(int i=0; i<=maxLine; i++) {
        flag[i]= parse_file(in, program[command_count].name, program[command_count].args);
        if(flag[i]==1) {
            program[command_count].adress = address;
            memory_write(memory, program[command_count]);
            address++;
        }
        command_count++;
    }
    for(int i=0; i<10;i++){
        for(int k=0; k<16; k++)
            printf("%d", memory[i][k]);
        printf("\n");
    }
    //Выполняем программу
    while(PC<=maxPC) {
        run_instruction(reg, memory, &PC);
        PC++;
    }
    for (int z = 0; z < 8; z++) {
        printf("register[%d]= %d \n", z, reg[z]);
    }
    for (int z = 0; z < 8; z++) {
        fprintf(out, "register[%d]= %d\n", z, reg[z]);
    }
}

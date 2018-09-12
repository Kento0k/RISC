#include"RISCEmulatorLibrary.h"
#include"instruction.c"
void debug_program(FILE *in, FILE *out, int *reg, int *memory){
    printf("Debug mode.\nPrint '1' to do the next step.\nPrint'2'to run to the end\n");
    int maxPC=0, num_of_commands=0, command_count=0, PC[1];
    char command[20];
    PC[0]=0;
    text_parameters(in, &maxPC, &num_of_commands);
    instruction *program= (instruction*)malloc(num_of_commands * sizeof(instruction));
    int flag[num_of_commands];
    for(int i=0; i<=maxPC; i++) {
        flag[i]= parse_file(in, program[command_count].name, program[command_count].args);
        if(flag[i]==1)
            program[command_count].adress=i;
        command_count++;
    }
    //Пока не дошли до конца программы
    while(PC[0]<=maxPC) {
        scanf("%s", command);
        if (strcmp("1", command) != 0 && strcmp("2", command) != 0) {
            printf("Wrong command\n");
            continue;
        }
        //Делаем один шаг
        else if (strcmp("1", command) == 0) {
            while (flag[PC[0]] != 1)
                PC[0]++;
            run_instruction(program[PC[0]], reg, memory, PC, maxPC);
            printf("registers:\n");
            for (int z = 0; z < 8; z++)
                printf("register[%d]= %d \n", z, reg[z]);
            printf("\n");
            PC[0]++;
        }
        //Завершаем до конца
        else if(strcmp("2", command) == 0){
            while(PC[0]<=maxPC){
                while (flag[PC[0]] != 1)
                    PC[0]++;
                //printf("%d %d %d\n", program[PC[0]].args[0], program[PC[0]].args[1], program[PC[0]].args[2]);
                run_instruction(program[PC[0]], reg, memory, PC, maxPC);
                printf("registers:\n");
                for (int z = 0; z < 8; z++)
                    printf("register[%d]= %d \n", z, reg[z]);
                printf("\n");
                PC[0]++;
            }
        }
    }
    for (int z = 0; z < 8; z++) {
        printf("register[%d]= %d \n", z, reg[z]);
    }
    for (int z = 0; z < 8; z++) {
        fprintf(out, "register[%d]= %d\n", z, reg[z]);
    }
}


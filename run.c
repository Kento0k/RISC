#include "RISCEmulatorLibrary.h"
#include"instruction.c"
void run_instruction(int reg[8][16], int memory[4096][16], int *PC){
    if(memory[*PC][0]==0&&memory[*PC][1]==0&&memory[*PC][2]==0){
        int regA, regB, regC, carry=0;
        regA=memory[*PC][3]*4+memory[*PC][4]*2+memory[*PC][5];
        regB=memory[*PC][6]*4+memory[*PC][7]*2+memory[*PC][8];
        regC=memory[*PC][13]*4+memory[*PC][14]*2+memory[*PC][15];
        for(int i=16; i>=0; i++){

        }
    }
    else if(memory[*PC][0]==0&&memory[*PC][1]==0&&memory[*PC][2]==1){
        printf("ADDI\n");
    }
    else if(memory[*PC][0]==0&&memory[*PC][1]==1&&memory[*PC][2]==0){
        printf("NAND\n");
    }
    else if(memory[*PC][0]==0&&memory[*PC][1]==1&&memory[*PC][2]==1){
        printf("LUI\n");
    }
    else if(memory[*PC][0]==1&&memory[*PC][1]==0&&memory[*PC][2]==0){
        printf("SW\n");
    }
    else if(memory[*PC][0]==1&&memory[*PC][1]==0&&memory[*PC][2]==1){
        printf("LW\n");
    }
    else if(memory[*PC][0]==1&&memory[*PC][1]==1&&memory[*PC][2]==0){
        printf("BEQ\n");
    }
    else if(memory[*PC][0]==1&&memory[*PC][1]==1&&memory[*PC][2]==1){
        printf("JALR\n");
    }
}
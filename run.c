#include "RISCEmulatorLibrary.h"
#include"instruction.c"
void run_instruction(int reg[8][16], int memory[4096][16], int *PC){
    if(memory[*PC][0]==0&&memory[*PC][1]==0&&memory[*PC][2]==0){
        int regA, regB, regC, carry=0;
        regA=memory[*PC][3]*4+memory[*PC][4]*2+memory[*PC][5];
        regB=memory[*PC][6]*4+memory[*PC][7]*2+memory[*PC][8];
        regC=memory[*PC][13]*4+memory[*PC][14]*2+memory[*PC][15];
        for(int i=15; i>=0; i--){
            reg[regA][i]=reg[regB][i]+reg[regC][i]+carry;
            if(reg[regA][i]==2){
                reg[regA][i]=0;
                carry=1;
            }
            else if(reg[regA][i]==3){
                reg[regA][i]=1;
                carry=1;
            }
            else
                carry=0;
        }
    }
    else if(memory[*PC][0]==0&&memory[*PC][1]==0&&memory[*PC][2]==1){
        int regA, regB, carry=0, imm[16]={0};
        regA=memory[*PC][3]*4+memory[*PC][4]*2+memory[*PC][5];
        regB=memory[*PC][6]*4+memory[*PC][7]*2+memory[*PC][8];
        for(int i=15; i>8; i--)
            imm[i]=memory[*PC][i];
        if(imm[9]==1) {
            for (int i=8; i>=0; i--)
                imm[i]=1;
        }
        for(int i=15; i>=0; i--){
            reg[regA][i]=reg[regB][i]+imm[i]+carry;
            if(reg[regA][i]==2){
                reg[regA][i]=0;
                carry=1;
            }
            else if(reg[regA][i]==3){
                reg[regA][i]=1;
                carry=1;
            }
            else
                carry=0;
        }
    }
    else if(memory[*PC][0]==0&&memory[*PC][1]==1&&memory[*PC][2]==0){
        int regA, regB, regC;
        regA=memory[*PC][3]*4+memory[*PC][4]*2+memory[*PC][5];
        regB=memory[*PC][6]*4+memory[*PC][7]*2+memory[*PC][8];
        regC=memory[*PC][13]*4+memory[*PC][14]*2+memory[*PC][15];
        for(int i=0; i<16; i++){
            if(reg[regB][i]==1&&reg[regC][i]==1)
                reg[regA][i]=0;
            else
                reg[regA][i]=1;
        }
    }
    else if(memory[*PC][0]==0&&memory[*PC][1]==1&&memory[*PC][2]==1){
        int regA;
        regA=memory[*PC][3]*4+memory[*PC][4]*2+memory[*PC][5];
        for(int i=6; i<16;i++){
            reg[regA][i-6]=memory[*PC][i];
        }
        for(int i=10; i<16;i++)
            reg[regA][i]=0;
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
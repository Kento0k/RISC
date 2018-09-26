#include "RISCEmulatorLibrary.h"
#include "instruction.c"
void memory_write(int memory[1024][16], instruction step){
    int address=step.adress;
    int memcnt;
    //reg[a]= reg[b]+reg[c]
    if(strcmp(step.name, "add")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7||step.args[2]<0||step.args[2]>7)
            error_processing(100);
        int regA= step.args[0];
        int regB= step.args[1];
        int regC= step.args[2];
        memory[address][0]=0;
        memory[address][1]=0;
        memory[address][2]=0;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        memcnt=9;
        for(int i=memcnt; i<4; i++)
            memory[address][i] = 0;
        memcnt=15;
        while(regC!=0){
            memory[address][memcnt]=regC%2;
            regC/=2;
            memcnt--;
        }
    }
        //reg[a]=reg[b]+imm
    else if(strcmp(step.name, "addi")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[0]<-63||step.args[0]>63)
            error_processing(110);
        int regA= step.args[0];
        int regB= step.args[1];
        int imm= step.args[2];
        memory[address][0]=0;
        memory[address][1]=0;
        memory[address][2]=1;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        if(imm<0){
            memory[address][9]=1;
            imm=-imm;
        }
        memcnt=15;
        while(imm!=0){
            memory[address][memcnt]=imm%2;
            imm/=2;
            memcnt--;
        }

    }
        //reg[a]=~(reg[a]&reg[b])
    else if(strcmp(step.name, "nand")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7||step.args[2]<0||step.args[2]>7)
            error_processing(100);
        int regA= step.args[0];
        int regB= step.args[1];
        int regC= step.args[2];
        memory[address][0]=0;
        memory[address][1]=1;
        memory[address][2]=0;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        for(int i=memcnt; i<4; i++)
            memory[address][i] = 0;
        memcnt=15;
        while(regC!=0){
            memory[address][memcnt]=regC%2;
            regC/=2;
            memcnt--;
        }

    }
        //place 10 bits of imm from the 16-th bit of reg[a]. The lower 6 bits of reg[a] become 0
    else if(strcmp(step.name, "lui")==0){
        if(step.args[0]<0||step.args[0]>7)
            error_processing(100);
        int regA= step.args[0];
        int imm=step.args[1];
        memory[address][0]=0;
        memory[address][1]=1;
        memory[address][2]=1;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=15;
        while(imm!=0){
            memory[address][memcnt]=imm%2;
            imm/=2;
            memcnt--;
        }
    }
        //store reg[a] in the memory with adress= reg[b]+imm
    else if(strcmp(step.name, "sw")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-63||step.args[2]>63)
            error_processing(110);
        if(step.args[1]+step.args[2]>2047)
            error_processing(120);
        int regA= step.args[0];
        int regB= step.args[1];
        int imm= step.args[2];
        memory[address][0]=1;
        memory[address][1]=0;
        memory[address][2]=0;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        if(imm<0){
            memory[address][9]=1;
            imm=-imm;
        }
        memcnt=15;
        while(imm!=0){
            memory[address][memcnt]=imm%2;
            imm/=2;
            memcnt--;
        }

    }
        //place to reg[a] a value from the memory with adress= reg[b]+imm
    else if(strcmp(step.name, "lw")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-63||step.args[2]>63)
            error_processing(110);
        if(step.args[1]+step.args[2]>2047)
            error_processing(120);
        int regA= step.args[0];
        int regB= step.args[1];
        int imm= step.args[2];
        memory[address][0]=1;
        memory[address][1]=0;
        memory[address][2]=1;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        if(imm<0){
            memory[address][9]=1;
            imm=-imm;
        }
        memcnt=15;
        while(imm!=0){
            memory[address][memcnt]=imm%2;
            imm/=2;
            memcnt--;
        }
    }
        //if reg[a]==reg[b] go to program adress PC+1+imm. PC is the adress of beq
    else if(strcmp(step.name, "beq")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-63||step.args[2]>63)
            error_processing(110);
        int regA= step.args[0];
        int regB= step.args[1];
        int imm= step.args[2];
        memory[address][0]=1;
        memory[address][1]=1;
        memory[address][2]=0;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        if(imm<0){
            memory[address][9]=1;
            imm=-imm;
        }
        memcnt=15;
        while(imm!=0){
            memory[address][memcnt]=imm%2;
            imm/=2;
            memcnt--;
        }
    }
    //go to program adress which contains in reg[b]. reg[a]=PC+1.PC is the adress of jalr
    else if(strcmp(step.name, "jalr")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        int regA= step.args[0];
        int regB= step.args[1];
        memory[address][0]=1;
        memory[address][1]=1;
        memory[address][2]=1;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
    }

}


#include "RISCEmulatorLibrary.h"
#include"instruction.c"
void run_instruction(instruction step, int *reg, int*memory, int *PC, int maxPC){
    //reg[a]= reg[b]+reg[c]
    if(strcmp(step.name, "add")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7||step.args[2]<0||step.args[2]>7)
            error_processing(100);
        reg[step.args[0]]=reg[step.args[1]]+reg[step.args[2]];
    }
    //reg[a]=reg[b]+imm
    else if(strcmp(step.name, "addi")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[0]<-63||step.args[0]>63)
            error_processing(110);
        reg[step.args[0]]=reg[step.args[1]]+step.args[2];
    }
    //reg[a]=~(reg[a]&reg[b])
    else if(strcmp(step.name, "nand")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7||step.args[2]<0||step.args[2]>7)
            error_processing(100);
        reg[step.args[0]]=~(reg[step.args[1]]&reg[step.args[2]]);
    }
    //place 10 bits of imm from the 16-th bit of reg[a]. The lower 6 bits of reg[a] become 0
    else if(strcmp(step.name, "lui")==0){
        if(step.args[0]<0||step.args[0]>7)
            error_processing(100);
        reg[step.args[0]] = step.args[1] <<6;
    }
    //store reg[a] in the memory with adress= reg[b]+imm
    else if(strcmp(step.name, "sw")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-63||step.args[2]>63)
            error_processing(110);
        if(step.args[1]+step.args[2]>2047)
            error_processing(120);
        memory[step.args[1]+step.args[2]]= reg[step.args[0]];

    }
    //place to reg[a] a value from the memory with adress= reg[b]+imm
    else if(strcmp(step.name, "lw")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-63||step.args[2]>63)
            error_processing(110);
        if(step.args[1]+step.args[2]>2047)
            error_processing(120);
        reg[step.args[0]]=memory[step.args[1]+step.args[2]];
    }
    //if reg[a]==reg[b] go to program adress PC+1+imm. PC is the adress of beq
    else if(strcmp(step.name, "beq")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-63||step.args[2]>63)
            error_processing(110);
        if(reg[step.args[0]]==reg[step.args[1]]){
            PC[0]+=step.args[2];
            if(PC[0]>maxPC)
                error_processing(130);
        }
    }
    //go to program adress which contains in reg[b]. reg[a]=PC+1.PC is the adress of jalr
    else if(strcmp(step.name, "jalr")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        reg[step.args[0]]=PC[0]+1;
        if(reg[step.args[1]]>maxPC)
            error_processing(130);
        PC[0]=reg[step.args[1]];
    }
    //finishing program
    else if(strcmp(step.name, "halt")==0){
        PC[0]=maxPC;
    }
}
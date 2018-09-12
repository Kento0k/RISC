#include "RISCEmulatorLibrary.h"
#include"instruction.c"
void run_instruction(instruction step, int *reg, int*memory){
    if(strcmp(step.name, "add")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7||step.args[2]<0||step.args[2]>7)
            error_processing(100);
        reg[step.args[0]]=reg[step.args[1]]+reg[step.args[2]];
    }
    else if(strcmp(step.name, "addi")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[0]<-63||step.args[0]>63)
            error_processing(110);
        reg[step.args[0]]=reg[step.args[1]]+step.args[2];
    }
    else if(strcmp(step.name, "nand")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7||step.args[2]<0||step.args[2]>7)
            error_processing(100);
        reg[step.args[0]]=reg[step.args[1]]&reg[step.args[2]];
    }
    else if(strcmp(step.name, "lui")==0){
        if(step.args[0]<0||step.args[0]>7)
            error_processing(100);
        reg[step.args[0]] = step.args[1] <<6;
    }
    else if(strcmp(step.name, "sw")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-63||step.args[2]>63)
            error_processing(110);
        if(step.args[1]+step.args[2]>2047)
            error_processing(120);
        memory[step.args[1]+step.args[2]]= reg[step.args[0]];

    }
    else if(strcmp(step.name, "lw")==0){
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-63||step.args[2]>63)
            error_processing(110);
        if(step.args[1]+step.args[2]>2047)
            error_processing(120);
        reg[step.args[0]]=memory[step.args[1]+step.args[2]];
    }
    else if(strcmp(step.name, "beq")==0){

    }
    else if(strcmp(step.name, "jalr")==0){

    }
}
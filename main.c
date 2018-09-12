#include "RISCEmulatorLibrary.h"

int main(int argc, char *argv[]){
    FILE *in, *out;
    int reg[8]= {0};
    int memory[2048]= {0};
    if(argc<3 || argc>4) {
        printf("############################################################\n");
        printf("#                                                          #\n");
        printf("# The RISC-16 machine emulator                             #\n");
        printf("#                                                          #\n");
        printf("# Example of command line:                                 #\n");
        printf("# ...\\RISC.exe ...\\in.txt ...\\out.txt [debug]              #\n");
        printf("# ...\\RISC.exe- path to executable file                    #\n");
        printf("# ...\\in.exe- path to input file                           #\n");
        printf("# ...\\RISC.exe- path to output file                        #\n");
        printf("# Print '[debug]' key if you want to enter to debug mode   #\n");
        printf("#                                                          #\n");
        printf("# Example of an input file:                                #\n");
        printf("# SW R1 R2 15                                              #\n");
        printf("# ADD R3 R5 R7                                             #\n");
        printf("# ADDI R4 R2 23                                            #\n");
        printf("# NOP                                                      #\n");
        printf("#                                                          #\n");
        printf("############################################################\n\n");
        error_processing(10);
    }
    else{
        in=fopen(argv[1], "r");
        out=fopen(argv[2], "w");
        if(in==NULL){
            error_processing(20);
        }
        else{
            if(argc==3) {
                exec_program(in, out, reg, memory);
            }
            else if(argc==4){
                if(strcmp(argv[3], "[debug]")==0)
                    debug_program(in,out, reg, memory);
                else
                    error_processing(30);
            }
        }
        fclose(in);
        fclose(out);
    }
    return 0;
}
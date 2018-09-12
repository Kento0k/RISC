#include "RISCEmulatorLibrary.h"
#include "instruction.c"
void clear_text(char *text, int length) {
    char *allowed_symbols = ("abdeijlnrsuw0123456789,-# ");
    int k=0;
    while(k<length) {
        if (text[k] == '#') {
            do {
                text[k] = '#';
                k++;
            } while (text[k] != '\n' && k != length&&text[k]!=EOF);
            continue;
        }
        if (text[k] == '\n'||text[k]==EOF) {
            k++;
            continue;
        }
        text[k] = (char)tolower(text[k]);
        if (strchr(allowed_symbols, text[k]) == NULL)
            error_processing(50);
        k++;
    }
}
int parse_file(FILE *in, instruction program) {
    const char *command[8];
    command[0] = "addi";
    command[1] = "nand";
    command[2] = "jalr";
    command[3] = "add";
    command[4] = "lui";
    command[5] = "beq";
    command[6] = "sw";
    command[7] = "lw" ;
    char *numbers={"0123456789"};
    int symbol=0, strlen=0, argcnt=0, flag=0;
    char *str=(char*)malloc(0);
    while(symbol!='\n'&&symbol!=EOF&&symbol!='#'){
        strlen++;
        str= (char*)realloc(str, strlen*sizeof(char));
        symbol=fgetc(in);
        str[strlen-1]= (char)symbol;
    }
    clear_text(str, strlen);
    while(symbol!='\n'&&symbol!=EOF)
        symbol=fgetc(in);
    if(strlen==1) {
        return 0;
    }
    str[strlen-1]='\0';
    for(int i=0; i<strlen; i++)
        printf("%c", str[i]);
    printf("\n");
    char *oper=strtok(str, " ,");
    strcpy(program.name, oper);
    for(int i=0; i<8; i++){
       if (strcmp(program.name, command[i])==0)
           flag=1;
    }
    if(flag==0)
        error_processing(70);
    for(int i=0; i<5; i++)
        printf("%c",program.name[i]);

    while(oper!=NULL){
        oper=strtok(NULL, ",");
        if(oper!=NULL) {
            if(argcnt==3)
                error_processing(70);
            program.arguments[argcnt] = atoi(oper);
            printf("arg[%d]= %d\n", argcnt, program.arguments[argcnt]);
            argcnt++;
        }
    }
    printf("\n");
    free(str);
    return 0;
}
void text_parameters(FILE* in, int *maxPC, int *num_of_commands){
    int symbol;
    while(!feof(in)){
        if(fgetc(in)=='\n')
            *maxPC+=1;
    }
    fseek(in, 0, SEEK_SET);
    for(int i=0; i<=*maxPC; i++){
        symbol=fgetc(in);
        if(symbol!='#' && symbol!=' ' &&symbol!='\n')
            *num_of_commands+=1;
        while(symbol!='\n' && symbol!=EOF)
                symbol=fgetc(in);
    }
    fseek(in, 0, SEEK_SET);
}




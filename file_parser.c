#include "RISCEmulatorLibrary.h"
void ready_to_run(char *text, int size, instruction *program) {
    const char *command[8];
    command[0] = "addi";
    command[1] = "nand";
    command[2] = "jalr";
    command[3] = "add";
    command[4] = "lui";
    command[5] = "beq";
    command[6] = "sw";
    command[7] = "lw";
    int cnt=0;
    while(cnt<size){
        while(text[cnt]!='\n')
        cnt++;
    }
}
void clear_text(char *text, int length) {
    char *allowed_symbols = ("abdeijlnrsuw0123456789,-# ");
    int k=0;
    while(k<length) {
        if (text[k] == '#') {
            do {
                text[k] = '#';
                k++;
            } while (text[k] != '\n' && k != length);
            continue;
        }
        if (text[k] == '\n') {
            k++;
            continue;
        }
        text[k] = (char)tolower(text[k]);
        if (strchr(allowed_symbols, text[k]) == NULL)
            error_processing(50);
        k++;
    }
}
void parse_file(FILE *in, instruction *program) {
    int length=0;
    char str[20];
    while(!feof(in)){
        fgetc(in);
        length++;
    }
    fseek(in, 0, SEEK_SET);
    char text[length];
    for(int i=0; i< length; i++){
        text[i]=(char)fgetc(in);
        printf("%c", text[i]);
    }
    fclose(in);
    printf("\n");
    clear_text(text, length);
    for(int i=0; i< length; i++){
        printf("%c", text[i]);
    }
    ready_to_run(text, length, program);
}




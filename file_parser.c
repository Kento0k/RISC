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
void read_file(FILE *in, char *str, int length) {
    fgets(str, length, in);
    for(int i=0; i<length; i++)
        printf("%c", str[i]);
    printf("length= %d\n", length);
}
int str_size(FILE *in){
    int cnt=0, symbol=0;
    while(symbol!=EOF&&symbol!='\n') {
        symbol=fgetc(in);
        cnt++;
    }
    fseek(in, 0, SEEK_CUR-cnt);
    return cnt;
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
    //int size=file_size(in);
    char *str;
    int length;
    while(!feof(in)) {
        length=str_size(in);
        str=(char*)malloc(length*sizeof(char));
        read_file(in, str, length);
        free(str);
        //for(int i=0; i<length; i++)
            //printf("%c a", str[i]);
        //clear_text(text, size);
        //ready_to_run(text, size, program);
    }
}




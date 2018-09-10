#include "RISCEmulatorLibrary.h"
void find_operands(char *str, char *oper1, char *oper2, char*oper3){
    
}
void read_file(FILE *in, int *text) {
    int cnt=0, symbol;
    while(!feof(in)){
        symbol=fgetc(in);
        text[cnt]=symbol;
        cnt++;
    }
    fclose(in);
}
int file_size(FILE *in){
    int cnt=0;
    while(!feof(in)) {
        fgetc(in);
        cnt++;
    }
    fseek(in, 0, SEEK_SET);
    return cnt;
}
void clear_text(int *text, int length) {
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
        text[k] = tolower(text[k]);
        if (strchr(allowed_symbols, text[k]) == NULL)
            error_processing(50);
        k++;
    }
}
void parse_file(FILE *in) {
    int size=file_size(in);
    int text[size];
    read_file(in, text);
    clear_text(text, size);

}




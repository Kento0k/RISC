#include "RISCEmulatorLibrary.h"
#include"instruction.c"
void run_instruction(int reg[8][16], int memory[4096][16], int *PC) {
    //ADD
    if (memory[*PC][0] == 0 && memory[*PC][1] == 0 && memory[*PC][2] == 0) {
        int regA, regB, regC, carry = 0;
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        regC = memory[*PC][13] * 4 + memory[*PC][14] * 2 + memory[*PC][15];
        if(regA!=0) {
            for (int i = 15; i >= 0; i--) {
                reg[regA][i] = reg[regB][i] + reg[regC][i] + carry;
                if (reg[regA][i] == 2) {
                    reg[regA][i] = 0;
                    carry = 1;
                } else if (reg[regA][i] == 3) {
                    reg[regA][i] = 1;
                    carry = 1;
                } else
                    carry = 0;
            }
        }
    }
        //ADDI
    else if (memory[*PC][0] == 0 && memory[*PC][1] == 0 && memory[*PC][2] == 1) {
        int regA, regB, carry = 0, imm[16] = {0};
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        if(regA!=0) {
            for (int i = 15; i > 8; i--)
                imm[i] = memory[*PC][i];
            if (imm[9] == 1) {
                for (int i = 8; i >= 0; i--)
                    imm[i] = 1;
            }
            for (int i = 15; i >= 0; i--) {
                reg[regA][i] = reg[regB][i] + imm[i] + carry;
                if (reg[regA][i] == 2) {
                    reg[regA][i] = 0;
                    carry = 1;
                } else if (reg[regA][i] == 3) {
                    reg[regA][i] = 1;
                    carry = 1;
                } else
                    carry = 0;
            }
        }
    }
        //NAND
    else if (memory[*PC][0] == 0 && memory[*PC][1] == 1 && memory[*PC][2] == 0) {
        int regA, regB, regC;
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        regC = memory[*PC][13] * 4 + memory[*PC][14] * 2 + memory[*PC][15];
        if(regA!=0) {
            for (int i = 0; i < 16; i++) {
                if (reg[regB][i] == 1 && reg[regC][i] == 1)
                    reg[regA][i] = 0;
                else
                    reg[regA][i] = 1;
            }
        }
    }
        //LUI
    else if (memory[*PC][0] == 0 && memory[*PC][1] == 1 && memory[*PC][2] == 1) {
        int regA;
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        if(regA!=0) {
            for (int i = 6; i < 16; i++) {
                reg[regA][i - 6] = memory[*PC][i];
            }
            for (int i = 10; i < 16; i++)
                reg[regA][i] = 0;
        }
    }
        //SW
    else if (memory[*PC][0] == 1 && memory[*PC][1] == 0 && memory[*PC][2] == 0) {
        int regA, regB, carry = 0, imm[16] = {0}, address[16] = {0}, intAddress = 0, deg = 1;
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        for (int i = 15; i > 8; i--)
            imm[i] = memory[*PC][i];
        if (imm[9] == 1) {
            for (int i = 8; i >= 0; i--)
                imm[i] = 1;
        }
        for (int i = 15; i >= 0; i--) {
            address[i] = reg[regB][i] + imm[i] + carry;
            if (address[i] == 2) {
                address[i] = 0;
                carry = 1;
            } else if (address[i] == 3) {
                address[i] = 1;
                carry = 1;
            } else
                carry = 0;
        }
        for (int i = 15; i >= 0; i--) {
            intAddress += address[i] * deg;
            deg *= 2;
        }
        if (intAddress > 4095)
            error_processing(120);
        if (intAddress != 0) {
            for (int i = 0; i < 16; i++)
                memory[intAddress][i] = reg[regA][i];
        }
    }
        //LW
    else if (memory[*PC][0] == 1 && memory[*PC][1] == 0 && memory[*PC][2] == 1) {
        int regA, regB, carry = 0, imm[16] = {0}, address[16] = {0}, intAddress = 0, deg = 1;
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        if(regA!=0) {
            for (int i = 15; i > 8; i--)
                imm[i] = memory[*PC][i];
            if (imm[9] == 1) {
                for (int i = 8; i >= 0; i--)
                    imm[i] = 1;
            }
            for (int i = 15; i >= 0; i--) {
                address[i] = reg[regB][i] + imm[i] + carry;
                if (address[i] == 2) {
                    address[i] = 0;
                    carry = 1;
                } else if (address[i] == 3) {
                    address[i] = 1;
                    carry = 1;
                } else
                    carry = 0;
            }
            for (int i = 15; i >= 0; i--) {
                intAddress += address[i] * deg;
                deg *= 2;
            }
            if (intAddress > 4095)
                error_processing(120);
            for (int i = 0; i < 16; i++)
                reg[regA][i] = memory[intAddress][i];
        }
    }
        //BEQ
    else if (memory[*PC][0] == 1 && memory[*PC][1] == 1 && memory[*PC][2] == 0) {
        int regA, regB, carry = 0, imm[16] = {0}, address[16] = {0}, intAddress = *PC, deg = 1, cnt = 15, isEqual = 1;
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        for (int i = 0; i < 16; i++) {
            if (reg[regA][i] != reg[regB][i]) {
                isEqual = 0;
                break;
            }
        }
        if (isEqual == 1) {
            for (int i = 15; i > 8; i--)
                imm[i] = memory[*PC][i];
            if (imm[9] == 1) {
                for (int i = 8; i >= 0; i--)
                    imm[i] = 1;
            }
            while (intAddress != 0) {
                address[cnt] = intAddress % 2;
                intAddress /= 2;
                cnt--;
            }
            for (int i = 15; i >= 0; i--) {
                address[i] = address[i] + imm[i] + carry;
                if (address[i] == 2) {
                    address[i] = 0;
                    carry = 1;
                } else if (address[i] == 3) {
                    address[i] = 1;
                    carry = 1;
                } else
                    carry = 0;
            }
            for (int i = 15; i >= 0; i--) {
                intAddress += address[i] * deg;
                deg *= 2;
            }
            if (intAddress > 4095)
                error_processing(120);
            *PC = intAddress;
        }
    }
        //JALR
    else if (memory[*PC][0] == 1 && memory[*PC][1] == 1 && memory[*PC][2] == 1) {
        int regA, regB, address=0, jalrAddress = *PC + 1, cnt = 15, deg = 1;
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        for (int i = 15; i >= 0; i--) {
            address += reg[regB][i] * deg;
            deg *= 2;
        }
        address--;
        if (address > 4094)
            error_processing(120);
        *PC = address;
        if(regA!=0) {
            while (jalrAddress != 0) {
                reg[regA][cnt] = jalrAddress % 2;
                jalrAddress /= 2;
                cnt--;
            }
            while (cnt >= 0) {
                reg[regA][cnt] = 0;
                cnt--;
            }
        }
    }
}
.PHONY: all clean

all: final.exe

final.exe : main.o errors.o file_parser.o instruction.o
	gcc -o final main.o errors.o file_parser.o instruction.o

main.o : main.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o main.o main.c

errors.o : errors.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o errors.o errors.c

file_parser.o : file_parser.c   
	gcc -std=c11 -pedantic -Wall -Wextra -c -o file_parser.o file_parser.c

instruction.o : instruction.c   
	gcc -std=c11 -pedantic -Wall -Wextra -c -o instruction.o instruction.c

clean :
	del *.o
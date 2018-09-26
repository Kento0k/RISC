.PHONY: all clean

all: RISC.exe

RISC.exe : main.o errors.o file_parser.o instruction.o run.o execute.o debug.o write_to_memory.o
	gcc -o RISC main.o errors.o file_parser.o instruction.o run.o execute.o debug.o write_to_memory.o

main.o : main.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o main.o main.c

errors.o : errors.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o errors.o errors.c

file_parser.o : file_parser.c   
	gcc -std=c11 -pedantic -Wall -Wextra -c -o file_parser.o file_parser.c

instruction.o : instruction.c   
	gcc -std=c11 -pedantic -Wall -Wextra -c -o instruction.o instruction.c

run.o : run.c   
	gcc -std=c11 -pedantic -Wall -Wextra -c -o run.o run.c

debug.o : debug.c   
	gcc -std=c11 -pedantic -Wall -Wextra -c -o debug.o debug.c

execute.o : execute.c   
	gcc -std=c11 -pedantic -Wall -Wextra -c -o execute.o execute.c

write_to_memory.o : write_to_memory.c   
	gcc -std=c11 -pedantic -Wall -Wextra -c -o write_to_memory.o write_to_memory.c
clean :
	del *.o
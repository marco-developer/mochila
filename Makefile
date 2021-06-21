# the compiler: gcc for C program, define as g++ for C++
CC = gcc 

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -O3 -Wextra -Wno-unused-result 

all: main

aplicacao: mochila.o main.o
	$(CC) $(CFLAGS) mochila.o main.o -o main

mochila.o: mochila.c mochila_privada.h mochila_publica.h
	$(CC) $(CFLAGS) -c mochila.c -o mochila.o

#main.o: main.c
#	$(CC) $(CFLAGS) -c main.c -o main.o
	
main: main.c mochila.o
	$(CC) $(CFLAGS) main.c mochila.o -o main

clean: 
	rm -f main *.o 

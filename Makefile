all: main

aplicacao: mochila.o main.o
	gcc mochila.o main.o -o main

mochila.o: mochila.c
	gcc -c mochila.c mochila_privada.h mochila_publica.h -o mochila.o

main.o: main.c
	gcc -c main.c -o main.o

clean: 
	rm -f main *.o 

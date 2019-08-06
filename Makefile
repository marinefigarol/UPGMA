CC = gcc
CFLAGS = -c -Wall -g

all: main

arbre.o: arbre.c
	$(CC) arbre.c $(CFLAGS)

liste.o: liste.c
	$(CC) liste.c arbre.c $(CFLAGS)
	
matrice.o: matrice.c
	$(CC) matrice.c liste.c arbre.c $(CFLAGS)
    
upgma.o: upgma.c
	$(CC) upgma.c liste.c arbre.c matrice.c $(CFLAGS)
   
main.o: main.c
	$(CC) main.c $(CFLAGS)
	
main: main.o liste.o arbre.o matrice.o upgma.o
	$(CC) liste.o arbre.o matrice.o upgma.o -o main main.o

clean:
	rm *o

mrproper:
	rm *o main

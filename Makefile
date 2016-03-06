################################################################################
#Compilation : se deplacer dans la racine des fichiers et lancer						   #
#via le terminal la commande make																							 #
################################################################################

CC=gcc
CFLAGS=-Wall

Allocator: main.o myfree.o mymalloc.o mytest.o
	$(CC) main.o myfree.o mymalloc.o mytest.o Allocator

main.o: main.c myfree.c mymalloc.c mytest.c
	$(CC) -c main.c -o main.o

myfree.o: myfree.c
	$(CC) -c myfree.c -o myfree.o

mymalloc.o: mymalloc.c
	$(CC) -c mymalloc.c -o mymalloc.o

mytest.o: mytest.c
	$(CC) -c mytest.c -o mytest.o

################################################################################
#lancement du programme : se deplacer dans la racine des fichiers         	   #
#et lancer via le terminal la commande make run																 #
################################################################################

run:
	@echo "Lancement du programme : "
	./main

################################################################################
#Nettoyage des executables : se deplacer dans la racine des fichiers       	   #
#et lancer via le terminal la commande make clean															 #
################################################################################
clean:
	rm -rf *o

mrproper: clean
	rm -rf Allocator

#AUTHOR : SINGH AMAN AND MOTTIAT GILLES


################################################################################
#Compilation : se deplacer a l'endroit du makefile et lancer "make build"      #
#via le terminal    							       #
################################################################################

CC = gcc
CFLAGS = -c -Wall
INCLUDE_PATH = include/
SRC_PATH = src/
cUnit_INCLUDE_PATH = $(HOME)/local/include
cUnit_LIB_PATH = $(HOME)/local/lib

build: output

output: tests.o myfree.o mymalloc.o mycalloc.o
	$(CC) -I$(cUnit_INCLUDE_PATH) -L$(cUnit_LIB_PATH) tests.o myfree.o mymalloc.o -o alloc -lcunit

tests.o: $(SRC_PATH)tests.c $(INCLUDE_PATH)mymalloc.h $(INCLUDE_PATH)mycalloc.h $(INCLUDE_PATH)myfree.h
	$(CC) -I$(cUnit_INCLUDE_PATH) -L$(cUnit_LIB_PATH) $(CFLAGS) $(SRC_PATH)tests.c -lcunit

mymalloc.o: $(SRC_PATH)mymalloc.c $(INCLUDE_PATH)mymalloc.h
	$(CC) $(CFLAGS) $(SRC_PATH)mymalloc.c

mycalloc.o: $(SRC_PATH)mycalloc.c $(INCLUDE_PATH)mycalloc.h
	$(CC) $(CFLAGS) $(SRC_PATH)mycalloc.c

myfree.o: $(SRC_PATH)myfree.c $(INCLUDE_PATH)myfree.h
	$(CC) $(CFLAGS) $(SRC_PATH)myfree.c

################################################################################
#Nettoyage des fichiers .o : se deplacer a l'endroit du makefile et lancer     #
# "make clean" via le terminal 	   					       #
################################################################################

.PHONY: clean

clean:
	rm -rf *o

################################################################################
#Nettoyage de l'exec alloc : se deplacer a l'endroit du makefile et lancer     #
# "make mrproper" via le terminal 	   				       #
################################################################################

mrproper: clean
	rm -rf alloc

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: main.o database.o set.o stack.o queue.o hashmap.o
	$(CC) $(CFLAGS) main.o database.o set.o stack.o queue.o hashmap.o -o dbms

main.o: main.c database.h
	$(CC) -c main.c

database.o:	database.c database.h
	$(CC) -c database.c

set.o: set.c set.h
	$(CC) -c set.c

stack.o: stack.c stack.h
	$(CC) -c stack.c

queue.o: queue.c queue.h
	$(CC) -c queue.c

hashmap.o: hashmap.c hashmap.h
	$(CC) -c hashmap.c

clear:
	rm -rf *.o
	rm dbms

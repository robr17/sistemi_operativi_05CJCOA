CC = gcc

all: compile clean

compile: object
	$(CC) *.o -o es2

object:
	$(CC) -c *.c

clean:
	rm -f *.o 
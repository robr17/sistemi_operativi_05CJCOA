CC = gcc
CFLAGS = -Wall
SOURCE = main.c
OBJ = main.o
EXE = exe

all: compile clean

compile: object
	$(CC) -o $(EXE) $(OBJ)

object:
	$(CC) -c $(SOURCE)

clean:
	rm $(OBJ)

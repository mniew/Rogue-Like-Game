SRCS = $(wildcard *.c)

all:Rogue

Rogue: src/main.c
	gcc src/main.c src/drawRoom.c src/readFile.c src/fileTest.c src/heroMove.c -Wall -std=c99 -lncurses -Iinclude -o Rogue

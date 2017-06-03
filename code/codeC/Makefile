.PHONY: all clean maxclean

CC=gcc
DIRSRC = ./src
DIROBJ = ./obj
CFLAGS= -g -Wall -std=c99
LDFLAGS=-lm
#EXEC=TestIA.out


all : EXEC

Coordinates.o :
	$(CC) -c $(DIRSRC)/Coordinates.c -o $(DIROBJ)/Coordinates.o
Piece.o :
	$(CC) -c $(DIRSRC)/Piece.c -o $(DIROBJ)/Piece.o
List.o :
	$(CC) -c $(DIRSRC)/List.c -o $(DIROBJ)/List.o
HashTable.o :
	$(CC) -c $(DIRSRC)/HashTable.c -o $(DIROBJ)/HashTable.o
FileProcessing.o :
	$(CC) -c $(DIRSRC)/FileProcessing.c -o $(DIROBJ)/FileProcessing.o
Graph.o :
	$(CC) -c $(DIRSRC)/Graph.c -o $(DIROBJ)/Graph.o
ReducedGraph.o :
	$(CC) -c $(DIRSRC)/ReducedGraph.c -o $(DIROBJ)/ReducedGraph.o
TreeOfGameIA.o :
	$(CC) -c $(DIRSRC)/TreeOfGameIA.c -o $(DIROBJ)/TreeOfGameIA.o
TestIA.o :
	$(CC) -c $(DIRSRC)/TestIA.c -o $(DIROBJ)/TestIA.o
sdl.o :
	$(CC) -c $(DIRSRC)/sdl.c -o $(DIROBJ)/sdl.o
EXEC : Coordinates.o\
	   Piece.o\
	   List.o\
	   HashTable.o\
	   FileProcessing.o\
	   Graph.o\
	   ReducedGraph.o\
	   TreeOfGameIA.o\
	   sdl.o\
	   TestIA.o\

	$(CC) $(CFLAGS) -o ./bin/hex $(DIROBJ)/*.o -lSDL -lSDL_image #$(LDFLAGS)

clean: ;
	rm $(DIROBJ)/*.o

maxclean:
	rm $(DIROBJ)/*.o ./bin/*

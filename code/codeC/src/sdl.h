//
//  sdl.h
//  sdl
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
//

#ifndef sdl_h
#define sdl_h

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Graph.h"
#include "ReducedGraph.h"
#include "TreeOfGameIA.h"

#define WIGTH 900
#define HEIGHT 550
#define SIZE_HEX 30
#define POS_BEGIN 0
#define SHIFT_RIGHT 15
#define SHIFT_DOWN 20
#define MARGE 2

void loadBoard(char *spots, SDL_Surface *screen, int sizeBoard, int coordX[], int coordY[]);

void placePiece(SDL_Surface *screen, int x, int y, SDL_Surface * colorHex);

int coordOK(int coordX[], int coordY[], int *x, int *y, int sizeBoard);

int getReelyCoordinates(int coordX[], int coordY[], int y, int x, int nbCoord);

void convertPosToPixel(int coordX[], int coordY[], int *y, int *x, int pos);

void menuLoop(SDL_Surface * screen);

int isVertexEmpty(const Graph g, int pos);

int coordOK(int coordX[], int coordY[], int *x, int *y, int sizeBoard);

void play(SDL_Surface *scree, int level);

int chooseLevel(SDL_Surface * screen);
#endif /* sdl_h */

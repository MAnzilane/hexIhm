//
// main.c
//
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
//


#include <stdio.h>
#include "Graph.h"
#include "ReducedGraph.h"
#include "TreeOfGameIA.h"
#include "FileProcessing.h"
#include "sdl.h"



int main(int argc, const char * argv[]) {
    SDL_Surface *screen = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    //to set icon on the game window
    SDL_WM_SetIcon(IMG_Load("/home/manzilane/Documents/IHMenSDL/doc/data/icon.png"), NULL);

    if ((screen = SDL_SetVideoMode(WIGTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        fprintf(stderr, "sory the scree don't init : %s\n", SDL_GetError());
        exit(-1);
    }
    //title of windows
    SDL_WM_SetCaption("HEX GAME", NULL);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    menuLoop(screen);

    SDL_Quit();
    return EXIT_SUCCESS;
}

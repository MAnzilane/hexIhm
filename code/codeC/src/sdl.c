#include "sdl.h"
/*-----------------------------SDL FONCTIO-------------------------------------*/
void loadBoard(char *spots, SDL_Surface *screen, int sizeBoard, int coordX[], int coordY[]) {
    SDL_Surface *whiteHex = NULL,  *blueHex = NULL, *redHex = NULL;
    SDL_Rect posHex;

    whiteHex = IMG_Load("/home/manzilane/Documents/IHMenSDL/doc/data/hex.png");
    blueHex = IMG_Load("/home/manzilane/Documents/IHMenSDL/doc/data/BleuHex.png");
    redHex = IMG_Load("/home/manzilane/Documents/IHMenSDL/doc/data/RedHex.png");
    int x = POS_BEGIN; int y = POS_BEGIN;
    posHex.x = POS_BEGIN;
    posHex.y = POS_BEGIN;
    int cx = 0;
    int cy = 0;
    for (int i = 0; i < sizeBoard*sizeBoard; i++) { //juste for test
        if (i % sizeBoard == 0 && i != 0) {
             posHex.x = x + SHIFT_RIGHT;
             posHex.y += SHIFT_DOWN;
             x = posHex.x;
        }
        switch (spots[i]) {
            case BLACK:
                SDL_BlitSurface(blueHex, NULL, screen, &posHex);
                break;
            case WHITE:
                SDL_BlitSurface(redHex, NULL, screen, &posHex);
                break;
            case EMPTY:
                SDL_BlitSurface(whiteHex, NULL, screen, &posHex);
        }
        coordX[cx++] = posHex.x; coordY[cy++] = posHex.y;
        posHex.x += SIZE_HEX;
    }
    SDL_Flip(screen);
    SDL_FreeSurface(blueHex);
    SDL_FreeSurface(whiteHex);
    SDL_FreeSurface(redHex);
    printf("je sorts de la fonction de chargement\n");
}

//if I call this fonctoin. that means we have reely coordinates
int getReelyCoordinates(int coordX[], int coordY[], int y, int x, int nbCoord) {
    for (int i = 0; i < nbCoord; i++) {
        if (coordX[i] == x && coordY[i] == y) {
            return i;
        }
    }
    return -1;
}

void convertPosToPixel(int coordX[], int coordY[], int *y, int *x, int pos) {
    *x = coordX[pos];
    //printf("coordX[%d] =  %d  coordY[%d] = %d\n",pos, coordX[pos], pos, coordY[pos]);
    *y = coordY[pos];
}


void placePiece(SDL_Surface *screen, int x, int y, SDL_Surface * colorHex) {
    SDL_Rect posHex;
    posHex.x = x;
    posHex.y = y;

    SDL_BlitSurface(colorHex, NULL, screen, &posHex);
    SDL_Flip(screen);
}

int coordOK(int coordX[], int coordY[], int *x, int *y, int sizeBoard) {

    int turn = 1;

    for (int i = 0; i < sizeBoard*sizeBoard; i++) {
        if (i % sizeBoard == 0 && i != 0) {
            turn++;
        }
        if ((coordX[i]+MARGE <= *x && coordX[i]+SIZE_HEX-MARGE > *x)
        && ((turn-1)*SHIFT_DOWN+MARGE <= *y && *y < turn*SHIFT_DOWN-MARGE)) {
            *x = coordX[i];
            *y = (turn-1)*SHIFT_DOWN;
            return 1;
        }
    }
    return 0;
}


int isVertexEmpty(const Graph g, int pos) {
    return g->v[pos]->color == EMPTY;
}

char * createFileName(int level) {
    char * buff = malloc(sizeof(char)*100);
    sprintf(buff, "/home/manzilane/Documents/IHMenSDL/doc/config/size%d.txt", level);
    return buff;
}


void play(SDL_Surface *screen, int level) {
    int go = 1;
    int ok = 1;
    int stop = 0;
    int loaded = 0;
    SDL_Surface * blueHex = NULL, *redHex = NULL, * gameBack = NULL;
    SDL_Rect posBack;
    SDL_Event event;
    Graph g = createGraph(level);
    char * fileName = createFileName(level);
    char * spots = getSpotsFromFile(fileName);
    g = createBoardGraph(g, spots, &loaded);
    ReducedGraph *rg = createReducedGraph(g);
    int coordY[getNbVertexGraph(g)];
    int coordX[getNbVertexGraph(g)];
    int t = getSizeGraph(g);
    if ((screen = SDL_SetVideoMode(t*SIZE_HEX+(t-1)*SHIFT_RIGHT, t*SHIFT_DOWN+SHIFT_DOWN/2, 32,
    SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE)) == NULL) {
        fprintf(stderr, "sory the scree don't init : %s\n", SDL_GetError());
        exit(-1);
    }
    
    gameBack = IMG_Load("/home/manzilane/Documents/IHMenSDL/doc/data/gameBack.png");
    posBack.x = 0;
    posBack.y = 0;
    SDL_BlitSurface(gameBack, NULL, screen, &posBack);
    SDL_Flip(screen);
    loadBoard(spots, screen, getSizeGraph(g), coordX, coordY);
    blueHex = IMG_Load("/home/manzilane/Documents/IHMenSDL/doc/data/BleuHex.png");
    redHex = IMG_Load("/home/manzilane/Documents/IHMenSDL/doc/data/RedHex.png");
    int wWin = 0; int bWin = 0;
    int x = -1; int y = -1;
    int pos = -1; int ko = 1;
    while (go) {
        if (ok) {
            printf("pos %d \n", pos);
            pos = minimax(g, 2);
            convertPosToPixel(coordX, coordY, &y, &x, pos);
            printf("pos = %d x = %d y = %d\n", pos, x, y);
            replaceVertexGraph(g, pos, BLACK); //replace aschii mode
            placePiece(screen, x, y, blueHex); //replace graphics mode

            if ((stop = searchGroup(rg->blackHashTab, g, pos, BLACK)) == 1) {
                bWin = 1;
            }
            ok = !ok;
        }else {
            ko = 1; //init the loop of human player
            while (ko) {
                SDL_WaitEvent(&event);
                switch (event.type) {
                    case SDL_QUIT:
                        go = 0;
                        ko = 0;
                        break;
                    case SDL_MOUSEBUTTONUP:
                        x = event.button.x; y= event.button.y;
                        if (coordOK(coordX, coordY, &x, &y, getSizeGraph(g))) {
                            pos = getReelyCoordinates(coordX, coordY, y , x, getNbVertexGraph(g));
                            if (isVertexEmpty(g, pos)) {
                                replaceVertexGraph(g, pos, WHITE); //replace aschii mode
                                placePiece(screen, x, y, redHex); //replace graphics mode
                                if ((stop = searchGroup(rg->whiteHashTab, g, pos, WHITE)) == 1) {
                                    wWin = 1;
                                }
                                ok = !ok;
                                ko = 0;
                            }
                        }
                        break;
                    case SDL_KEYDOWN :
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            go = 0;
                            ko = 0;
                        }
                }
            }
        }
    }
    SDL_FreeSurface(redHex);
    SDL_FreeSurface(blueHex);
    free(spots);
    free(fileName);
    destroyReducedGraph(rg);
    destroyGraph(g);
}

void menuLoop(SDL_Surface * screen) {
    int go = 1; int sizeGame = 0;
    SDL_Event event;
    SDL_Surface * menu = NULL;
    SDL_Rect posMenu;
    posMenu.x = 0;
    posMenu.y = 0;
    menu = IMG_Load("/home/manzilane/Documents/IHMenSDL/doc/data/HexMenu.png");
    while (go) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                go = 0; //stop game
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: //quit game
                        go = 0;
                        break;
                    case SDLK_n:
                        if ((sizeGame = chooseLevel(screen)) != 0) {
                            play(screen, sizeGame);
                        }
                        break;
                        //if I want to load game
                }

        }
        if ((screen = SDL_SetVideoMode(WIGTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
            fprintf(stderr, "sory the scree don't init : %s\n", SDL_GetError());
            exit(-1);
        }
        SDL_BlitSurface(menu, NULL, screen, NULL);
        SDL_Flip(screen);
    }
}

int chooseLevel(SDL_Surface * screen) {
    int go = 1;
    int sizeGame = 0;
    SDL_Event event;
    SDL_Surface * level = NULL;
    SDL_Rect posMenu;
    posMenu.x = 0;
    posMenu.y = 0;
    level = IMG_Load("/home/manzilane/Documents/IHMenSDL/doc/data/Level.png");

    while (go) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                go = 0; //stop game
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: //quit game
                        go = 0;
                        break;
                    case SDLK_a:
                        sizeGame = 3;
                        go = 0;
                        break;
                    case SDLK_b:
                        sizeGame = 4;
                        go = 0;
                        break;
                    case SDLK_c:
                        sizeGame = 5;
                        go = 0;
                        break;
                    case SDLK_d:
                        sizeGame = 6;
                        go = 0;
                        break;
                    case SDLK_e:
                        sizeGame = 7;
                        go = 0;
                        break;
                    case SDLK_f:
                        sizeGame = 8;
                        go = 0;
                        break;
                    case SDLK_g:
                        sizeGame = 9;
                        go = 0;
                        break;
                    case SDLK_h:
                        sizeGame = 10;
                        go = 0;
                        break;
                    case SDLK_i:
                        sizeGame = 11;
                        go = 0;
                        break;
                    case SDLK_j:
                        sizeGame = 12;
                        go = 0;
                        break;
                    case SDLK_k:
                        sizeGame = 13;
                        go = 0;
                        break;
                    case SDLK_l:
                        sizeGame = 14;
                        go = 0;
                        break;
                }

        }
        SDL_BlitSurface(level, NULL, screen, &posMenu);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(level);
    return sizeGame;
}

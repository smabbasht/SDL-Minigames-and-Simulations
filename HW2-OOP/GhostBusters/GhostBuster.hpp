#include<SDL.h>



void initialize();

void drawBlocks(SDL_Renderer*, SDL_Texture*);

void huntGhost(int x, int y);

void bustGhost(int x, int y);

void drawOneBlock(SDL_Renderer* renderer, SDL_Texture*, int row, int col, char sym);

void quitGhostBuster();
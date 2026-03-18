#ifndef TERRAING_H
#define TERRAIN_H
#include "raylib.h"
#include <stdlib.h>
// da finire di scrivere
typedef struct {
    int dimensionx;
    int dimensiony;
    int *tileMap;    
    int nTiles;
    Image tilesTexture[100];
} Terrain;

Terrain initTerrain(int dimx, int dimy);
void updateTerrain(Terrain *terrain);
void drawTerrain(Terrain terrain);

#endif
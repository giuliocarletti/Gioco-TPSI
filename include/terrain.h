#ifndef TERRAING_H
#define TERRAIN_H
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    Vector2 size;
    int *tileMap;
    int tileSize;    
    Texture2D tilesTexture;
} Terrain;

Terrain initTerrain(int dimx, int dimy, int size);
void updateTerrain(Terrain *terrain);
void drawTerrain(Terrain terrain, Vector2 playerWorld);

#endif
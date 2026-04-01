#ifndef TERRAIN_H
#define TERRAIN_H
#include "raylib.h"
#include "player.h"

typedef struct {
    Vector2 size;
    int *tileMap;
    int tileSize;    
    Texture2D tilesTexture;
} Terrain;

Terrain initTerrain(int dimx, int dimy, int size);
void drawTerrain(Terrain terrain, Player player);

#endif
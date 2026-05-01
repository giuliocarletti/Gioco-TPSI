#ifndef TERRAIN_H
#define TERRAIN_H

#include "config.h"
#include "player.h"

typedef struct {
    int xDimension;
    int yDimension;
    int *tileMap;
    int tileSize;    
    Texture2D tilesTexture;    
} Terrain;

Terrain initTerrain();
void renderTerrain(Terrain terrain, Player player);
void unloadTerrain(Terrain *terrain);

#endif
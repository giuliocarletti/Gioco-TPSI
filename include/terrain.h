#ifndef TERRAIN_H
#define TERRAIN_H

#include "config.h"
#include "player.h"

typedef struct Terrain {
    int xDimension;
    int yDimension;
    int *tileMap;
    int tileSize;    
    Texture2D tilesTexture;  

    struct {
        int array[N_BLOCKED_TILES];  
        int length;
    } blockedTiles;

} Terrain;

Terrain initTerrain();
void renderTerrain(Terrain terrain, Player player);
void unloadTerrain(Terrain *terrain);
bool isTileBlocked(int n, Terrain terrain);

#endif
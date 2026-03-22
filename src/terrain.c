#include "terrain.h"

Terrain initTerrain(int dimx, int dimy, int size) {
    Terrain terrain;
    terrain.size.x = dimx;
    terrain.size.y = dimy;
    terrain.tileSize = size;
    terrain.tileMap = (int *)malloc(sizeof(int)*dimx*dimy);
    terrain.tilesTexture = LoadTexture("floor_tiles.png");
    FILE *file = fopen("assets/maps/map.csv", "r");
    char line[4096];
    for(int row=0; row<dimy; row++) {
        fgets(line, 4096, file);
        for(int col=0; col<dimx; col++) {
            char *info = strtok(col==0? line:NULL, ",");
            terrain.tileMap[row*col] = atoi(info);   
        }
    }    
    return terrain;
}

void updateTerrain(Terrain *terrain) {
    
}

void drawTerrain(Terrain terrain) {
    for(int row=0; row<terrain.size.y; row++) {
        for(int col=0; col<terrain.size.x; col++) {
            int currentTileNum = terrain.tileMap[row*col];
            // disegno
        }    
    }
}
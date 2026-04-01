#include "terrain.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Terrain initTerrain(int dimx, int dimy, int size) {
    Terrain terrain;
    terrain.size.x = dimx; // larghezza mappa
    terrain.size.y = dimy; // altezza mappa
    terrain.tileSize = size; // grandezza tile
    terrain.tileMap = (int *)malloc(sizeof(int)*dimx*dimy); // inizializzazione dell'array
    terrain.tilesTexture = LoadTexture("assets/tiles/floor_tiles.png"); // caricamento delle texture tile
    FILE *file = fopen("assets/maps/map.csv", "r"); // apertura del file csv
    for(int row=0; row<dimy; row++) { 
        char line[4096]; // buffer
        fgets(line, 4096, file); // prende una riga
        for(int col=0; col<dimx; col++) {
            int index = row*dimx+col; // indice
            char *info = strtok(col==0? line:NULL, ","); // la riga viene suddivisa 
            terrain.tileMap[index] = atoi(info); // il dato viene trasformato in int
            //printf(" %s", info);
        } 
        //printf("\n");
    }
    fclose(file);
    return terrain; // restituisci il terreno
}

void drawTerrain(Terrain terrain, Player player) {
    int resolution = 32;    
    Texture texture = terrain.tilesTexture;
    for(int row=0; row<terrain.size.y; row++) {
        for(int col=0; col<terrain.size.x; col++) {
            int index = row*terrain.size.x+col;
            int currentTileNum = terrain.tileMap[index];
            int textureCols = texture.width/resolution;
            int xTexturePos = currentTileNum%textureCols;
            int yTexturePos = currentTileNum/textureCols;
            Vector2 world = {
                col*terrain.tileSize, 
                row*terrain.tileSize
            };
            Vector2 screen = {
                world.x-player.world.x+player.screen.x, 
                world.y-player.world.y+player.screen.y
            };
            Rectangle src = {
                xTexturePos*resolution, 
                yTexturePos*resolution, 
                resolution, 
                resolution
            };
            Rectangle dst = {
                (int)screen.x, // cast a int per togliere spaziature inutili
                (int)screen.y,
                terrain.tileSize,
                terrain.tileSize
            };
            Vector2 pivot = {
                terrain.tileSize/2,
                terrain.tileSize/2
            };
            DrawTexturePro(texture, src, dst, pivot, 0, WHITE);
        }
    }
}
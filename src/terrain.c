#include "terrain.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
        }         
    }
    fclose(file);
    return terrain; // restituisci il terreno
}

void drawTerrain(Terrain terrain, Player player) {
    int resolution = 32; // la risoluzione delle texture dei tile (per ora 32x32)
    Texture texture = terrain.tilesTexture; 
    int textureCols = texture.width/resolution; // il numero di colonne della texture
    for(int row=0; row<terrain.size.y; row++) {
        for(int col=0; col<terrain.size.x; col++) {
            int index = row*terrain.size.x+col; // siccome e' un' array a una dimensione devo calcolare l'inidice
            int currentTileNum = terrain.tileMap[index]; // il tile da piazzare 
            int xTexturePos = currentTileNum%textureCols; // il resto e' la posizione orizzontale nell'immagine
            int yTexturePos = currentTileNum/textureCols; // il risultato e' la posizione verticale nell'immagine
            Vector2 world = { 
                col*terrain.tileSize, 
                row*terrain.tileSize
            }; // la posizione nel mondo
            Vector2 screen = {
                world.x-player.world.x+player.screen.x, 
                world.y-player.world.y+player.screen.y
            }; // la posizione nello schermo
            Rectangle src = {
                xTexturePos*resolution, 
                yTexturePos*resolution, 
                resolution, 
                resolution
            }; // il ritaglio dell'immagine per prendere un solo tile
            Rectangle dst = {
                (int)screen.x, // cast a int per togliere spaziature inutili
                (int)screen.y,
                terrain.tileSize,
                terrain.tileSize
            }; // la posizione e dimensione finale del tile
            Vector2 origin = {
                terrain.tileSize/2,
                terrain.tileSize/2
            }; // origine, la parte centrale del tile
            DrawTexturePro(texture, src, dst, origin, 0, WHITE);
        }
    }
}

void unloadTerrain(Terrain *terrain) {
    UnloadTexture(terrain->tilesTexture);
    free(terrain);
}
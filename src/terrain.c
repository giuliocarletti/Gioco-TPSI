#include "terrain.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Terrain initTerrain() {
    Terrain terrain;

    terrain.xDimension = TERRAIN_WIDTH; // larghezza mappa
    terrain.yDimension = TERRAIN_HEIGHT; // altezza mappa
    terrain.tileSize = TILE_SIZE; // grandezza tile

    terrain.tileMap = (int *)malloc(sizeof(int)*terrain.xDimension*terrain.yDimension); // inizializzazione dell'array
    terrain.tilesTexture = LoadTexture(TERRAIN_TILES_PATH); // caricamento delle texture tile
    SetTextureFilter(terrain.tilesTexture, TEXTURE_FILTER_POINT);

    FILE *file = fopen(TERRAIN_MAP_PATH, "r"); // apertura del file csv

    if(file == NULL) {
        printf("\nErrore apertura mappa: %s\n", TERRAIN_MAP_PATH);
        return terrain;
    }

    for(int row=0; row<terrain.yDimension; row++) { 
        char line[4096]; // buffer
        fgets(line, 4096, file); // prende una riga
        for(int col=0; col<terrain.xDimension; col++) {
            int index = row*terrain.xDimension+col; // indice
            char *info = strtok(col==0? line:NULL, ","); // la riga viene suddivisa 
            terrain.tileMap[index] = atoi(info); // il dato viene trasformato in int
            printf(" %i ", terrain.tileMap[index]);
        }
        printf("\n");
    }
    fclose(file);
    
    int blockedArray[] = BLOCKED_TILES; 
    terrain.blockedTiles.length = N_BLOCKED_TILES;    
    for(int i=0; i<N_BLOCKED_TILES; i++) {
        terrain.blockedTiles.array[i] = blockedArray[i];
    }    

    return terrain; // restituisci il terreno
}

void renderTerrain(Terrain terrain, Player player) {

    int resolution = TILE; // la risoluzione di un tile
    Texture texture = terrain.tilesTexture; 
    int textureCols = texture.width/resolution; // il numero di colonne della texture

    for(int row=0; row<terrain.yDimension; row++) {
        for(int col=0; col<terrain.xDimension; col++) {

            int index = row*terrain.xDimension+col; // siccome e' un' array a una dimensione devo calcolare l'inidice
            int currentTileNum = terrain.tileMap[index]; // il tile da piazzare 

            int xTexturePos = currentTileNum%textureCols; // il resto e' la posizione orizzontale nell'immagine
            int yTexturePos = currentTileNum/textureCols; // il risultato e' la posizione verticale nell'immagine            
            
            Vector2 world = { 
                col*terrain.tileSize, 
                row*terrain.tileSize
            }; // la posizione nel mondo
            Vector2 screen = {
                world.x-player.world.x+player.screen.x, 
                world.y-player.world.y+player.screen.y, 
            }; // la posizione nello schermo               
            Rectangle src = {
                xTexturePos*resolution, 
                yTexturePos*resolution, 
                resolution, 
                resolution
            }; // il ritaglio dell'immagine per prendere un solo tile
            Rectangle dst = {
                (int)screen.x, // cast a int per togliere spazi inutili
                (int)screen.y,
                terrain.tileSize,
                terrain.tileSize
            }; // la posizione e dimensione finale del tile
            Vector2 origin = {
                0,
                0
            }; // origine, la parte centrale del tile
            
            DrawTexturePro(texture, src, dst, origin, 0, WHITE);

            if(player.showStats && isTileBlocked(currentTileNum, terrain)) {        
                Rectangle outline;    
                outline.x = dst.x-origin.x;
                outline.y = dst.y-origin.y;
                outline.width = dst.width;
                outline.height = dst.height;                
                DrawRectangleLinesEx(outline, 2, YELLOW);
            }
        }
    }
}

void unloadTerrain(Terrain *terrain) {
    UnloadTexture(terrain->tilesTexture);
    free(terrain->tileMap); // libera l'array allocato con malloc in initTerrain
    terrain->tileMap = NULL;
}

bool isTileBlocked(int n, Terrain terrain) {
    for(int i=0; i<terrain.blockedTiles.length; i++) {
        if(n == terrain.blockedTiles.array[i]) return true;
    }
    return false;
}
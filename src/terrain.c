#include "terrain.h"

Terrain initTerrain(int dimx, int dimy, int size) {
    Terrain terrain;
    terrain.size.x = dimx; // larghezza mappa
    terrain.size.y = dimy; // altezza mappa
    terrain.tileSize = size; // grandezza tile
    terrain.tileMap = (int *)malloc(sizeof(int)*dimx*dimy); // inizializzazione dell'array
    terrain.tilesTexture = LoadTexture("assets/tiles/floor_tiles.png"); // caricamento delle texture tile
    FILE *file = fopen("assets/maps/map.csv", "r"); // apertura del file csv
    char line[4096]; // buffer
    for(int row=0; row<dimy; row++) { 
        fgets(line, 4096, file); // prende una riga
        for(int col=0; col<dimx; col++) {
            int index = row*dimx+col;
            char *info = strtok(col==0? line:NULL, ","); // la riga viene suddivisa 
            terrain.tileMap[index] = atoi(info); // il dato viene trasformato in int
            printf(" %d", *info);
        }        
        printf("\n");
    }
    fclose(file);
    return terrain; // restituisci il terreno
}

void updateTerrain(Terrain *terrain) {
    
}

void drawTerrain(Terrain terrain, Vector2 playerWorld) {
    int res = 32;
    Texture texture = terrain.tilesTexture;
    for(int row=0; row<terrain.size.y; row++) {
        for(int col=0; col<terrain.size.x; col++) {
            int index = row*terrain.size.x+col;
            int currentTileNum = terrain.tileMap[index];
            int textureCols = texture.width/res;
            int xTexturePos = currentTileNum%textureCols;
            int yTexturePos = currentTileNum/textureCols;
            Vector2 world = {col*terrain.tileSize, row*terrain.tileSize};
            Vector2 screen = {world.x-playerWorld.x, world.y-playerWorld.y};
            Rectangle src = {xTexturePos*res, yTexturePos*res, res, res};
            Rectangle dst = {screen.x, screen.y, terrain.tileSize, terrain.tileSize};
            DrawTexturePro(texture, src, dst, (Vector2){terrain.tileSize/2, terrain.tileSize/2}, 0, WHITE);
        }    
    }
}
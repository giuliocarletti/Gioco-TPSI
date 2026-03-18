#include "terrain.h"
// da finire di scrivere
Terrain initTerrain(int dimx, int dimy) {
    Terrain terrain;
    terrain.dimensionx = dimx;
    terrain.dimensiony = dimy;
    terrain.nTiles = 100;
    terrain.tileMap = (int *)malloc(sizeof(int)*dimx*dimy);
    // caricare le texture
    return terrain;
}

void updateTerrain(Terrain *terrain) {
    
}
void drawTerrain(Terrain terrain) {

}
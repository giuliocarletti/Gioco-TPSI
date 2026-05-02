#include "collision.h"

Vector2 checkCollision(Player player, Terrain terrain) {

    for(int row=0; row<terrain.yDimension; row++) {
        for(int col=0; col<terrain.xDimension; col++) {
            // TILE CORRENTE E LA SUA POSIZiONE
            int currentTile = row*terrain.xDimension+col;
            if(currentTile==25) {
                Vector2 world;
                world.x = col*terrain.tileSize;                 
                world.y = row*terrain.tileSize;
               
            }
            
        }    
    }
}

#include "raylib.h"
#include "player.h"
#include "terrain.h"

const int TILE = 16; // risuluzione 16x16
const int TILE_SIZE = TILE*3; // grandezza tile sullo schermo

int main() 
{
    InitWindow(800, 600, "Gioco TPSI");
    SetTargetFPS(60);
    
    Player player = initiPlayer(400, 225, 180, TILE_SIZE*2);
    Terrain terrain = initTerrain(50, 50, TILE_SIZE);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(BLACK);
        updatePlayer(&player);
        drawPlayer(player);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// per fare il make: mingw32-make su windows, make su linux
// per avviarlo: ./build/raylib-test
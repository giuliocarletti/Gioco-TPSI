#include "raylib.h"
#include "player.h"
#include "terrain.h"

const int TILE = 16; // risuluzione 16x16
const int TILE_SIZE = TILE*6; // grandezza tile sullo schermo
Player player;
Terrain terrain;

void GameLoop();

int main() {
    InitWindow(1000, 750, "Gioco TPSI");
    SetTargetFPS(120);
    player = initiPlayer(TILE_SIZE*25, TILE_SIZE*25, TILE_SIZE*2, TILE_SIZE);
    terrain = initTerrain(50, 50, TILE_SIZE);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        GameLoop();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void GameLoop() {
    updatePlayer(&player);    
    drawTerrain(terrain, player);
    drawPlayer(player);    
}

// per fare il make: mingw32-make su windows, make su linux
// per avviarlo: ./build/raylib-test
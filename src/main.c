#include "raylib.h"
#include "player.h"
#include "terrain.h"
#include "UIManager.h"

const int TILE = 16; // risuluzione 16x16
const int TILE_SIZE = TILE*6; // grandezza tile sullo schermo
Player player;
Terrain terrain;
UIManager uiManager;

int main() {
    InitWindow(1000, 750, "Gioco TPSI");
    SetTargetFPS(120);
    player = initiPlayer(TILE_SIZE*25, TILE_SIZE*25, TILE_SIZE*2, TILE_SIZE);
    terrain = initTerrain(50, 50, TILE_SIZE);
    uiManager = initUIManager();
    bool updateGame = false;
    bool drawGame = false;

    while (!WindowShouldClose()) {
        if(uiManager.currentPanel!=0) {
            updateGame = true;
            drawGame = true;
        }
        if(updateGame) {
            updatePlayer(&player);
        }
        updateUIManager(&uiManager);
        BeginDrawing();
        ClearBackground(BLACK);        
        if(drawGame) {
            drawTerrain(terrain, player);
            drawPlayer(player);
        }        
        drawUIManager(uiManager);
        EndDrawing();
    }        
    CloseWindow();
    return 0;
}

// per fare il make: mingw32-make su windows, make su linux
// per avviarlo: ./build/raylib-test
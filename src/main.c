#include "raylib.h"
#include "player.h"
#include "terrain.h"
#include "UIManager.h"

const int TILE = 16; // risuluzione 16x16
const int TILE_SIZE = TILE*8; // grandezza tile sullo schermo
Player player;
Terrain terrain;
UIManager uiManager;

void update(bool updateGame);
void draw(bool drawGame);
void unload();

int main() {    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // rende ridimensionabile la finestra
    InitWindow(1200, 750, "Gioco TPSI");
    SetWindowMinSize(1200, 750); // grandezza minima
    SetTargetFPS(120);
    SetExitKey(0); // toglie tasti per l'uscita
    player = initiPlayer(TILE_SIZE*25, TILE_SIZE*25, TILE_SIZE*2, TILE_SIZE); // x, y, velocita, grandezza nello schermo
    terrain = initTerrain(50, 50, TILE_SIZE); // grandezza terreno in tile, grandezza di un tile
    uiManager = initUIManager();
    bool updateGame = false; // aggiorna il gioco
    bool drawGame = false; // disegna gli aggiornamenti
    while (!WindowShouldClose()) {
        if(uiManager.currentPanel==1) { // se non sono nel main screen allora fai il loop di gioco
            updateGame = true;
            drawGame = true;
        } else if(uiManager.currentPanel==2) {
            updateGame = false;
            drawGame = true;
        }
        update(updateGame);
        draw(drawGame);
    }    
    CloseWindow();
    unload();
    return 0;
}

void update(bool updateGame) {
    if(updateGame) {
        updatePlayer(&player);
    }
    updateUIManager(&uiManager); // aggiorna la ui
}

void draw(bool drawGame) {
    BeginDrawing(); 
    ClearBackground(BLACK);        
    if(drawGame) {
        drawTerrain(terrain, player);
        drawPlayer(player);
    }        
    drawUIManager(uiManager);
    EndDrawing();
}

void unload() {
    unloadPlayer(&player);
    unloadTerrain(&terrain);
    unloadUIManager(&uiManager);
}


// per fare il make: mingw32-make su windows, make su linux
// per avviarlo: ./build/raylib-test
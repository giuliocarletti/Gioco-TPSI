#include "raylib.h"
#include "game.h"

int main() {    
    
    InitWindow(1200, 750, "Gioco TPSI");    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // rende ridimensionabile la finestra
    SetWindowMinSize(1200, 750); // grandezza minima
    ToggleBorderlessWindowed();
    SetTargetFPS(120);
    SetExitKey(0); // toglie tasti per l'uscita

    Game game = initGame();
    
    while (!WindowShouldClose()) {
        updateGame(&game);
        renderGame(game);
    }     

    closeGame(&game);
    CloseWindow();

    return 0;
}

// per fare il make: mingw32-make su windows, make su linux
// per avviarlo: ./build/raylib-test Gioco-TPSI/build/raylib-test
#include "raylib.h"
#include "game.h"
 
int main() {    
    
    InitWindow(1200, 750, "Gioco TPSI");    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(1200, 750);
    ToggleBorderlessWindowed();
    SetTargetFPS(120);
    SetExitKey(0);
 
    Game game = initGame();
    // fix puntatore player: dopo la copia di initGame il puntatore dentro
    // entities punta al vecchio stack, va aggiornato al game reale in main
    for (int i = 0; i < game.entities.entities.length; i++) {
        if (game.entities.entities.array[i].type == ENTITY_PLAYER) {
            game.entities.entities.array[i].object = &game.player;
            break;
        }
    }
    
    while (!WindowShouldClose()) {
        updateGame(&game);
        renderGame(&game);
    }     
 
    closeGame(&game);
    CloseWindow();
 
    return 0;
}
 
// per fare il make: mingw32-make su windows, make su linux
// per avviarlo: ./build/raylib-test Gioco-TPSI/build/raylib-test
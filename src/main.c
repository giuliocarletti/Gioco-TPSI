#include "raylib.h"

int main() 
{
    InitWindow(800, 450, "Titolo");
    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Schermo vuoto", 190, 200, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// per fare il make: mingw32-make su windows, make su linux
// per avviarlo: ./build/raylib-test
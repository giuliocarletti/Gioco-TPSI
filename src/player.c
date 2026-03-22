#include "player.h"
#include <math.h>

Player initiPlayer(double x, double y, int speed, int size) {
    Player player;
    player.screen.x = x;
    player.screen.y = y;
    player.speed = speed;
    player.size = size;
    player.walkTexture = LoadTexture("assets/player/ASEPRITE FILE-WALK.png");
    player.idleTexture = LoadTexture("assets/player/ASEPRITE FILE-IDLE.png");
    player.isMoving = 0;
    return player;
}

void updatePlayer(Player *player) {   
    float dt = GetFrameTime();
    int inputx = 0;
    int inputy = 0;
    player->isMoving = 0;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        inputx = 1;
        player->direction = 1;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        inputx = -1;
        player->direction = -1;
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        inputy = -1;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))  {
        inputy = 1;
    }
    double magnitude = sqrt(inputx*inputx+inputy*inputy);
    if(magnitude>0) {
        double xDirection = inputx/magnitude;
        double yDirection = inputy/magnitude;
        player->screen.x += xDirection*player->speed*dt;
        player->screen.y += yDirection*player->speed*dt;
        player->isMoving = 1;
    }    
}

void drawPlayer(Player player) {
    /*
    // DISEGNO BOX PLAYER
    int x = player.screen.x-player.size/2;
    int y = player.screen.y-player.size/2;
    DrawRectangle(x, y, player.size, player.size, WHITE);
    */    
    
    int length = player.idleTexture.height; // lunghezza di un quadrato di un frame
    Rectangle src = {0, 0, player.direction==1? length:-length, length}; // ritaglio dell'immagine
    Rectangle dst = {player.screen.x, player.screen.y, player.size, player.size}; // dimensione finale
    Texture2D texture = player.isMoving? player.walkTexture:player.idleTexture; // texture da usare
    double deltaAnimTime = 1/(double)(texture.width/length); // calcolo del tempo 1/iFrameDellAnimazione
    double deltaTime = GetTime()-floor(GetTime()); // calcolo del'intervallo di tempo in max di un secondo
    int currentFrame = deltaTime/deltaAnimTime; 
    src.x = currentFrame*length; // spostamento del ritaglio immagine per il prossimo frame
    DrawTexturePro(texture, src, dst, (Vector2) {player.size/2,player.size/2}, 0, WHITE);

    char text[50];
    sprintf(text, "Frame animazione player: %i", currentFrame);
    DrawText(text, 20, 20, 20, WHITE);
}
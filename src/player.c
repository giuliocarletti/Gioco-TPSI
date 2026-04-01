#include "player.h"
#include <stdio.h>
#include <math.h>

Player initiPlayer(double x, double y, int speed, int size) {
    Player player;
    player.world.x = x;
    player.world.y = y;
    player.scroll.x = x;
    player.scroll.y = y;
    player.speed = speed;
    player.size = size;
    player.textures[0] = LoadTexture("assets/player/ASEPRITE FILE-IDLE.png");
    player.textures[1] = LoadTexture("assets/player/ASEPRITE FILE-WALK.png");
    player.textures[2] = LoadTexture("assets/player/ASEPRITE FILE-JUMP.png");
    player.state = 0;
    return player;
}

void updatePlayer(Player *player) {   
    float dt = GetFrameTime();
    player->scroll.x += (player->world.x-player->scroll.x)*2*dt;
    player->scroll.y += (player->world.y-player->scroll.y)*2*dt;
    player->screen.x = GetScreenWidth()/2+(player->world.x-player->scroll.x);
    player->screen.y = GetScreenHeight()/2+(player->world.y-player->scroll.y);
    int inputx = 0;
    int inputy = 0;
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
    if (IsKeyDown(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))  {
        player->state = 2;
        player->timer = 0.001;
    }
    if (IsKeyPressed(KEY_O))  {
        player->showStats = player->showStats? 0:1;
    }
    double magnitude = sqrt(inputx*inputx+inputy*inputy);
    if(magnitude>0) {
        double xDirection = inputx/magnitude;
        double yDirection = inputy/magnitude;
        player->world.x += xDirection*player->speed*dt;
        player->world.y += yDirection*player->speed*dt;
    }    
    if(player->timer>0) {
        player->timer += GetFrameTime();
        if(player->timer>1) player->timer=0;
    } else {
       player->state = magnitude>0? 1:0;
    }
}

void drawPlayer(Player player) {    
    Texture2D texture = player.textures[player.state];
    int length = texture.height;
    double deltaAnimTime = 1/(double)(texture.width/length); // calcolo del tempo 1/iFrameDellAnimazione
    double deltaTime = GetTime()-floor(GetTime()); // calcolo del'intervallo di tempo in max di un secondo
    int currentFrame = deltaTime/deltaAnimTime; 
    int xTexturePos = currentFrame*length;
    int yTexturePos = 0;
    Rectangle src = {
        xTexturePos, 
        yTexturePos, 
        player.direction==1? length:-length, 
        length
    }; // ritaglio dell'immagine
    Rectangle dst = {
        (int)player.screen.x, 
        (int)player.screen.y, 
        player.size, 
        player.size
    }; // dimensione finale
    Vector2 pivot = {
        player.size/2,
        player.size/2
    }; // punto da cui viene "preso" (il punto di rotazione e posizionamento)
    DrawTexturePro(texture, src, dst, pivot, 0, WHITE);
    // CONTROLLO ANIMAZIONE
    if(player.showStats) {
        int fontSize = 20;
        int xPadding = 40;
        char text[50];
        DrawRectangle(20, 20, 400, 120, DARKGRAY);
        sprintf(text, "Frame animazione Player: %i", currentFrame);
        DrawText(text, xPadding, 40, fontSize, LIGHTGRAY);    
        sprintf(text, "Stato del Player: %i", player.state);
        DrawText(text, xPadding, 70, fontSize, LIGHTGRAY);
        sprintf(text, "Timer del Player: %f", player.timer);
        DrawText(text, xPadding, 100, fontSize, LIGHTGRAY);
    }    
}
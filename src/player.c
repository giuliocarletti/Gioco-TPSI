#include "player.h"
#include <math.h>

Player initiPlayer(double x, double y, int speed, int size) {
    Player player;
    player.screenx = x;
    player.screeny = y;
    player.speed = speed;
    player.size = size;
    // caricare texture
    return player;
}

void updatePlayer(Player *player) {   
    int inputx = 0;
    int inputy = 0;     
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        inputx = 1;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        inputx = -1;
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
        player->screenx += xDirection*player->speed;
        player->screeny += yDirection*player->speed;
    }
}

void drawPlayer(Player player) {    
    int x = player.screenx-player.size/2;
    int y = player.screeny-player.size/2;
    DrawRectangle(x, y, player.size, player.size, RED);
}
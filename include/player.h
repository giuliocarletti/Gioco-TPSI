#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "config.h"

typedef struct {
    Vector2 world;
    Vector2 screen;
    Vector2 scroll;
    int speed;
    int size;
    int state; // 0.idle, 1.walk, 2.jumping
    int direction;
    bool showStats;
    double timer;
    Texture2D textures[3];    
} Player;

Player initPlayer();
void renderPlayer(Player player);
void updatePlayer(Player *player);
void unloadPlayer(Player *player);

#endif
#ifndef PLAYER_H // Serve per includere piu volte il file
#define PLAYER_H
#include "raylib.h"
#include <stdio.h>

typedef struct {
    Vector2 world;
    Vector2 screen;
    int speed;
    int size;    
    int isMoving;
    int direction;
    Texture2D walkTexture;
    Texture2D idleTexture;
} Player;

Player initiPlayer(double x, double y, int speed, int size);
void updatePlayer(Player *player);
void drawPlayer(Player player);

#endif
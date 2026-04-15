#ifndef PLAYER_H // Serve per includere piu volte il file
#define PLAYER_H
#include "raylib.h"

typedef struct {
    Vector2 world;
    Vector2 screen;
    Vector2 scroll;
    int speed;
    int size;
    int state; // 0.idle, 1.walk, 2.jumping    
    int direction;
    int showStats;    
    double timer;    
    Texture2D textures[3];
} Player;

Player initiPlayer(double x, double y, int speed, int size);
void drawPlayer(Player player);
void updatePlayer(Player *player);
void unloadPlayer(Player *player);

#endif
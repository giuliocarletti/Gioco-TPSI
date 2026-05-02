#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "config.h"

typedef struct {
    Vector2 world;
    Vector2 screen;
    Vector2 scroll;
    int health;
    int speed;
    int size;
    int state; // 0.idle, 1.walk, 2.hurt, 3.death, 4.attack
    int direction;
    bool showStats;
    float timer;
    float attackTimer; // durata animazione attacco
    Texture2D textures[5]; // 0.idle, 1.walk, 2.hurt, 3.death, 4.attack
    Vector2 screenSize;    
} Player;

Player initPlayer();
void renderPlayer(Player player);
void updatePlayer(Player *player);
void unloadPlayer(Player *player);

#endif
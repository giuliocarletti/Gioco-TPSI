#ifndef ENEMY_H
#define ENEMY_H
 
#include "raylib.h"
#include "config.h"
#include "player.h"
 
typedef enum {
    CARLI,
    ARI,
    GIULIO
} EnemyType;
 
typedef struct {
    EnemyType type;
    Vector2 world;
    Vector2 screen;
    int health;
    bool isAlive;
    int speed;
    int size;
    int state;      // 0.idle, 1.walk, 2.hurt, 3.death
    int direction;  // 1.destra, -1.sinistra
    double timer;
    double timerMovement; // timer per cambio direzione random
    int randomDirX;       // direzione random corrente X
    int randomDirY;       // direzione random corrente Y
    Texture2D textures[4]; // 0.idle, 1.walk, 2.hurt, 3.death
    Rectangle hitbox;
    bool showHitbox;
} Enemy;
 
Enemy initEnemy(EnemyType type, Vector2 spawn);
void updateEnemy(Enemy *enemy, Player player);
void renderEnemy(Enemy enemy);
void unloadEnemy(Enemy *enemy);
 
#endif
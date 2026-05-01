#ifndef SPAWNER_H
#define SPAWNER_H
 
#include "raylib.h"
#include "enemy.h"
#include "player.h"
 
typedef struct {    
    struct {
        Enemy *array;
        int length;
    } enemies;
    int enemyCount;
} Spawner;
 
Spawner initSpawner(int nEnemy, Vector2 playerWorld);
void updateEnemies(Spawner *spawner, Player player);
void renderEnemies(Spawner spawner);
void unloadSpawner(Spawner *spawner);
 
#endif
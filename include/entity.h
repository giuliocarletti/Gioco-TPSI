#ifndef ENTITY_H
#define ENTITY_H
 
#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include "terrain.h"
 
typedef enum {
    ENTITY_PLAYER,
    ENTITY_ENEMY
} EntityType;
 
typedef struct {
    EntityType type;
    Vector2 world;
    Rectangle hitbox;
    int speed;
    void *object;       // puntatore a Player o Enemy    
} Entity;
 
typedef struct {
    struct {
        Entity *array; // array di entita'
        int length;
    } entities;
    int enemyCount;
    Terrain terrain;
} EntitiesManager;
 
EntitiesManager initEntitiesManager(int nEnemy, Player *player, Vector2 playerWorld, Terrain terrain);
void updateEntitiesManager(EntitiesManager *entityManager, Player *player);
void renderEntitiesManager(EntitiesManager *entityManager);
void unloadEntitiesManager(EntitiesManager *entityManager);
 
#endif
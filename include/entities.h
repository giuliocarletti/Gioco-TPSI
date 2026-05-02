#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

typedef enum {
    PLAYER,
    ENEMY
} EntityType;

typedef struct {
    EntityType type;
    int yCoordinates;
    void *object;
} Entity;

typedef struct {
    struct {
        Entity *array; // array di entita'
        int length;
    } entities;
} EntitiesManager;

EntitiesManager initEntititesManager(int nEntity);
void updateEntitiesManager(EntitiesManager *EntitiesManager);
void renderEntitiesManager(EntitiesManager  EntitiesManager);
void unloadEntitiesManager(EntitiesManager *EntitiesManager);

#endif
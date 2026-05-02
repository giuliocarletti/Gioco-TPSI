#include "entity.h"
#include "config.h"
#include <stdlib.h>
#include <math.h>
 
static Vector2 RandomSpawnPosition(Vector2 playerWorld) {
    float minDistance = 5 * TILE_SIZE;
    Vector2 position;
    do {
        position = (Vector2){
            GetRandomValue(0, (TERRAIN_WIDTH - 1) * TILE_SIZE),
            GetRandomValue(0, (TERRAIN_HEIGHT - 1) * TILE_SIZE)
        };
        float dx = position.x - playerWorld.x;
        float dy = position.y - playerWorld.y;
        float distance = sqrt(dx*dx + dy*dy);
        if (distance >= minDistance) break;
    } while (1);
    return position;
}
 
static EnemyType RandomEnemyType() {
    switch (GetRandomValue(0, 2)) {
        case 0:  return CARLI;
        case 1:  return ARI;
        case 2:  return GIULIO;
        default: return CARLI;
    }
}
 

static int compareEntityY(const void *a, const void *b) {
    const Entity *ea = (const Entity *)a;
    const Entity *eb = (const Entity *)b;
    if (ea->yCoordinates < eb->yCoordinates) return -1;
    if (ea->yCoordinates > eb->yCoordinates) return  1;
    return 0;
}
 
EntitiesManager initEntitiesManager(int nEnemy, Player *player, Vector2 playerWorld) {
    EntitiesManager em;
    em.enemyCount = nEnemy;
    em.entities.length = nEnemy + 1; // nemici + player
    em.entities.array  = malloc(sizeof(Entity) * em.entities.length);
 
    // Slot 0: player
    em.entities.array[0].type         = ENTITY_PLAYER;
    em.entities.array[0].object       = player;
    em.entities.array[0].yCoordinates = player->world.y;
 
    // Slot 1..nEnemy: nemici
    for (int i = 0; i < nEnemy; i++) {
        Enemy *enemy = malloc(sizeof(Enemy));
        Vector2 position = RandomSpawnPosition(playerWorld);
        EnemyType type   = RandomEnemyType();
        *enemy = initEnemy(type, position);
 
        em.entities.array[i + 1].type         = ENTITY_ENEMY;
        em.entities.array[i + 1].object       = enemy;
        em.entities.array[i + 1].yCoordinates = enemy->world.y;
    }
 
    return em;
}

void updateEntitiesManager(EntitiesManager *entityManager, Player *player) {
    for (int i = 0; i < entityManager->entities.length; i++) {
        Entity *e = &entityManager->entities.array[i];
 
        if (e->type == ENTITY_ENEMY) {
            updateEnemy((Enemy *)e->object, *player);
            e->yCoordinates = ((Enemy *)e->object)->world.y;
        } else {
            // aggiorna yCoordinates del player (il player e' gia' aggiornato in game.c)
            e->yCoordinates = player->world.y;
        }
    }
}
 
void renderEntitiesManager(EntitiesManager *entityManager) {
    qsort(
        entityManager->entities.array,
        entityManager->entities.length,
        sizeof(Entity),
        compareEntityY
    );
 
    for (int i = 0; i < entityManager->entities.length; i++) {
        Entity *e = &entityManager->entities.array[i];
        if (e->type == ENTITY_PLAYER) {
            renderPlayer(*(Player *)e->object);
        } else {
            renderEnemy(*(Enemy *)e->object);
        }
    }
}

void unloadEntitiesManager(EntitiesManager *entityManager) {
    for (int i = 0; i < entityManager->entities.length; i++) {
        Entity *e = &entityManager->entities.array[i];
        if (e->type == ENTITY_ENEMY) {
            unloadEnemy((Enemy *)e->object);
            free(e->object);
            e->object = NULL;
        }
    }
    free(entityManager->entities.array);
    entityManager->entities.array  = NULL;
    entityManager->entities.length = 0;
}
 
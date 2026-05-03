#include "entity.h"
#include "config.h"
#include <stdlib.h>
#include <math.h>

static bool checkTerrainCollision(Rectangle entityHitbox, Terrain terrain) {
    int tiles = terrain.yDimension*terrain.xDimension;    
    for(int i=0; i<tiles; i++) {
        int row = i/terrain.yDimension;
        int col = i%terrain.xDimension;
        int currentTile = terrain.tileMap[i];
        
        if(isTileBlocked(currentTile, terrain)) {
            Rectangle tileHitbox;
            tileHitbox.x = col*terrain.tileSize;
            tileHitbox.y = row*terrain.tileSize;
            tileHitbox.width = TILE_SIZE;
            tileHitbox.height = TILE_SIZE;
            if(CheckCollisionRecs(entityHitbox, tileHitbox))
                return true;
        }
    }    
    return false;
}

static void getEntityBounds(Entity *entity, Terrain terrain, bool *blockedDir) {
    int directions = 4; // est, ovest, sud, nord
    float dt = GetFrameTime();
    int xOffsets[4] = { entity->speed * 2 * dt, -entity->speed * 2 * dt, 0, 0 };
    int yOffsets[4] = { 0, 0, entity->speed * 2 * dt , -entity->speed * 2 * dt };
        
    for(int i=0; i<directions; i++) {  
        Rectangle bounds;
        bounds.x = entity->world.x + entity->hitbox.x + xOffsets[i];
        bounds.y = entity->world.y + entity->hitbox.y + yOffsets[i];
        bounds.width = entity->hitbox.width;
        bounds.height = entity->hitbox.height;
        blockedDir[i] = checkTerrainCollision(bounds, terrain);        
    }                    
    
}
 
static Vector2 RandomSpawnPosition(Vector2 playerWorld, Terrain terrain) {
    float minDistance = 5*TILE_SIZE;    
    bool validPosition = false;
    Vector2 position;
    
    while(!validPosition) {
        position.x = GetRandomValue(0, (TERRAIN_WIDTH - 1) * TILE_SIZE);
        position.y = GetRandomValue(0, (TERRAIN_HEIGHT - 1) * TILE_SIZE);
        
        float dx = position.x - playerWorld.x;
        float dy = position.y - playerWorld.y;
        float distance = sqrt(dx*dx + dy*dy);
       
        Rectangle box;
        box.width = TILE_SIZE*2;
        box.height = TILE_SIZE*2;
        box.x = position.x-box.width/2;
        box.y = position.y-box.height/2;
        

        if (distance >= minDistance && !checkTerrainCollision(box, terrain)) {
            validPosition = true;
        }
    }   
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
    if (ea->world.y < eb->world.y) return -1;
    if (ea->world.y > eb->world.y) return  1;
    return 0;
}
 
EntitiesManager initEntitiesManager(int nEnemy, Player *player, Vector2 playerWorld, Terrain terrain) {
    EntitiesManager em;
    em.terrain = terrain;
    em.enemyCount = nEnemy;
    em.entities.length = nEnemy + 1; // nemici + player
    em.entities.array = malloc(sizeof(Entity) * em.entities.length);
 
    // Slot 0: player
    em.entities.array[0].type = ENTITY_PLAYER;
    em.entities.array[0].object = player;
    em.entities.array[0].world.y = player->world.y;
    em.entities.array[0].world.x = player->world.x;
    em.entities.array[0].hitbox = player->hitbox;    
 
    // Slot 1..nEnemy: nemici
    for (int i = 0; i < nEnemy; i++) {
        Enemy *enemy = malloc(sizeof(Enemy));
        Vector2 position = RandomSpawnPosition(playerWorld, terrain);
        EnemyType type = RandomEnemyType();
        *enemy = initEnemy(type, position);
 
        em.entities.array[i+1].type = ENTITY_ENEMY;
        em.entities.array[i+1].object = enemy;
        em.entities.array[i+1].world.y = enemy->world.y;
        em.entities.array[i+1].world.x = enemy->world.x;
        em.entities.array[i+1].hitbox = enemy->hitbox;
    }
 
    return em;
}

void updateEntitiesManager(EntitiesManager *entityManager, Player *player) {
    for (int i = 0; i < entityManager->entities.length; i++) {
        Entity *e = &entityManager->entities.array[i];

        if (e->type == ENTITY_ENEMY) {
            Enemy *enemy = (Enemy*)e->object;
            updateEnemy(enemy, *player);
            e->world.y = enemy->world.y;
            e->world.x = enemy->world.x;
            e->speed = enemy->speed;
            getEntityBounds(e, entityManager->terrain, enemy->blockedDir);
        } else {
            // aggiorna yCoordinates del player (il player e' gia' aggiornato in game.c)
            e->world.y = player->world.y;
            e->world.x = player->world.x;
            e->speed = player->speed;
            getEntityBounds(e, entityManager->terrain, player->blockedDir);
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
            renderPlayer(*(Player*)e->object);
        } else {
            renderEnemy(*(Enemy*)e->object);
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
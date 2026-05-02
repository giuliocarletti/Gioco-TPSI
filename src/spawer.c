#include "spawner.h"
#include "stdlib.h"
#include "math.h"
 
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
        if(distance >= minDistance) break;
    } while(1);
    return position;
}
 
static EnemyType RandomEnemyType() {
    switch(GetRandomValue(0, 2)) {
        case 0: return CARLI;
        case 1: return ARI;
        case 2: return GIULIO;
        default: return CARLI;
    }
}
 
Spawner initSpawner(int nEnemy, Vector2 playerWorld) {
    Spawner spawner;
    spawner.enemies.length = nEnemy;
    spawner.enemies.array = malloc(sizeof(Enemy) * nEnemy);
    spawner.enemyCount = nEnemy;
    for(int i = 0; i < nEnemy; i++) {
        Vector2 position = RandomSpawnPosition(playerWorld);
        EnemyType type = RandomEnemyType();
        spawner.enemies.array[i] = initEnemy(type, position);
    }
    return spawner;
}
 
void updateEnemies(Spawner *spawner, Player player) {
    for(int i = 0; i < spawner->enemies.length; i++) {
        updateEnemy(&spawner->enemies.array[i], player);

        /*if(player.state == 4) {
            damageEnemy(&spawner->enemies.array[i], player.attackBox); // idea per colpire i nemici con l'attacco del player da implementare 
        }*/
    } // <-- mancava questa
}
 
void renderEnemies(Spawner spawner) {
    for(int i = 0; i < spawner.enemies.length; i++) {
        renderEnemy(spawner.enemies.array[i]);
    }
}
 
void unloadSpawner(Spawner *spawner) {
    for(int i = 0; i < spawner->enemies.length; i++) {
        unloadEnemy(&spawner->enemies.array[i]);
    }
    free(spawner->enemies.array);
    spawner->enemies.array = NULL;
    spawner->enemies.length = 0;
}
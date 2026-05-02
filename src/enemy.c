#include "enemy.h"
#include <stdlib.h>
#include <math.h>
 
Enemy initEnemy(EnemyType type, Vector2 spawn) {
    Enemy enemy;
    enemy.speed = 2.5*TILE_SIZE;
    enemy.size = 1.5*TILE_SIZE;
    enemy.world = spawn;
    enemy.timer = 0;
    enemy.timerMovement = 0;
    enemy.state = 0;
    enemy.direction = 1;
    enemy.randomDirX = 0;
    enemy.randomDirY = 0;
    enemy.type = type;
    switch(type) {
        case CARLI:
            enemy.textures[0] = LoadTexture(CARLI_IDLE_PATH);
            enemy.textures[1] = LoadTexture(CARLI_WALK_PATH);
            enemy.textures[2] = LoadTexture(CARLI_HURT_PATH);
            enemy.textures[3] = LoadTexture(CARLI_DEATH_PATH);
            break;
        case ARI:
            enemy.textures[0] = LoadTexture(ARI_IDLE_PATH);
            enemy.textures[1] = LoadTexture(ARI_WALK_PATH);
            enemy.textures[2] = LoadTexture(ARI_HURT_PATH);
            enemy.textures[3] = LoadTexture(ARI_DEATH_PATH);
            break;
        case GIULIO:
            enemy.textures[0] = LoadTexture(GIULIO_IDLE_PATH);
            enemy.textures[1] = LoadTexture(GIULIO_WALK_PATH);
            enemy.textures[2] = LoadTexture(GIULIO_HURT_PATH);
            enemy.textures[3] = LoadTexture(GIULIO_DEATH_PATH);
            break;
        default:
            break;
    }
    return enemy;
}
 
void updateEnemy(Enemy *enemy, Player player) {    
    float dt = GetFrameTime();
 
    // distanza dal player (coordinate mondo)
    float dx = player.world.x - enemy->world.x;
    float dy = player.world.y - enemy->world.y;
    float distance = sqrt(dx*dx + dy*dy);
    float aggroRange = 5*TILE_SIZE;
 
    int inputx = 0;
    int inputy = 0;
 
    if(distance < aggroRange) {
        // INSEGUIMENTO: si muove verso il player
        enemy->speed = 2*TILE_SIZE;
        inputx = (dx > 0) ? 1 : -1;
        inputy = (dy > 0) ? 1 : -1;        
        if(fabs(dx) < TILE_SIZE/2) inputx = 0;
        if(fabs(dy) < TILE_SIZE/2) inputy = 0;
    } else {
        // MOVIMENTO RANDOM: cambia direzione ogni 1-3 secondi
        enemy->speed = 1*TILE_SIZE;
        enemy->timerMovement -= dt;
        if(enemy->timerMovement <= 0) {
            enemy->randomDirX = GetRandomValue(-1, 1);
            enemy->randomDirY = GetRandomValue(-1, 1);
            enemy->timerMovement = (float)GetRandomValue(100, 300) / 100.0f;
        }
        inputx = enemy->randomDirX;
        inputy = enemy->randomDirY;
    }
 
    if(inputx != 0) enemy->direction = (inputx > 0) ? 1 : -1;
 
    double magnitude = sqrt(inputx*inputx + inputy*inputy);
    if(magnitude > 0) {
        double xDirection = inputx / magnitude;
        double yDirection = inputy / magnitude;
        enemy->world.x += xDirection * enemy->speed * dt;
        enemy->world.y += yDirection * enemy->speed * dt;
    }
 
    enemy->state = magnitude > 0 ? 1 : 0; // 0.idle, 1.walk
 
    enemy->timer += dt;
    if(enemy->timer > 1) enemy->timer = 0;
 
    enemy->screen.x = enemy->world.x - player.world.x + player.screen.x;
    enemy->screen.y = enemy->world.y - player.world.y + player.screen.y;
}
 
void renderEnemy(Enemy enemy) {
    Texture2D texture = enemy.textures[enemy.state];
    int length = texture.height;
    double deltaAnimTime = 1/(double)(texture.width/length);
    int currentFrame = enemy.timer/deltaAnimTime;
    int xTexturePos = currentFrame*length;
    int yTexturePos = 0;
    Rectangle src = {
        xTexturePos, 
        yTexturePos, 
        enemy.direction==1? length:-length,
        length
    };
    Rectangle dst = {
        (int)enemy.screen.x, 
        (int)enemy.screen.y, 
        enemy.size, 
        enemy.size
    };
    Vector2 pivot = {
        enemy.size/2,
        enemy.size/2
    };
    DrawTexturePro(texture, src, dst, pivot, 0, WHITE);
}
 
void unloadEnemy(Enemy *enemy) {        
    UnloadTexture(enemy->textures[0]);
    UnloadTexture(enemy->textures[1]);
    UnloadTexture(enemy->textures[2]);
    UnloadTexture(enemy->textures[3]);
    // textures[4] (attack) da aggiungere
}
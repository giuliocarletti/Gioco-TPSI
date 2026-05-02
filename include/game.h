#ifndef GAME_H
#define GAME_H
 
#include "raylib.h"
#include "config.h"
#include "player.h"
#include "terrain.h"
#include "entity.h"
#include "UI.h"
 
typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED,    
    STATE_SETTINGS
} PlayState;
 
typedef struct {    
    Player player;
    Terrain terrain;
    PlayState state;
    EntitiesManager entities;
    UI ui;
    int screenHeight;
    int screenWidth;
} Game;
 
Game initGame();
void updateGame(Game *game);
void renderGame(Game *game);
void closeGame(Game *game);
 
#endif
 
#ifndef CONFIG_H
#define CONFIG_H

#include "raylib.h"

#define TILE 16
#define TILE_SIZE 8*16
#define TERRAIN_HEIGHT 80
#define TERRAIN_WIDTH 80

#define FONT_REGUALAR_PATH "assets/fonts/PixelifySans-Regular.ttf"
#define FONT_MEDIUM_PATH "assets/fonts/PixelifySans-Medium.ttf"
#define FONT_SEMIBOLD_PATH "assets/fonts/PixelifySans-SemiBold.ttf"
#define FONT_BOLD_PATH "assets/fonts/PixelifySans-Bold.ttf"

#define PLAYER_IDLE_PATH "assets/sprites/lucaIdle.png"
#define PLAYER_WALK_PATH "assets/sprites/lucaWalk.png"
#define PLAYER_HURT_PATH "assets/sprites/lucaHurt.png"
#define PLAYER_DEATH_PATH "assets/sprites/lucaDeath.png"
#define PLAYER_ATTACK_PATH "assets/sprites/lucaAttack.png"

#define CARLI_IDLE_PATH "assets/sprites/carliIdle.png" 
#define CARLI_WALK_PATH "assets/sprites/carliWalk.png"
#define CARLI_HURT_PATH "assets/sprites/carliHurt.png"
#define CARLI_DEATH_PATH "assets/sprites/carliDeath.png"

#define ARI_IDLE_PATH "assets/sprites/ariIdle.png"
#define ARI_WALK_PATH "assets/sprites/ariWalk.png"
#define ARI_HURT_PATH "assets/sprites/ariHurt.png"
#define ARI_DEATH_PATH "assets/sprites/ariDeath.png"

#define GIULIO_IDLE_PATH "assets/sprites/giulioIdle.png"
#define GIULIO_WALK_PATH "assets/sprites/giulioWalk.png"
#define GIULIO_HURT_PATH "assets/sprites/giulioHurt.png"
#define GIULIO_DEATH_PATH "assets/sprites/giulioDeath.png"

#define TERRAIN_TILES_PATH "assets/tiles/terrain_tiles.png"
#define TERRAIN_MAP_PATH "assets/maps/terrain_map.csv"

#define COLOR_PRIMARY   (Color){34,  40,  49,  255}
#define COLOR_SECONDARY (Color){57,  62,  70,  255}
#define COLOR_TERTIARY  (Color){223, 208, 184, 255}

#define N_BLOCKED_TILES  5
#define BLOCKED_TILES { 21, 23, 25, 33, 35 }

#endif
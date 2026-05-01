#ifndef CONFIG_H
#define CONFIG_H

#include "raylib.h"

#define TILE_SIZE 16*8
#define TERRAIN_HEIGHT 50
#define TERRAIN_WIDTH 50

#define FONT_REGUALAR_PATH "assets/fonts/PixelifySans-Regular.ttf"
#define FONT_MEDIUM_PATH "assets/fonts/PixelifySans-Medium.ttf"
#define FONT_SEMIBOLD_PATH "assets/fonts/PixelifySans-SemiBold.ttf"
#define FONT_BOLD_PATH "assets/fonts/PixelifySans-Bold.ttf"

#define PLAYER_IDLE_PATH "assets/player/ASEPRITE FILE-IDLE.png"
#define PLAYER_WALK_PATH "assets/player/ASEPRITE FILE-WALK.png"
#define PLAYER_JUMP_PATH "assets/player/ASEPRITE FILE-JUMP.png"

#define TERRAIN_TILES_PATH "assets/tiles/floor_tiles.png"
#define TERRAIN_MAP_PATH "assets/maps/map.csv"

#define COLOR_PRIMARY (Color){34, 40, 49, 255}
#define COLOR_SECONDARY (Color){57, 62, 70, 255}
#define COLOR_TERTIARY (Color){223, 208, 184, 255}

#endif
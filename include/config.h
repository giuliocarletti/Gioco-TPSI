#ifndef CONFIG_H
#define CONFIG_H
#include "raylib.h"

// FONT PATHS - UIManager
#define REGULAR_FONT_PATH "assets/fonts/PixelifySans-Regular.ttf"
#define MEDIUM_FONT_PATH "assets/fonts/PixelifySans-Medium.ttf"
#define SEMI_BOLD_FONT_PATH "assets/fonts/PixelifySans-SemiBold.ttf"
#define BOLD_FONT_PATH "assets/fonts/PixelifySans-Bold.ttf"

// COLORI personalizzati - UIManager
static const Color DARK_GRAY = (Color) {34, 40, 49, 255}; // r, g, b, a
static const Color LIGHT_GRAY = (Color) {57, 62, 70, 255};
static const Color DARK_BROWN = (Color) {148, 137, 121, 255};
static const Color LIGHT_BROWN = (Color) {223, 208, 184, 255};
static const Color DARK_GRAY_T = (Color) {34, 40, 49, 128};
static const Color LIGHT_BROWN_T = (Color) {223, 208, 184, 128};

// TEXTURES PATHS - player
#define WALK_PLAYER_PATH "assets/player/ASEPRITE FILE-WALK.png"
#define IDLE_PLAYER_PATH "assets/player/ASEPRITE FILE-IDLE.png"
#define JUMP_PLAYER_PATH "assets/player/ASEPRITE FILE-JUMP.png"

// TEXTURES PATH - terrain
#define TILES_PATH "assets/tiles/floor_tiles.png"

// MAP PATH - terrain
#define MAP_PATH "assets/maps/map.csv"

// PANELS - UIManager
#define MAIN_PANEL 0
#define HUD_PANEL 1
#define OPTION_PANEL 2
#define SETTINGS_PANEL 3

#endif
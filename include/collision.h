#ifndef COLLISION_H
#define COLLISION_H

#include "raylib.h"
#include "player.h"
#include "terrain.h"

Vector2 checkCollision(Player player, Terrain terrain);

#endif
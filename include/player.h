#ifndef PLAYER_H // Serve per includere piu volte il file
#define PLAYER_H
#include "raylib.h"

typedef struct {
    double worldx;
    double worldy;
    double screenx;
    double screeny;
    int speed;
    int size;
    Image texture;
} Player;

Player initiPlayer(double x, double y, int speed, int size);
void updatePlayer(Player *player);
void drawPlayer(Player player);

#endif
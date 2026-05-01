#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Player initPlayer() {
    Player player;
    player.world.x = 25*TILE_SIZE;
    player.world.y = 25*TILE_SIZE;
    player.scroll = player.world;
    player.speed = 2*TILE_SIZE;
    player.size = TILE_SIZE;
    player.textures[0] = LoadTexture(PLAYER_IDLE_PATH);
    player.textures[1] = LoadTexture(PLAYER_WALK_PATH);
    player.textures[2] = LoadTexture(PLAYER_HURT_PATH);
    player.textures[3] = LoadTexture(PLAYER_DEATH_PATH);
    player.textures[4] = LoadTexture(PLAYER_ATTACK_PATH);
    player.state = 0; // 0.idle, 1.walk, 2.hurt, 3.death, 4.attack
    player.timer = 0;
    player.health = 100;
    return player;
}

void updatePlayer(Player *player) {   
    float dt = GetFrameTime();
    player->scroll.x += (player->world.x-player->scroll.x)*2*dt; // somma un valore che cresce gradualmenteS
    player->scroll.y += (player->world.y-player->scroll.y)*2*dt; // per dare un animazione di fluidita'
    player->screen.x = GetScreenWidth()/2+(player->world.x-player->scroll.x); // il player sta al centro dello schermo
    player->screen.y = GetScreenHeight()/2+(player->world.y-player->scroll.y); // ma con piccole variazioni date da scroll
    int inputx = 0; // input da tastiera orizzontale
    int inputy = 0; // input da tastiera verticale
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        inputx = 1;
        player->direction = 1; // direzione 1 e' verso destra
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        inputx = -1;
        player->direction = -1; // direzione -1 e' verso sinistra
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        inputy = -1;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))  {
        inputy = 1;
    }
    if (IsKeyDown(KEY_SPACE))  {
        player->state = 4;
    }
    if (IsKeyPressed(KEY_O))  {
        player->showStats = !player->showStats; // vedere le stats del player
    }
    double magnitude = sqrt(inputx*inputx+inputy*inputy);
    if(magnitude>0) {
        double xDirection = inputx/magnitude;
        double yDirection = inputy/magnitude;
        player->world.x += xDirection*player->speed*dt;
        player->world.y += yDirection*player->speed*dt;
    }
    player->state = magnitude>0? 1:0; // 1.walk se si muove, 0.idle altrimenti
    player->timer = player->timer>1? 0:player->timer+dt;
    
}

void renderPlayer(Player player) {    
    Texture2D texture = player.textures[player.state]; // prende la texture dello stato attuale (es. se sta fermo sara' 0)
    int length = texture.height; // lunghezza di un lato di uno sprite (se non si capisce basta guardare l'immagine negli asset)
    double deltaAnimTime = 1/(double)(texture.width/length); // calcolo del tempo 1/iFrameDellAnimazione    
    int currentFrame = player.timer/deltaAnimTime; // corrisponde alla divisione dell'intervallo di tempo fratto il tempo necessario per un frame dell'animazione
    int xTexturePos = currentFrame*length; // per ritaglia lo spritesheet si calcola il frame attuale moltiplicato per la lunghezza di uno sprite
    int yTexturePos = 0; // gli spritesheet hanno tutti solo una riga e quindi l'altezza e' sempre zero
    Rectangle src = { // il rettangolo di ritaglio nello spritesheet
        xTexturePos, 
        yTexturePos, 
        player.direction==1? length:-length, // a seconda della direzione si ritaglia orizzonalmente specchiato o non
        length
    }; // ritaglio dell'immagine
    Rectangle dst = { // la grandezza e posizione finale della texture del player
        (int)player.screen.x, 
        (int)player.screen.y, 
        player.size, 
        player.size
    }; // dimensione finale
    Vector2 pivot = { // il punto di oringine, in questo caso il centro del player
        player.size/2,
        player.size/2
    }; // punto da cui viene "preso" (il punto di rotazione e posizionamento)
    DrawTexturePro(texture, src, dst, pivot, 0, WHITE);
    // CONTROLLO ANIMAZIONE
    if(player.showStats) {
        int fontSize = 20;
        int xPadding = 40;
        char text[50];
        DrawRectangle(20, 20, 400, 120, DARKGRAY);
        sprintf(text, "Frame animazione Player: %i", currentFrame);
        DrawText(text, xPadding, 40, fontSize, LIGHTGRAY);    
        sprintf(text, "Stato del Player: %i", player.state);
        DrawText(text, xPadding, 70, fontSize, LIGHTGRAY);
        sprintf(text, "Timer del Player: %f", player.timer);
        DrawText(text, xPadding, 100, fontSize, LIGHTGRAY);
    }    
}

void unloadPlayer(Player *player) {        
    UnloadTexture(player->textures[0]);
    UnloadTexture(player->textures[1]);
    UnloadTexture(player->textures[2]);
    UnloadTexture(player->textures[3]);
    UnloadTexture(player->textures[4]);    
}
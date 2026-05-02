#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Player initPlayer() {
    Player player;
    player.world.x = TERRAIN_WIDTH/2*TILE_SIZE;
    player.world.y = TERRAIN_HEIGHT/2*TILE_SIZE;
    player.scroll = player.world;
    player.speed = 3*TILE_SIZE;
    player.size = 1.5*TILE_SIZE;
    player.textures[0] = LoadTexture(PLAYER_IDLE_PATH);
    player.textures[1] = LoadTexture(PLAYER_WALK_PATH);
    player.textures[2] = LoadTexture(PLAYER_HURT_PATH);
    player.textures[3] = LoadTexture(PLAYER_DEATH_PATH);
    player.textures[4] = LoadTexture(PLAYER_ATTACK_PATH);
    player.state = 0; // 0.idle, 1.walk, 2.hurt, 3.death, 4.attack
    player.timer = 0;
    player.attackTimer = 0;
    player.health = 100;
    player.hitbox.x = 0.3; // posizione all'interno dello sprite (in %)
    player.hitbox.y = 0.5;
    player.hitbox.width = 0.4;
    player.hitbox.height = 0.4;
    player.showStats = 0;
    return player;
}

void updatePlayer(Player *player) {   

    float dt = GetFrameTime();    

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
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        inputy = 1;
    }
    // attacco: si attiva solo se non si sta gia' attaccando
    if (IsKeyPressed(KEY_SPACE) && player->state != 4) {
        player->state = 4;
        player->attackTimer = 0.4f; // durata attacco in secondi
        player->timer = 0; // resetta animazione subito
    }
    if (IsKeyPressed(KEY_O)) {
        player->showStats = !player->showStats; // vedere le stats del player
    }

    double magnitude = sqrt(inputx*inputx+inputy*inputy);
    if (magnitude > 0) {
        double xDirection = inputx/magnitude;
        double yDirection = inputy/magnitude;
        player->world.x += xDirection*player->speed*dt;
        player->world.y += yDirection*player->speed*dt;
    }

    int prevState = player->state; // salva lo stato PRIMA di aggiornarlo

    // attacco in corso: conta il timer
    if (player->state == 4) {
        player->attackTimer -= dt;
        if (player->attackTimer <= 0) {
            player->state = 0;
            player->attackTimer = 0;
        }
    }

    // aggiorna stato solo se NON sta attaccando
    if (player->state != 4) {
        player->state = magnitude > 0 ? 1 : 0; // 1.walk se si muove, 0.idle altrimenti
    }

    // resetta il timer dell'animazione al cambio di stato
    if (player->state != prevState) {
        player->timer = 0;
    }

    //player->timer = player->timer > 1 ? 0 : player->timer + dt;
    float timerSpeed = player->state == 4 ? 2.5f : 1.0f; // se attacck avanza il timer 4x
    player->timer = player->timer > 1 ? 0 : player->timer + timerSpeed * dt; // avanza il timer in base alla velocita'

    player->scroll.x += (player->world.x - player->scroll.x) * 6 * dt; // somma un valore che cresce gradualmente
    player->scroll.y += (player->world.y - player->scroll.y) * 6 * dt; // per dare un animazione di fluidita'
    player->screen.x = player->screenSize.x/2 + (player->world.x - player->scroll.x); // il player sta al centro dello schermo
    player->screen.y = player->screenSize.y/2 + (player->world.y - player->scroll.y); // ma con piccole variazioni date da scroll
}

void renderPlayer(Player player) {    

    // informazioni riguardante la textura: prima la selezione, dopo le varie configurazioni
    Texture2D texture = player.textures[player.state]; // prende la texture dello stato attuale (es. se sta fermo sara' 0)
    int length = texture.height; // lunghezza di un lato di uno sprite (se non si capisce basta guardare l'immagine negli asset)

    // calcolo del frame attuale
    float deltaAnimTime = 1/(float)(texture.width/length); // calcolo del tempo 1/iFrameDellAnimazione    
    int currentFrame = player.timer/deltaAnimTime; // corrisponde alla divisione dell'intervallo di tempo fratto il tempo necessario per un frame dell'animazione

    // ritaglio immagine
    int xTexturePos = currentFrame*length; // per ritaglia lo spritesheet si calcola il frame attuale moltiplicato per la lunghezza di uno sprite
    int yTexturePos = 0; // gli spritesheet hanno tutti solo una riga e quindi l'altezza e' sempre zero

    Rectangle src = { 
        xTexturePos, 
        yTexturePos, 
        player.direction==1? length:-length, // a seconda della direzione si ritaglia orizzonalmente specchiato o non
        length
    }; // il quadrato di ritaglio nello spritesheet
    Rectangle dst = { 
        (int)player.screen.x, 
        (int)player.screen.y, 
        player.size,
        player.size
    }; // la grandezza e posizione finale della texture del player
    Vector2 pivot = { 
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
                
        Rectangle hitbox = {
            player.size*player.hitbox.x,
            player.size*player.hitbox.y,
            player.size*player.hitbox.width,
            player.size*player.hitbox.height
        };
        Rectangle box = {
            player.screen.x-player.size/2+hitbox.x,
            player.screen.y-player.size/2+hitbox.y,
            hitbox.width,
            hitbox.height
        };         
        
        DrawRectangleLinesEx(box, 2, RED);
    }    
}

void unloadPlayer(Player *player) {        
    UnloadTexture(player->textures[0]);
    UnloadTexture(player->textures[1]);
    UnloadTexture(player->textures[2]);
    UnloadTexture(player->textures[3]);
    UnloadTexture(player->textures[4]);
}
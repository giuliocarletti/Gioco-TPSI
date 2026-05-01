#include "game.h"

Game initGame() {
    Game game;
    game.state = STATE_PLAYING;
    game.player = initPlayer();
    game.terrain = initTerrain();
    game.ui = initUI();
    return game;
}

void updateGame(Game *game) {
    game->screenHeight = GetScreenHeight();
    game->screenWidth = GetScreenWidth();
    game->ui.screenSize.x = game->screenWidth;
    game->ui.screenSize.y = game->screenHeight;
    if(game->state==STATE_PLAYING) {
        updatePlayer(&game->player);
    }
    if(IsKeyPressed(KEY_F1)) {
        ToggleBorderlessWindowed();
    }  
}

void renderGame(Game game) {
    BeginDrawing();
    ClearBackground(BLACK);
    if(game.state==STATE_PLAYING) {
        renderTerrain(game.terrain, game.player);
        renderPlayer(game.player);
    }    
    renderUI(game.ui);
    EndDrawing();    
}

void closeGame(Game *game) {    
    unloadPlayer(&game->player);
    unloadTerrain(&game->terrain);
    unloadUI(&game->ui);
}

#include "game.h"
 
Game initGame() {
    Game game;
    game.state = STATE_PLAYING;
    game.player = initPlayer();
    game.terrain = initTerrain();
    game.spawner = initSpawner(20, game.player.world);
    game.ui = initUI();
    return game;
}
 
void updateGame(Game *game) {
    game->screenHeight = GetScreenHeight();
    game->screenWidth = GetScreenWidth();
    game->ui.screenSize.x = game->screenWidth;
    game->ui.screenSize.y = game->screenHeight;
    game->player.screenSize.x = game->screenWidth;
    game->player.screenSize.y = game->screenHeight;
    if (IsKeyPressed(KEY_O))  {
        game->player.showStats = !game->player.showStats; // vedere le stats del player
        
    }
    if(game->state == STATE_PLAYING) {
        updatePlayer(&game->player);
        updateEnemies(&game->spawner, game->player);
    }
    if(IsKeyPressed(KEY_F1)) {
        ToggleBorderlessWindowed();
    }
}
 
void renderGame(Game game) {
    BeginDrawing();
    ClearBackground(BLACK);
    if(game.state == STATE_PLAYING) {
        renderTerrain(game.terrain, game.player);
        renderEnemies(game.spawner);
        renderPlayer(game.player);
    }
    //renderUI(game.ui); // da attivare quando la UI è pronta
    EndDrawing();
}
 
void closeGame(Game *game) {
    unloadPlayer(&game->player);
    unloadTerrain(&game->terrain);
    unloadSpawner(&game->spawner);
    unloadUI(&game->ui);
}
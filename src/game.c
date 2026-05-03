#include "game.h"
 
Game initGame() {
    Game game;
    game.state = STATE_PLAYING;
    game.player = initPlayer();
    game.terrain = initTerrain();
    game.ui = initUI();
    game.entities = initEntitiesManager(20, &game.player, game.player.world, game.terrain);
    return game;
}
 
void updateGame(Game *game) {

    game->screenHeight = GetScreenHeight();
    game->screenWidth = GetScreenWidth();

    game->ui.screenSize.x = game->screenWidth;
    game->ui.screenSize.y = game->screenHeight;

    game->player.screenSize.x = game->screenWidth;
    game->player.screenSize.y = game->screenHeight;
 
    if (game->state == STATE_PLAYING) {
        updatePlayer(&game->player);
        updateEntitiesManager(&game->entities, &game->player);
    }
 
    if (IsKeyPressed(KEY_F11)) {
        ToggleBorderlessWindowed();
    }
}
 
void renderGame(Game *game) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (game->state == STATE_PLAYING) {
        renderTerrain(game->terrain, game->player);
        renderEntitiesManager(&game->entities);
    }
    //renderUI(game->ui);
    EndDrawing();
}
void closeGame(Game *game) {
    unloadPlayer(&game->player);
    unloadTerrain(&game->terrain);
    unloadEntitiesManager(&game->entities);
    unloadUI(&game->ui);
}
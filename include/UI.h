#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "config.h"
#include "UIcomponents.h"

typedef struct {
    Panel mainScreen;
    Panel settingsScreen;
    
    Vector2 screenSize;

    struct {
        Font regular;
        Font medium;
        Font semibold;
        Font bold;
    } fonts;

} UI;

UI initUI();
void renderUI(UI ui);
void updateUI(UI *ui);
void unloadUI(UI *ui);

#endif
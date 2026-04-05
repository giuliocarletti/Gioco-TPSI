#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include "raylib.h"
#include "UIComponents.h"

typedef struct {
    Button *buttons;
    Label *labels;
    Box *boxes;
    int nButtons;
    int nLabels;
    int nBoxes;
} Panel;

typedef struct {
    int currentPanel;
    Panel panels[3];
} UIManager;

UIManager initUIManager();
Panel setupMainScreen();
Panel setupHUD();
void drawUIManager(UIManager uiManager);
void updateUIManager(UIManager *uiManager);
void unloadUIManager(UIManager *uiManager);

#endif
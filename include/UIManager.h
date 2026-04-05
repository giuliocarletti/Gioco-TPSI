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
Panel setupOptionScreen();
void drawUIManager(UIManager uiManager);
void updateUIManager(UIManager *uiManager);
void checkAction(UIManager *uiManager, char *action);
void unloadUIManager(UIManager *uiManager);

#endif
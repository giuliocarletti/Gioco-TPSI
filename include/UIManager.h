#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include "raylib.h"
#include "UIComponents.h"

typedef struct {
    Button *buttons;
    Label *labels;
    int nButtons;
    int nLabels;
} Panel;

typedef struct {
    int currentPanel;
    Panel panels[3];
} UIManager;

UIManager initUIManager();
Panel setupMainScreen();
Panel setupSettingsMenu();
void drawUIManager(UIManager uiManager);
void updateUIManager(UIManager *uiManager);

#endif
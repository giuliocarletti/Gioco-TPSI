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
    Font regular;
    Font medium;
    Font semibold;
    Font bold;
} Fonts;

typedef struct {    
    int lastPanel;
    int currentPanel;
    int totalPanels;
    double timer;
    double maxTime;
    Panel panels[3];
    Fonts fonts;
} UIManager;

UIManager initUIManager();
Fonts initFonts();
Panel setupMainScreen(Fonts fonts);
Panel setupHUD(Fonts fonts);
Panel setupOptionScreen(Fonts fonts);
Panel setupSettingsScreen(Fonts fonts);
void drawUIManager(UIManager uiManager);
void updateUIManager(UIManager *uiManager);
void checkAction(UIManager *uiManager, char *action);
void unloadUIManager(UIManager *uiManager);

#endif
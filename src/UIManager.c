#include "UIManager.h"
#include <stdlib.h>
#include <stdio.h>

UIManager initUIManager() {
    UIManager uiManager;
    uiManager.currentPanel = 0;
    uiManager.panels[0] = setupMainScreen();
    uiManager.panels[1] = setupSettingsMenu();   
    return uiManager;
}

Panel setupMainScreen() {
    Panel panel;
    panel.nButtons = 3;
    panel.nLabels = 2;
    panel.buttons = (Button*)malloc(sizeof(Button)*panel.nButtons);
    panel.labels = (Label*)malloc(sizeof(Label)*panel.nLabels);
    // SETUP LABELS
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    //Font font = LoadFont("assets/fonts/Jersey15-Regular.ttf"); // questo coso non funziona
    Font font = GetFontDefault();
    Color labelColors[3] = {LIGHTGRAY, WHITE, WHITE};
    panel.labels[0] = initLabel("Gioco Assurdo", font, 80, labelColors);
    panel.labels[1] = initLabel("Gioco creato da giulio e ari", font, 25, labelColors);
    panel.labels[0].position = (Vector2){screenWidth/2, 100};
    panel.labels[1].position = (Vector2){screenWidth/2, 180};
    // SETUP BUTTONS
    Label labelButton1 = initLabel("Gioca", font, 40, labelColors);
    Label labelButton2 = initLabel("Impostazioni", font, 40, labelColors);
    Label labelButton3 = initLabel("Esci", font, 40, labelColors);
    Color buttonColors[3] = {BLUE, DARKBLUE, BLACK};
    Rectangle areas[panel.nButtons];    
    for(int i=0; i<panel.nButtons; i++) {
        areas[i].width = 400;
        areas[i].height = 100;
        areas[i].x = screenWidth/2;
        areas[i].y = (screenHeight/3+50)+(areas[0].height+20)*i;
    }
    panel.buttons[0] = initButton(areas[0], labelButton1, buttonColors);
    panel.buttons[1] = initButton(areas[1], labelButton2, buttonColors);
    panel.buttons[2] = initButton(areas[2], labelButton3, buttonColors);
    return panel;
}

Panel setupSettingsMenu() {
    Panel panel;
    panel.nButtons = 0;
    panel.nLabels = 0;
    return panel;
}

void drawUIManager(UIManager uiManager) {
    Panel panel = uiManager.panels[uiManager.currentPanel];  
    for(int i=0; i<panel.nButtons; i++) {        
        drawButton(panel.buttons[i]);
    }  
    for(int i=0; i<panel.nLabels; i++) {
        drawLabel(panel.labels[i], panel.labels[i].position);
    }    
}

void updateUIManager(UIManager *uiManager) {
    Vector2 mousePosition = GetMousePosition();
    Panel panel = uiManager->panels[uiManager->currentPanel];
    int buttonPressed = -1;
    for(int i=0; i<panel.nButtons; i++) {
        if(updateButton(&panel.buttons[i], mousePosition)) {
            buttonPressed = i;
        }        
    }
    switch (buttonPressed) {
        case 0:
            uiManager->currentPanel = 1;
            break;    
        default:
            break;
    }

}


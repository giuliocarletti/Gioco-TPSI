#include "UIManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

UIManager initUIManager() {    
    UIManager uiManager; // si occupa di gestire tutti i pannelli
    uiManager.currentPanel = 0; // il pannello iniziale (main screen) e' 0
    uiManager.fonts = initFonts();
    uiManager.panels[0] = setupMainScreen(uiManager.fonts); // il pannello della schermata principale
    uiManager.panels[1] = setupHUD(uiManager.fonts); // parte sempre visibile in gioco (vita, item ecc.)
    uiManager.panels[2] = setupOptionScreen(uiManager.fonts);
    uiManager.panels[3] = setupSettingsScreen(uiManager.fonts);
    uiManager.totalPanels = 4;
    uiManager.maxTime = 0.2;
    return uiManager; 
}

Fonts initFonts() {
    Fonts fonts;
    fonts.regular = LoadFontEx(REGULAR_FONT_PATH, 128, 0, 0);
    fonts.medium = LoadFontEx(MEDIUM_FONT_PATH, 128, 0 ,0);
    fonts.semibold = LoadFontEx(SEMI_BOLD_FONT_PATH, 128, 0, 0);
    fonts.bold = LoadFontEx(BOLD_FONT_PATH, 128, 0, 0);
    SetTextureFilter(fonts.regular.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fonts.medium.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fonts.semibold.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fonts.bold.texture, TEXTURE_FILTER_BILINEAR);
    return fonts;
}

Panel setupMainScreen(Fonts fonts) {
    Panel panel; // ogni pannello ha dei puntatori e le grandezze degli array
    panel.nButtons = 3; // 3 bottoni
    panel.nLabels = 2; // 2 testi
    panel.nBoxes = 1; // 1 solo "rettangolo"
    panel.buttons = (Button*)malloc(sizeof(Button)*panel.nButtons);
    panel.labels = (Label*)malloc(sizeof(Label)*panel.nLabels);
    panel.boxes = (Box*)malloc(sizeof(Box)*panel.nBoxes);

    // SETUP LABELS (Le posizioni sono scritte tutte in %, quindi se voglio il centro sara 50)    
    Color labelColors[3] = {DARK_BROWN, WHITE, WHITE}; // colori dei testi
    panel.labels[0] = initLabel("Gioco Assurdo", fonts.semibold, 10, labelColors); // il 10 sta per la % occupata nella finestra
    panel.labels[1] = initLabel("Creato da giulio e ari", fonts.regular, 5, labelColors); // testo, font, %, i colori
    panel.labels[0].sectionPosition = (Vector2){50, 20}; // la posizione va messa manualmente fuori dal "costruttore"
    panel.labels[1].sectionPosition = (Vector2){50, 30}; // le posizioni sono sempre in %, quindi: 50->centro, 30->30% in basso dalla cima della finestra

    // SETUP BUTTONS
    Color buttonColors[3] = {LIGHT_GRAY, DARK_BROWN, DARK_GRAY}; // i colori dei pulsanti, sono 3 per ogni tipo di stato (normale, hover, click)
    Color buttonLabelColors[3] = {DARK_BROWN, LIGHT_BROWN, DARK_BROWN}; // stessa cosa per i testi
    Label labelButtons[panel.nButtons];
    labelButtons[0] = initLabel("Gioca", fonts.medium, 5, buttonLabelColors); // prima creo i testi
    labelButtons[1] = initLabel("Impostazioni", fonts.medium, 5, buttonLabelColors); // senza modificare le loro posizioni
    labelButtons[2] = initLabel("Esci", fonts.medium, 5, buttonLabelColors); // perche sarannno assegnate nella funzione initButton in UIComponents
    Rectangle areas[panel.nButtons]; // le varie aree dei bottoni
    for(int i=0; i<panel.nButtons; i++) { // visto che sono uno sotto all'altro metto un for 
        areas[i].width = 40; // larghezza del bottone in %
        areas[i].height = 12; // altezza in %
        areas[i].x = 50; // posizione al centro della larghezza dello schermo
        areas[i].y = 45+(areas[i].height+2)*i; // posizione base 45, da li aggiungo i bottoni con un padding di 2
        panel.buttons[i] = initButton(areas[i], labelButtons[i], buttonColors); // parametri: area, il testo del bottone, e i colori
    }
    panel.buttons[0].action = "play";
    panel.buttons[1].action = "settings";
    panel.buttons[2].action = "close";
    
    // SETUP BOXES
    panel.boxes[0] = initBox((Rectangle){50, 50, 100, 100}, DARK_GRAY); // inizializzazione del rettangolo colorato (in questo caso usato come sfondo)

    return panel;
}

Panel setupHUD(Fonts fonts) {
    Panel panel;
    panel.nLabels = 0;
    panel.nButtons = 0;
    panel.nBoxes = 0;
    /*
    panel.labels = (Label*)malloc(sizeof(Label)*panel.nLabels);
    panel.buttons = (Button*)malloc(sizeof(Button)*panel.nButtons);
    panel.boxes = (Box*)malloc(sizeof(Box)*panel.nBoxes);

    // COLORI personalizzati
    Color blue = (Color) {56, 82, 180, 255}; // r, g, b, a
    Color lightBlue = (Color) {94, 122, 196, 255};
    Color lightOrange = (Color) {243, 190, 122, 255};
    Color orange = (Color) {240, 141, 57, 255};
    Color blueTransparent = (Color) {56, 82, 180, 128};

    // SETUP LABELS 
    Font font = GetFontDefault(); 
    Color labelColors[3] = {WHITE, orange, lightBlue}; // colori dei testi
    panel.labels[0] = initLabel("Opzioni", font, 6, labelColors); 
    panel.labels[1] = initLabel("Ciao", font, 5, labelColors);
    panel.labels[0].sectionPosition = (Vector2){10, 5};
    panel.labels[1].sectionPosition = (Vector2){8, 90};
    
    // SETUP BUTTONS
    Color buttonColors[3] = {lightBlue, lightOrange, BLACK};
    Color buttonLabelColors[3] = {lightOrange, orange, lightBlue};
    Label labelButtons[panel.nButtons];
    labelButtons[0] = initLabel("Continua", font, 4, buttonLabelColors);
    labelButtons[1] = initLabel("Impostazioni di gioco", font, 4, buttonLabelColors);
    labelButtons[2] = initLabel("Schermata principale", font, 4, buttonLabelColors);
    labelButtons[3] = initLabel("Esci", font, 4, buttonLabelColors);
    Rectangle areas[panel.nButtons];
    for(int i=0; i<panel.nButtons; i++) { 
        areas[i].width = 35;
        areas[i].height = 10;
        areas[i].x = 20;
        areas[i].y = 20+(areas[i].height+2)*i;
        panel.buttons[i] = initButton(areas[i], labelButtons[i], buttonColors);
    }    
    panel.buttons[0].action = "play";
    panel.buttons[1].action = "settings";
    panel.buttons[2].action = "mainscreen";
    panel.buttons[3].action = "close";

    // SETUP BOXES
    panel.boxes[0] = initBox((Rectangle){50, 50, 100, 100}, blueTransparent); 
    panel.boxes[1] = initBox((Rectangle){20, 50, 40, 100}, blue);
    panel.boxes[2] = initBox((Rectangle){50, 5, 100, 10}, orange);
    */
    return panel;
}

Panel setupOptionScreen(Fonts fonts) {
    Panel panel;
    panel.nLabels = 1;
    panel.nButtons = 4;
    panel.nBoxes = 3;
    panel.labels = (Label*)malloc(sizeof(Label)*panel.nLabels);
    panel.buttons = (Button*)malloc(sizeof(Button)*panel.nButtons);
    panel.boxes = (Box*)malloc(sizeof(Box)*panel.nBoxes);

    // SETUP LABELS 
    Color labelColors[3] = {LIGHT_BROWN, WHITE, WHITE}; // colori dei testi
    panel.labels[0] = initLabel("Opzioni", fonts.semibold, 6, labelColors); 
    panel.labels[0].sectionPosition = (Vector2){10, 5};
    
    // SETUP BUTTONS
    Color buttonColors[3] = {LIGHT_GRAY, DARK_BROWN, DARK_GRAY};
    Color buttonLabelColors[3] = {DARK_BROWN, LIGHT_BROWN, DARK_BROWN};
    Label labelButtons[panel.nButtons];
    labelButtons[0] = initLabel("Continua", fonts.medium, 4, buttonLabelColors);
    labelButtons[1] = initLabel("Impostazioni di gioco", fonts.medium, 4, buttonLabelColors);
    labelButtons[2] = initLabel("Schermata principale", fonts.medium, 4, buttonLabelColors);
    labelButtons[3] = initLabel("Esci", fonts.medium, 4, buttonLabelColors);
    Rectangle areas[panel.nButtons];
    for(int i=0; i<panel.nButtons; i++) { 
        areas[i].width = 35;
        areas[i].height = 10;
        areas[i].x = 20;
        areas[i].y = 20+(areas[i].height+2)*i;
        panel.buttons[i] = initButton(areas[i], labelButtons[i], buttonColors);
    }    
    panel.buttons[0].action = "play";
    panel.buttons[1].action = "settings";
    panel.buttons[2].action = "mainscreen";
    panel.buttons[3].action = "close";

    // SETUP BOXES
    panel.boxes[0] = initBox((Rectangle){50, 50, 100, 100}, DARK_GRAY_T);
    panel.boxes[1] = initBox((Rectangle){20, 50, 40, 100}, DARK_GRAY);
    panel.boxes[2] = initBox((Rectangle){50, 5, 100, 10}, LIGHT_GRAY);

    return panel;
}

Panel setupSettingsScreen(Fonts fonts) {
    Panel panel;
    panel.nLabels = 1;
    panel.nButtons = 5;
    panel.nBoxes = 2;
    panel.labels = (Label*)malloc(sizeof(Label)*panel.nLabels);
    panel.buttons = (Button*)malloc(sizeof(Button)*panel.nButtons);
    panel.boxes = (Box*)malloc(sizeof(Box)*panel.nBoxes);

    // SETUP LABELS 
    Color labelColors[3] = {LIGHT_BROWN, WHITE, WHITE}; // colori dei testi
    panel.labels[0] = initLabel("Impostazioni", fonts.semibold, 6, labelColors);
    panel.labels[0].sectionPosition = (Vector2){15, 5};
    
    // SETUP BUTTONS
    Color buttonColors[3] = {LIGHT_GRAY, DARK_BROWN, DARK_GRAY};
    Color buttonLabelColors[3] = {DARK_BROWN, LIGHT_BROWN, DARK_BROWN};
    Label labelButtons[panel.nButtons];
    labelButtons[0] = initLabel("Settings 1", fonts.medium, 4, buttonLabelColors);
    labelButtons[1] = initLabel("Settings 2", fonts.medium, 4, buttonLabelColors);
    labelButtons[2] = initLabel("Settings 3", fonts.medium, 4, buttonLabelColors);
    labelButtons[3] = initLabel("Settings 4", fonts.medium, 4, buttonLabelColors);
    labelButtons[4] = initLabel("Indietro", fonts.medium, 4, buttonLabelColors);
    Rectangle areas[panel.nButtons];
    for(int i=0; i<panel.nButtons; i++) { 
        areas[i].width = 65;
        areas[i].height = 12;
        areas[i].x = 50;
        areas[i].y = 25+(areas[i].height+2)*i;
        panel.buttons[i] = initButton(areas[i], labelButtons[i], buttonColors);
    } 
    panel.buttons[4].action = "back";

    // SETUP BOXES
    panel.boxes[0] = initBox((Rectangle){50, 50, 100, 100}, DARK_GRAY);
    panel.boxes[1] = initBox((Rectangle){50, 5, 100, 10}, LIGHT_GRAY);
    
    return panel;
}

void drawUIManager(UIManager uiManager) { // serve a disegnare tutti i componenti (l'ordine in cui vengono scritti e' fondamentale)
    Panel panel = uiManager.panels[uiManager.currentPanel];
    for(int i=0; i<panel.nBoxes; i++) {
        drawBox(panel.boxes[i]);
    }
    for(int i=0; i<panel.nButtons; i++) {
        drawButton(panel.buttons[i]);
    }  
    for(int i=0; i<panel.nLabels; i++) {
        drawLabel(panel.labels[i]);
    }
    if(uiManager.timer>0) {
        int trasparency = (uiManager.maxTime-uiManager.timer)/uiManager.maxTime*255;
        Rectangle blackScreen = {0, 0, GetScreenWidth(), GetScreenHeight()};
        Color color = {0, 0, 0, trasparency};
        DrawRectangleRec(blackScreen, color);
    }   
}

void updateUIManager(UIManager *uiManager) { // aggiorna tutti i componenti e controlla bottoni premuti
    Panel panel = uiManager->panels[uiManager->currentPanel];
    Vector2 mousePosition = GetMousePosition();
    for(int i=0; i<panel.nBoxes; i++) {
        updateBox(&panel.boxes[i]);
    }
    for(int i=0; i<panel.nLabels; i++) {
        updateLabel(&panel.labels[i]);
    }
    char *action = "";
    for(int i=0; i<panel.nButtons; i++) {
        if(updateButton(&panel.buttons[i], mousePosition)) {
            action = panel.buttons[i].action;
        }        
    }
    checkAction(uiManager, action);
    if(IsKeyPressed(KEY_ESCAPE)) {
        if(uiManager->currentPanel==1) uiManager->currentPanel = 2;
        else if(uiManager->currentPanel==2) uiManager->currentPanel = 1;
    }
    if(IsKeyPressed(KEY_F1)) {
        ToggleBorderlessWindowed();
    }
    if(uiManager->timer>0) {
        uiManager->timer += GetFrameTime();
        uiManager->timer = uiManager->timer>uiManager->maxTime? 0:uiManager->timer;
    } 
}

void checkAction(UIManager *uiManager, char *action) {
    if(strcmp(action, "play")==0)  {
        uiManager->currentPanel = HUD_PANEL;
        uiManager->timer = 0.001;
    } else if(strcmp(action, "settings")==0) {
        uiManager->lastPanel = uiManager->currentPanel;
        uiManager->currentPanel = SETTINGS_PANEL;
        uiManager->timer = 0.001;
    } else if(strcmp(action, "mainscreen")==0) {
        uiManager->lastPanel = uiManager->currentPanel;
        uiManager->currentPanel = MAIN_PANEL;
        uiManager->timer = 0.001;
    } else if(strcmp(action, "back")==0) {
        uiManager->currentPanel = uiManager->lastPanel;
        uiManager->timer = 0.001;
    } else if(strcmp(action, "close")==0) {
        // chiusura della finestra (senza usare closeWindow)
    }
}

void unloadUIManager(UIManager *uiManager) { // svuota dati non piu utilizzati
    for(int i=0; i<uiManager->totalPanels; i++) {        
        for(int j=0; j<uiManager->panels[i].nBoxes; j++) {
            UnloadTexture(uiManager->panels[i].boxes[j].texture);
        }
        if(uiManager->panels[i].nLabels!=0) {
            free(uiManager->panels[i].labels);
            free(uiManager->panels[i].buttons);
            free(uiManager->panels[i].boxes);
        }        
    }
    UnloadFont(uiManager->fonts.regular);
    UnloadFont(uiManager->fonts.medium);
    UnloadFont(uiManager->fonts.semibold);
    UnloadFont(uiManager->fonts.bold);
}
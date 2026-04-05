#include "UIManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

UIManager initUIManager() {
    UIManager uiManager; // si occupa di gestire tutti i pannelli
    uiManager.currentPanel = 0; // il pannello iniziale (main screen) e' 0
    uiManager.panels[0] = setupMainScreen(); // il pannello della schermata principale
    uiManager.panels[1] = setupHUD(); // parte sempre visibile in gioco (vita, item ecc.)
    uiManager.panels[2] = setupOptionScreen();
    return uiManager; 
}

Panel setupMainScreen() {
    Panel panel; // ogni pannello ha dei puntatori e le grandezze degli array
    panel.nButtons = 3; // 3 bottoni
    panel.nLabels = 2; // 2 testi
    panel.nBoxes = 1; // 1 solo "rettangolo"
    panel.buttons = (Button*)malloc(sizeof(Button)*panel.nButtons);
    panel.labels = (Label*)malloc(sizeof(Label)*panel.nLabels);
    panel.boxes = (Box*)malloc(sizeof(Box)*panel.nBoxes);

    // COLORI personalizzati
    Color blue = (Color) {56, 82, 180, 255}; // r, g, b, a
    Color lightBlue = (Color) {94, 122, 196, 255};
    Color lightOrange = (Color) {243, 190, 122, 255};
    Color orange = (Color) {240, 141, 57, 255};
    
    // SETUP LABELS (Le posizioni sono scritte tutte in %, quindi se voglio il centro sara 50)
    Font font = GetFontDefault(); // font che scegli te
    Color labelColors[3] = {lightOrange, orange, lightBlue}; // colori dei testi
    panel.labels[0] = initLabel("Gioco Assurdo", font, 10, labelColors); // il 10 sta per la % occupata nella finestra
    panel.labels[1] = initLabel("Gioco creato da giulio e ari", font, 5, labelColors); // testo, font, %, i colori
    panel.labels[0].sectionPosition = (Vector2){50, 20}; // la posizione va messa manualmente fuori dal "costruttore"
    panel.labels[1].sectionPosition = (Vector2){50, 30}; // le posizioni sono sempre in %, quindi: 50->centro, 30->30% in basso dalla cima della finestra

    // SETUP BUTTONS
    Color buttonColors[3] = {lightBlue, lightOrange, BLACK}; // i colori dei pulsanti, sono 3 per ogni tipo di stato (normale, hover, click)
    Color buttonLabelColors[3] = {lightOrange, orange, lightBlue}; // stessa cosa per i testi
    Label labelButtons[panel.nButtons];
    labelButtons[0] = initLabel("Gioca", font, 5, buttonLabelColors); // prima creo i testi
    labelButtons[1] = initLabel("Impostazioni", font, 5, buttonLabelColors); // senza modificare le loro posizioni
    labelButtons[2] = initLabel("Esci", font, 5, buttonLabelColors); // perche sarannno assegnate nella funzione initButton in UIComponents
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
    panel.boxes[0] = initBox((Rectangle){50, 50, 100, 100}, blue); // inizializzazione del rettangolo colorato (in questo caso usato come sfondo)

    return panel;
}

Panel setupHUD() {
    Panel panel; // per ora non ho messo nulla
    panel.nButtons = 0; 
    panel.nLabels = 0;
    panel.nBoxes = 0;
    return panel;
}

Panel setupOptionScreen() {
    Panel panel;
    panel.nLabels = 2;
    panel.nButtons = 4;
    panel.nBoxes = 3;
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

    // SETUP BOXES
    panel.boxes[0] = initBox((Rectangle){50, 50, 100, 100}, blueTransparent); 
    panel.boxes[1] = initBox((Rectangle){20, 50, 40, 100}, blue); 
    panel.boxes[2] = initBox((Rectangle){50, 5, 100, 10}, orange);

    panel.buttons[0].action = "play";
    panel.buttons[1].action = "settings";
    panel.buttons[2].action = "mainscreen";
    panel.buttons[3].action = "close";

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
    if(IsKeyPressed(KEY_ESCAPE) && uiManager->currentPanel==1) {
        uiManager->currentPanel = 2;
    }
}

void checkAction(UIManager *uiManager, char *action) {
    if(strcmp(action, "play")==0)  {
        uiManager->currentPanel = 1;
    } else if(strcmp(action, "settings")==0) {
        //uiManager->currentPanel = ;
    } else if(strcmp(action, "mainscreen")==0) {
        uiManager->currentPanel = 0;
    } else if(strcmp(action, "close")==0) {
        CloseWindow();
    }
}

void unloadUIManager(UIManager *uiManager) { // svuota dati non piu utilizzati
    free(uiManager->panels[0].buttons);
    free(uiManager->panels[0].labels);
    free(uiManager->panels[0].boxes);
    int nBoxes = uiManager->panels[0].nBoxes;
    for(int i=0; i<nBoxes; i++) {
        UnloadTexture(uiManager->panels[0].boxes[i].texture);
    }
}


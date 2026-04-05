#include "UIManager.h"
#include <stdlib.h>
#include <stdio.h>

UIManager initUIManager() {
    UIManager uiManager; // si occupa di gestire tutti i pannelli
    uiManager.currentPanel = 0; // il pannello iniziale (main screen) e' 0
    uiManager.panels[0] = setupMainScreen(); // il pannello della schermata principale
    uiManager.panels[1] = setupHUD(); // parte sempre visibile in gioco (vita, item ecc.)
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
    Label labelButton1 = initLabel("Gioca", font, 5, buttonLabelColors); // prima creo i testi
    Label labelButton2 = initLabel("Impostazioni", font, 5, buttonLabelColors); // senza modificare le loro posizioni
    Label labelButton3 = initLabel("Esci", font, 5, buttonLabelColors); // perche sarannno assegnate nella funzione initButton in UIComponents
    Rectangle areas[panel.nButtons]; // le varie aree dei bottoni
    for(int i=0; i<panel.nButtons; i++) { // visto che sono uno sotto all'altro metto un for 
        areas[i].width = 40; // larghezza del bottone in %
        areas[i].height = 12; // altezza in %
        areas[i].x = 50; // posizione al centro della larghezza dello schermo
        areas[i].y = 45+(areas[i].height+2)*i; // posizione base 45, da li aggiungo i bottoni con un padding di 2
    }
    panel.buttons[0] = initButton(areas[0], labelButton1, buttonColors); // parametri: area, il testo del bottone, e i colori
    panel.buttons[1] = initButton(areas[1], labelButton2, buttonColors); // (se si vuole si possono aggiungere altri aspetti estetici, queste erano di prova)
    panel.buttons[2] = initButton(areas[2], labelButton3, buttonColors); 

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
    int buttonPressed = -1; // nel caso di nessun bottone premuto
    for(int i=0; i<panel.nButtons; i++) {
        if(updateButton(&panel.buttons[i], mousePosition)) {
            buttonPressed = i; // guarda il numero del bottone premuto
        }        
    }

    // questo switch deve essere modificato, pero ora e' cosi solo per testare
    switch (buttonPressed) { 
        case 0:
            uiManager->currentPanel = 1;
            break;
        default:
            break;
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


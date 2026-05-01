#include "UI.h"
#include <stdio.h>
#include <stdlib.h>

UI initUI() {    
    UI ui;

    // FONTS
    ui.fonts.regular = LoadFontEx(FONT_REGUALAR_PATH, 128, 0, 0);
    ui.fonts.medium = LoadFontEx(FONT_MEDIUM_PATH, 128, 0, 0);
    ui.fonts.semibold = LoadFontEx(FONT_SEMIBOLD_PATH, 128, 0, 0);
    ui.fonts.bold = LoadFontEx(FONT_BOLD_PATH, 128, 0, 0);
    
    // MENU PRINCIPALE
    char *text = "L'incredibile Fruscelli è alla ricerca del suo tesoro \nche è stato rubato dall'incredibile samurai che \nha sparso in tutto il mondo i suoi scagnozzi ragebaiter. \nAiutalo a ritrovare ciò che ha perso!";

    ui.mainScreen = initPanel((Rectangle){50, 50, 100, 100}, COLOR_PRIMARY);
    ui.mainScreen.origin.x = 0.5;
    ui.mainScreen.origin.y = 0.5;

    Label *label1 = initLabel((Vector2){50, 10}, "INCREDIBILE TITOLO", ui.fonts.bold);
    label1->origin.x = 0.5;
    label1->origin.y = 0.5;
    label1->size = 10;
    label1->color = COLOR_TERTIARY;

    Label *label2 = initLabel((Vector2){50, 25}, text, ui.fonts.medium);
    label2->origin.x = 0.5;
    label2->origin.y = 0.5;
    label2->size = 2.5;
    label2->color = COLOR_TERTIARY;
    
    Button *buttons[2];
    buttons[0] = initButton((Rectangle){50, 70, 60, 10}, "Primo Bottone", ui.fonts.medium);
    buttons[1] = initButton((Rectangle){50, 120, 60, 10}, "Secondo Bottone", ui.fonts.medium);
    for(int i=0; i<2; i++) {
        buttons[i]->origin.x = 0.5;
        buttons[i]->origin.y = 0.5;
        buttons[i]->size = 6;
        buttons[i]->colors[0] = COLOR_TERTIARY;
        buttons[i]->colors[1] = COLOR_SECONDARY;
    }
            
    insertComponent(&ui.mainScreen, toComponent(label1, LABEL));
    insertComponent(&ui.mainScreen, toComponent(label2, LABEL));
    insertComponent(&ui.mainScreen, toComponent(buttons[0], BUTTON));
    insertComponent(&ui.mainScreen, toComponent(buttons[1], BUTTON));

    // MENU PAUSE

    

    // PAUSA
    

    
    
    return ui;
}

void renderUI(UI ui) {       
    renderPanel(ui.mainScreen, ui.screenSize);
    
}

void updateUI(UI *ui) {
    
}

void unloadUI(UI *ui) {
    UnloadFont(ui->fonts.regular);
    UnloadFont(ui->fonts.medium);
    UnloadFont(ui->fonts.semibold);
    UnloadFont(ui->fonts.bold);
}
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
    ui.mainScreen = initPanel((Rectangle){50, 50, 100, 100}, COLOR_PRIMARY);
    ui.mainScreen.origin = 0.5;

    Label *label = initLabel((Vector2){50, 10}, "Titolo", ui.fonts.bold);
    label->size = 10;
    label->origin = 0.5;
    label->color = COLOR_TERTIARY;
    
    Button *button = initButton((Rectangle){}, "Primo Bottone", ui.fonts.medium);
    button->origin = 0.5;
    button->size = 6;
    button->colors[0] = COLOR_TERTIARY;
    button->colors[1] = COLOR_SECONDARY;

    insertComponent(&ui.mainScreen, toComponent(label, LABEL));
    insertComponent(&ui.mainScreen, toComponent(button, BUTTON));

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
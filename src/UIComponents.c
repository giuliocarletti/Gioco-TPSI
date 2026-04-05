#include "UIComponents.h"
#include <stdio.h>

// prinicipalmente questo e' un elenco di componenti da utilizzare nel UIManager
// in cui ogni componente ha un funzione di inizializzazione, disegno e aggiornamento

Label initLabel(char *text, Font font, int fontSize, Color *colors) {
    Label label; 
    label.text = text;
    label.font = font;
    label.sectionFontSize = fontSize; 
    label.colors[0] = colors[0];
    label.colors[1] = colors[1];
    label.colors[2] = colors[2];
    label.state = 0;
    return label;
}

Button initButton(Rectangle area, Label label, Color *colors) {
    Button button;
    button.sectionArea = area;
    button.label = label;
    button.label.sectionPosition.x = area.x; // la posizione del testo sara la stessa del bottone
    button.label.sectionPosition.y = area.y;
    button.colors[0] = colors[0];
    button.colors[1] = colors[1];
    button.colors[2] = colors[2];
    button.state = 0; // lo stato iniziale (normale)
    return button;
}

Box initBox(Rectangle area, Color color) {
    Box box;
    box.sectionArea = area;
    box.color = color;
    return box;
}

void drawLabel(Label label) {    
    int spacing = label.screenFontSize/10; // la distanza tra le lettere e' un decimo del font nello schermo
    Vector2 textInfo = MeasureTextEx(label.font, label.text, label.screenFontSize, spacing); // misura altezza e larghezza del testo
    Vector2 origin = { // mi serve per prendere il centro del testo come punto di origine
        textInfo.x/2, 
        textInfo.y/2
    };
    DrawTextPro(label.font, label.text, label.screenPosition, origin, 0, label.screenFontSize, spacing, label.colors[label.state]);
}

void drawButton(Button button) {     
    Vector2 origin = { // parte centrale del bottone
        button.screenArea.width/2,
        button.screenArea.height/2
    };
    DrawRectanglePro(button.screenArea, origin, 0, button.colors[button.state]); // disegna prima il pulsante
    drawLabel(button.label); // e poi sopra disegna il testo
}

void drawBox(Box box) {    
    Vector2 origin = { // centro del rettangolo
        box.screenArea.width/2,
        box.screenArea.height/2
    };
    DrawRectanglePro(box.screenArea, origin, 0, box.color);
}

void updateLabel(Label *label) {
    label->screenFontSize = getScreenValueY(label->sectionFontSize); // aggiorna le dimensioni sullo schermo
    label->screenPosition = getScreenSizeVec(label->sectionPosition); // sia della grandezza del testo e della posizione nello schermo
}

bool updateButton(Button *button, Vector2 mousePosition) {
    button->screenArea = getScreenSizeRec(button->sectionArea); // aggiorna la grandezza sullo schermo  
    updateLabel(&button->label); // aggiorna il testo del bottone
    button->state = 0; // mette lo stato del bottone a 0 quindi normale
    button->label.state = 0; // stessa cosa per il testo del bottone
    Rectangle collisionBox = { 
        button->screenArea.x-button->screenArea.width/2,
        button->screenArea.y-button->screenArea.height/2,
        button->screenArea.width,
        button->screenArea.height
    }; // il rettangolo ha il centro come punto di riferimento e quindi si crea un rettangolo con riferimento in alto a sinistra
    if(CheckCollisionPointRec(mousePosition, collisionBox)) { // senza la modifica precendente la un funziona di questa riga vedrebbe il rettangolo spostato della sua meta'
        button->state = 1; // in caso di contatto tra mouse e area del bottone, lo stato passa a 1 (hover)
        button->label.state = 1; // stessa cosa per il testo del bottone
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) { 
            button->state = 2; // in caso di click del tasto sinistro, lo stato passa a 2 (click)
            button->label.state = 2; // stessa cosa per il testo 
            printf("Clicked\n");
            return true; // true nel caso in cui il bottone e' stato premuto
        }        
    }
    return false; // false se non e' stato premuto
}

void updateBox(Box *box) {
    box->screenArea = getScreenSizeRec(box->sectionArea); // unica modifica del rettangolo, per ora
}

Rectangle getScreenSizeRec(Rectangle rec) { 
    return (Rectangle) {
        getScreenValueX(rec.x),
        getScreenValueY(rec.y),
        getScreenValueX(rec.width),
        getScreenValueY(rec.height)
    };
}

Vector2 getScreenSizeVec(Vector2 vec) {
    return (Vector2) {
        getScreenValueX(vec.x),
        getScreenValueY(vec.y)
    };
}

int getScreenValueX(double val) {    
    return val/100*GetScreenWidth(); // trasforma da percentuale a un valore basato sulla larghezza dello schermo
}

int getScreenValueY(double val) {
    return val/100*GetScreenHeight(); // trasforma da percentuale a un valore basato sull'altezza dello schermo
}
#ifndef UI_COMPONENTS_H
#define UI_COMPONENTS_H
#include "raylib.h"

typedef struct {    
    char *text;
    Font font;
    int state;
    Color colors[3];
    int sectionFontSize;
    int screenFontSize;
    Vector2 sectionPosition;
    Vector2 screenPosition;
} Label;

typedef struct {    
    Label label;
    int state;
    Color colors[3];
    Rectangle sectionArea;
    Rectangle screenArea;
    char *action;
} Button;

typedef struct {    
    Color color;
    Texture texture;
    Rectangle sectionArea;
    Rectangle screenArea;
} Box;

Label initLabel(char *text, Font font, int fontSize, Color *colors);
Button initButton(Rectangle area, Label label, Color *colors);
Box initBox(Rectangle area, Color color);
void drawLabel(Label label);
void drawButton(Button button);
void drawBox(Box box);
void updateLabel(Label *label);
bool updateButton(Button *button, Vector2 mousePosition);
void updateBox(Box *box);

#endif
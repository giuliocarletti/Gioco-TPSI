#ifndef UI_COMPONENTS_H
#define UI_COMPONENTS_H
#include "raylib.h"

typedef struct {    
    char *text;
    Font font;
    int fontSize;
    int state;
    Color colors[3];
    Vector2 position;
} Label;

typedef struct {
    Rectangle area;
    Label label;
    int state;
    Color colors[3];
} Button;

Label initLabel(char *text, Font font, int fontSize, Color *colors);
Button initButton(Rectangle area, Label label, Color *colors);
void drawLabel(Label label, Vector2 position);
void drawButton(Button button);
bool updateButton(Button *button, Vector2 mousePosition);

#endif
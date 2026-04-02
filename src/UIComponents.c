#include "UIComponents.h"
#include <stdio.h>

Label initLabel(char *text, Font font, int fontSize, Color *colors) {
    Label label;
    label.text = text;
    label.font = font;
    label.fontSize = fontSize;
    label.colors[0] = colors[0];
    label.colors[1] = colors[1];
    label.colors[2] = colors[2];
    label.state = 0;
    printf("Testo creato: '%s'\n", text);
    return label;
}

Button initButton(Rectangle area, Label label, Color *colors) {
    Button button;
    button.area = area;
    button.label = label;
    button.colors[0] = colors[0];
    button.colors[1] = colors[1];
    button.colors[2] = colors[2];
    button.state = 0;
    printf("Bottone creato: '%s'\n", label.text);
    return button;
}

void drawLabel(Label label, Vector2 position) {
    int spacing = label.fontSize/8;
    Vector2 labelInfo = MeasureTextEx(label.font, label.text, label.fontSize, spacing);    
    Vector2 origin = {labelInfo.x/2, labelInfo.y/2}; 
    DrawTextPro(label.font, label.text, position, origin, 0, label.fontSize, spacing, label.colors[label.state]);
}

void drawButton(Button button) {    
    Vector2 origin = {button.area.width/2, button.area.height/2};
    Vector2 textPosition = {button.area.x, button.area.y};
    DrawRectanglePro(button.area, origin, 0, button.colors[button.state]);
    drawLabel(button.label, textPosition);
}

bool updateButton(Button *button, Vector2 mousePosition) {        
    button->state = 0;
    button->label.state = 0;
    Rectangle collisionBox = {
        button->area.x-button->area.width/2,
        button->area.y-button->area.height/2,
        button->area.width,
        button->area.height
    };
    if(CheckCollisionPointRec(mousePosition, collisionBox)) {
        button->state = 1;
        button->label.state = 1;    
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {            
            button->state = 2;
            button->label.state = 2;
            printf("Clicked\n");
            return true;
        }        
    }
    return false;
}
#include "UIcomponents.h"
#include <stdlib.h>
#include <stdio.h>

static Rectangle getScreenSizeRec(Vector2 screenSize, Rectangle rec);
static Vector2 getScreenSizeVec(Vector2 screenSize, Vector2 vec);

Panel initPanel(Rectangle area, Color color) {
    Panel panel;
    panel.area = area;
    panel.color = color;
    panel.components.length = 0;
    panel.components.array = NULL;
    return panel;
}

Label* initLabel(Vector2 pos, char *text, Font font) {
    Label *label = malloc(sizeof(Label));
    label->text = text;
    label->font = font;
    label->color = WHITE;
    label->size = 5;
    label->origin = 0;    
    return label;
}

Button* initButton(Rectangle area, char *text, Font font) {
    Button *button = malloc(sizeof(Button));
    button->area = area;
    button->text = text;
    button->font = font;
    button->colors[0] = WHITE;
    button->colors[1] = GRAY;
    button->size = 5;
    button->origin = 0;
    return button;
}

Component toComponent(void *element, ComponentType type) {
    Component component;
    component.object = element;
    component.type = type;
    return component;
}

void insertComponent(Panel *container, Component component) {
    container->components.length++;
    int size = sizeof(Component)*container->components.length;
    container->components.array = (Component*)realloc(container->components.array, size);
    container->components.array[container->components.length-1] = component;
}

void renderPanel(Panel panel, Vector2 screenSize) {
    
    DrawRectangleRec(area, panel.color);
    
    /*
    switch(component.type) {
        case PANEL:
            Panel *panel = component.object;
            DrawRectangleRec(panel->area, panel->color);
            for(int i=0; i<panel->components.length; i++) {
                renderComponent(panel->components.array[i]);
            }
            break;
        case LABEL:        
            Label *label = component.object;
            float spacing = label->size/24;
            Vector2 measures = MeasureTextEx(label->font, label->text, label->size, spacing);
            Vector2 position = {
                (int)label->position.x,
                (int)label->position.y
            };            
            Vector2 origin = {
                (int)(measures.x/2),
                (int)(measures.y/2)
            };
            DrawTextPro(label->font, label->text, position, origin, 0, label->size, spacing, label->color);            
            break;          
        default:
            break;
    }    
    */    
}
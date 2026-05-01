#include "UIcomponents.h"
#include <stdlib.h>
#include <stdio.h>

static Rectangle getScreenSizeRec(Vector2 screenSize, Rectangle rec);
static Vector2 getScreenSizeVec(Vector2 screenSize, Vector2 vec);
static Vector2 getOriginOfPoints(int x, int y, Vector2 origin);
static void drawLabel(Label *label, Vector2 screenSize);
static void drawButton(Button *button, Vector2 screenSize);

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
    label->position = pos;
    label->text = text;
    label->font = font;
    label->color = WHITE;
    label->size = 5;
    label->origin.x = 0;
    label->origin.y = 0;
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
    button->origin.x = 0;
    button->origin.y = 0;
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
    Rectangle screenRec = getScreenSizeRec(screenSize, panel.area);
    Vector2 origin = getOriginOfPoints(screenRec.width, screenRec.height, panel.origin);
    DrawRectanglePro(screenRec, origin, 0, panel.color);
    for(int i=0; i<panel.components.length; i++) {
        switch(panel.components.array[i].type) {
            case LABEL:
                Label *label = (Label*)panel.components.array[i].object;
                drawLabel(label, screenSize);
                break;
            case BUTTON:
                Button *button = (Button*)panel.components.array[i].object;
                drawButton(button, screenSize);
                break;            
        }
    }       
}

static void drawLabel(Label *label, Vector2 screenSize) {
    float size = label->size/100*screenSize.y;
    float spacing = size/22;
    Vector2 position = getScreenSizeVec(screenSize, label->position);
    Vector2 measures = MeasureTextEx(label->font, label->text, size, spacing);
    Vector2 origin = getOriginOfPoints(measures.x, measures.y, label->origin);
    DrawTextPro(label->font ,label->text, position, origin, 0, size, spacing, label->color);
}

static void drawButton(Button *button, Vector2 screenSize) {   
    /*
    Rectangle screenButton = getScreenSizeRec(screenSize, button->area);
    Vector2 origin = getOriginOfPoints(screenButton.x, screenButton.y, button->origin);
    DrawRectanglePro(screenButton, origin, 0, button->colors[button->hover? 1:0]);
    float size = button->size/100*screenSize.y;
    float spacing = size/22;
    Vector2 position = (Vector2){screenButton.x, screenButton.y};
    Vector2 measures = MeasureTextEx(button->font, button->text, size, spacing);
    Vector2 originText = getOriginOfPoints(measures.x, measures.y, button->origin);
    //DrawTextPro(button->font, button->text, position, originText, 0, size, spacing, button->colors[button->hover? 0:1]);
    */
    
}


static Rectangle getScreenSizeRec(Vector2 screenSize, Rectangle rec) {
    return (Rectangle) {
        rec.x/100*screenSize.x,
        rec.y/100*screenSize.y,
        rec.width/100*screenSize.x,
        rec.height/100*screenSize.y,
    };
}

static Vector2 getScreenSizeVec(Vector2 screenSize, Vector2 vec) {
    return (Vector2) {
        vec.x/100*screenSize.x,
        vec.y/100*screenSize.y
    };
}

static Vector2 getOriginOfPoints(int x, int y, Vector2 origin) {
    return (Vector2) {
        x*origin.x,
        y*origin.y,
    };
}

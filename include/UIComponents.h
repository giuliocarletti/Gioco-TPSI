#ifndef UI_ELEMENTS_H
#define UI_ELEMENTS_H

#include "raylib.h"

typedef enum {
    LABEL,
    BUTTON,
} ComponentType;

typedef struct {
    ComponentType type;
    void *object;
} Component;

typedef struct { 
    Rectangle area;
    Vector2 origin;
    Color color;
    struct {
        Component *array;
        int length;
    } components;     
} Panel;

typedef struct {
    char* text;
    float size;
    Font font;
    Color color;
    Vector2 position;
    Vector2 origin;
} Label;

typedef struct {
    bool hover;
    char* text;
    float size;
    Font font;    
    Color colors[2];
    Rectangle area;
    Vector2 origin;
} Button;

Panel initPanel(Rectangle area, Color color);
Label* initLabel(Vector2 pos, char *text, Font font);
Button* initButton(Rectangle area, char *text, Font font);
Component toComponent(void *element, ComponentType type);
void insertComponent(Panel *container, Component component);
void renderPanel(Panel panel, Vector2 screenSize);

#endif
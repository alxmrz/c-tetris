#ifndef FIGURE_MODULE
#define FIGURE_MODULE

#include "element.h"

#define MOVE_STEP 1

typedef struct Figure {
    Element *e1;
    Element *e2;
    Element *e3;
    Element *e4;
} Figure;


Figure * create_o_figure(int x, int y);
void delete_figure(Figure *figure);

int move_left (Figure *figure);
int move_right (Figure *figure);
int move_down_figure (Figure *figure);

#endif
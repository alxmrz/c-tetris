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

Figure * create_random_figure(int, int);
Figure * create_o_figure(int, int);
Figure * create_L_figure(int, int);
Figure * create_J_figure(int, int);
Figure * create_I_figure(int, int);
Figure * create_S_figure(int, int);
Figure * create_T_figure(int, int);
Figure * create_Z_figure(int, int);

void delete_figure(Figure *);

int move_left (Figure *);
int move_right (Figure *);
int move_down_figure (Figure *);
int move_up_figure(Figure *);
int is_figures_intersected(Figure *, Figure *);

#endif
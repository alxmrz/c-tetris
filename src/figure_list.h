#ifndef ARRAY_MODULE
#define ARRAY_MODULE

#include "figure.h"
#include "malloc.h"

#define DEFAULT_FL_SIZE 20

typedef struct FigureList {
    Figure **figures;
    int size;
    int maxSize;
} FigureList;

FigureList * create_figure_list();
void delete_figure_list(FigureList *);

int fl_push(FigureList *fl, Figure *figure);
int is_figure_intersect_list(FigureList * fl, Figure *figure);

#endif
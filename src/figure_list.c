#include "figure.h"
#include "figure_list.h"

FigureList * create_figure_list() {
    FigureList *fl = malloc(sizeof(FigureList));
    fl->figures = malloc(sizeof(Figure*) * DEFAULT_FL_SIZE);
    fl->size = 0;
    fl->maxSize = DEFAULT_FL_SIZE;

    return fl;
}

void delete_figure_list(FigureList * fl) {
    free(fl);
}

int fl_push(FigureList *fl, Figure *figure) {
    fl->figures[fl->size] = figure;
    fl->size += 1;

    return 1;
}

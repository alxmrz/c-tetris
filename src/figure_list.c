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
    //TODO: надо сделать увеличение блока памяти при fl->size == fl->maxSize
    fl->figures[fl->size] = figure;
    fl->size += 1;

    return 1;
}

int is_figure_intersect_list(FigureList * fl, Figure *figure) {
    for (int i = 0; i < fl->size; i++) {
        if (figure == fl->figures[i]) {
            continue;
        }
        
        int res = is_figures_intersected(figure, fl->figures[i]);
        if (res == 1) {
            return 1;
        }
    }

    return 0;
}
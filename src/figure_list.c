#include "figure.h"
#include "figure_list.h"

FigureList *create_figure_list() {
    FigureList *fl = malloc(sizeof(FigureList));
    fl->figures = malloc(sizeof(Figure *) * DEFAULT_FL_SIZE);
    fl->size = 0;
    fl->maxSize = DEFAULT_FL_SIZE;

    return fl;
}

void delete_figure_list(FigureList *fl) {
    for (int i = 0; i < fl->size; i++) {
        delete_figure(fl->figures[i]);
    }
    free(fl);
}

int fl_push(FigureList *fl, Figure *figure) {
    if (fl->size == fl->maxSize) {
        fl->maxSize *= 2;
        fl->figures = realloc(fl->figures, fl->maxSize * sizeof(Figure *));
    }

    fl->figures[fl->size] = figure;
    fl->size += 1;

    return 1;
}

int is_figure_intersect_list(FigureList *fl, Figure *figure) {
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

int delete_one_line_elements(FigureList *fl) {
    int deletedLines = 0;

    Element *elements[200];
    int elementsSize = 0;

    for (int i = 0; i < fl->size; i++) {
        elements[elementsSize] = fl->figures[i]->e1;
        elementsSize++;
        elements[elementsSize] = fl->figures[i]->e2;
        elementsSize++;
        elements[elementsSize] = fl->figures[i]->e3;
        elementsSize++;
        elements[elementsSize] = fl->figures[i]->e4;
        elementsSize++;
    }

    for (int i = 0; i < elementsSize; i++) {
        int countInLine = 1;

        for (int j = 0; j < elementsSize; j++) {
            if (i == j) continue;

            if (elements[j] && elements[i] && elements[j]->y == elements[i]->y) countInLine++;
        }

        if (countInLine == 10) {
            int searchToDelete = elements[i]->y;
            for (int j = 0; j < elementsSize; j++) {
                if (elements[j] && searchToDelete == elements[j]->y) {
                    for (int fi = 0; fi < fl->size; fi++) {
                        if (fl->figures[fi]->e1 == elements[j]) {
                            fl->figures[fi]->e1 = NULL;
                        } else if (fl->figures[fi]->e2 == elements[j]) {
                            fl->figures[fi]->e2 = NULL;
                        } else if (fl->figures[fi]->e3 == elements[j]) {
                            fl->figures[fi]->e3 = NULL;
                        } else if (fl->figures[fi]->e4 == elements[j]) {
                            fl->figures[fi]->e4 = NULL;
                        }
                    }
                    delete_element(elements[j]);
                    elements[j] = NULL;
                }
            }

            deletedLines++;
        }
    }

    return deletedLines;
}


#include "figure.h"
#include "malloc.h"
#include "configuration.h"

Figure * create_o_figure(int x, int y) {
    Figure * figure = malloc(sizeof(Figure));

    figure->e1 = create_element(x,y);
    figure->e2 = create_element(x+ELEMENT_SIZE,y);
    figure->e3 = create_element(x,y+ELEMENT_SIZE);
    figure->e4 = create_element(x+ELEMENT_SIZE,y+ELEMENT_SIZE);

    return figure;
}

void delete_figure(Figure *figure) {
    free(figure);
}

int move_left(Figure *figure) {
   if (figure->e1->x == GAME_LEFT_BORDER) {
    return 0;
   }

   figure->e1->x -= ELEMENT_SIZE;
   figure->e2->x -= ELEMENT_SIZE;
   figure->e3->x -= ELEMENT_SIZE;
   figure->e4->x -= ELEMENT_SIZE;

   return 1;
}

int move_right(Figure *figure) {
    if (figure->e1->x == GAME_RIGHT_BORDER-ELEMENT_SIZE ||
        figure->e2->x == GAME_RIGHT_BORDER-ELEMENT_SIZE ||
        figure->e3->x == GAME_RIGHT_BORDER-ELEMENT_SIZE ||
        figure->e4->x == GAME_RIGHT_BORDER-ELEMENT_SIZE
    ) {
        return 0;
    }

    figure->e1->x += ELEMENT_SIZE;
    figure->e2->x += ELEMENT_SIZE;
    figure->e3->x += ELEMENT_SIZE;
    figure->e4->x += ELEMENT_SIZE;

    return 1;
}

int move_down_figure(Figure *figure) {
    if (figure->e1 && figure->e1->y+ELEMENT_SIZE == GAME_BOTTOM_BORDER) {
        return 0;
    }

    if (figure->e2 && figure->e2->y+ELEMENT_SIZE == GAME_BOTTOM_BORDER) {
         return 0;
    }

    if (figure->e3 && figure->e3->y+ELEMENT_SIZE == GAME_BOTTOM_BORDER) {
         return 0;
    }

    if (figure->e4 && figure->e4->y+ELEMENT_SIZE == GAME_BOTTOM_BORDER) {
         return 0;
    }

    if (figure->e1) {
        figure->e1->y += ELEMENT_SIZE;
    }
    
    if (figure->e2) {
        figure->e2->y += ELEMENT_SIZE;
    }

    if (figure->e3) {
        figure->e3->y += ELEMENT_SIZE;
    }

    if (figure->e4) {
        figure->e4->y += ELEMENT_SIZE;
    }

    return 1;
}

int move_up_figure(Figure *figure) {
    figure->e1->y -= ELEMENT_SIZE;
    figure->e2->y -= ELEMENT_SIZE;
    figure->e3->y -= ELEMENT_SIZE;
    figure->e4->y -= ELEMENT_SIZE;

    return 1;
}


int is_figures_intersected(Figure *f1, Figure *f2) {
    int len = 4;
    Element *es1[len];
    es1[0] = f1->e1;
    es1[1] = f1->e2;
    es1[2] = f1->e3;
    es1[3] = f1->e4;

    Element *es2[len];
    es2[0] = f2->e1;
    es2[1] = f2->e2;
    es2[2] = f2->e3;
    es2[3] = f2->e4;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (!es1[i] || !es2[j]) continue;
            if (es1[i]->x == es2[j]->x && es1[i]->y == es2[j]->y) {
                return 1;
            }
        }
    }

    return 0;
}
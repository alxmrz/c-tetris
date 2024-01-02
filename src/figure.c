
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
    if (figure->e1->y+ELEMENT_SIZE == GAME_BOTTOM_BORDER ||
        figure->e2->y+ELEMENT_SIZE == GAME_BOTTOM_BORDER ||
        figure->e3->y+ELEMENT_SIZE == GAME_BOTTOM_BORDER ||
        figure->e4->y+ELEMENT_SIZE == GAME_BOTTOM_BORDER
    ) {
        return 0;
    }

    figure->e1->y += ELEMENT_SIZE;
    figure->e2->y += ELEMENT_SIZE;
    figure->e3->y += ELEMENT_SIZE;
    figure->e4->y += ELEMENT_SIZE;

    return 1;
}
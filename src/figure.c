#include "figure.h"
#include "malloc.h"
#include "stdlib.h"
#include "stdio.h"
#include "configuration.h"

static const int figure_types_count = 7;

Figure *create_random_figure(int x, int y) {
    int randNumber = rand() % figure_types_count;

    switch (randNumber) {
        case 0:
            return create_o_figure(x, y);
        case 1:
            return create_L_figure(x, y);
        case 2:
            return create_J_figure(x, y);
        case 3:
            return create_I_figure(x, y);
        case 4:
            return create_S_figure(x, y);
        case 5:
            return create_T_figure(x, y);
        case 6:
            return create_Z_figure(x, y);
        default:
            printf("Unexpected random number - %d!", randNumber);
            return create_o_figure(x, y);
    }
}

Figure *create_o_figure(int x, int y) {
    Figure *figure = malloc(sizeof(Figure));

    figure->type = 'O';
    figure->e1 = create_element(x, y);
    figure->e2 = create_element(x + ELEMENT_SIZE, y);
    figure->e3 = create_element(x, y + ELEMENT_SIZE);
    figure->e4 = create_element(x + ELEMENT_SIZE, y + ELEMENT_SIZE);

    return figure;
}

Figure *create_L_figure(int x, int y) {
    Figure *figure = malloc(sizeof(Figure));

    figure->type = 'L';
    figure->e1 = create_element(x, y);
    figure->e2 = create_element(x, y + ELEMENT_SIZE);
    figure->e3 = create_element(x, y + ELEMENT_SIZE * 2);
    figure->e4 = create_element(x + ELEMENT_SIZE, y + ELEMENT_SIZE * 2);

    return figure;
}

Figure *create_J_figure(int x, int y) {
    Figure *figure = malloc(sizeof(Figure));

    figure->type = 'J';
    figure->e1 = create_element(x, y);
    figure->e2 = create_element(x, y + ELEMENT_SIZE);
    figure->e3 = create_element(x, y + ELEMENT_SIZE * 2);
    figure->e4 = create_element(x - ELEMENT_SIZE, y + ELEMENT_SIZE * 2);

    return figure;
}

Figure *create_I_figure(int x, int y) {
    Figure *figure = malloc(sizeof(Figure));

    figure->type = 'I';
    figure->e1 = create_element(x, y);
    figure->e2 = create_element(x, y + ELEMENT_SIZE);
    figure->e3 = create_element(x, y + ELEMENT_SIZE * 2);
    figure->e4 = create_element(x, y + ELEMENT_SIZE * 3);

    return figure;
}

Figure *create_S_figure(int x, int y) {
    Figure *figure = malloc(sizeof(Figure));

    figure->type = 'S';
    figure->e1 = create_element(x, y + ELEMENT_SIZE);
    figure->e2 = create_element(x + ELEMENT_SIZE, y);
    figure->e3 = create_element(x + ELEMENT_SIZE, y + ELEMENT_SIZE);
    figure->e4 = create_element(x + ELEMENT_SIZE * 2, y);

    return figure;
}

Figure *create_T_figure(int x, int y) {
    Figure *figure = malloc(sizeof(Figure));

    figure->type = 'T';
    figure->e1 = create_element(x, y);
    figure->e2 = create_element(x + ELEMENT_SIZE, y);
    figure->e3 = create_element(x + ELEMENT_SIZE, y + ELEMENT_SIZE);
    figure->e4 = create_element(x + ELEMENT_SIZE * 2, y);

    return figure;
}

Figure *create_Z_figure(int x, int y) {
    Figure *figure = malloc(sizeof(Figure));

    figure->type = 'Z';
    figure->e1 = create_element(x, y);
    figure->e2 = create_element(x + ELEMENT_SIZE, y);
    figure->e3 = create_element(x + ELEMENT_SIZE, y + ELEMENT_SIZE);
    figure->e4 = create_element(x + ELEMENT_SIZE * 2, y + ELEMENT_SIZE);

    return figure;
}

void delete_figure(Figure *figure) {
    if (figure->e1) {
        delete_element(figure->e1);
    }

    if (figure->e2) {
        delete_element(figure->e2);
    }

    if (figure->e3) {
        delete_element(figure->e3);
    }

    if (figure->e4) {
        delete_element(figure->e4);
    }
    free(figure);
}

int move_left(Figure *figure) {
    // TODO: need test for this condition
    if (figure->e1->x == GAME_LEFT_BORDER ||
        figure->e2->x == GAME_LEFT_BORDER ||
        figure->e3->x == GAME_LEFT_BORDER ||
        figure->e4->x == GAME_LEFT_BORDER
    ) {
        return 0;
    }

    figure->e1->x -= ELEMENT_SIZE;
    figure->e2->x -= ELEMENT_SIZE;
    figure->e3->x -= ELEMENT_SIZE;
    figure->e4->x -= ELEMENT_SIZE;

    return 1;
}

int move_right(Figure *figure) {
    if (figure->e1->x == GAME_RIGHT_BORDER - ELEMENT_SIZE ||
        figure->e2->x == GAME_RIGHT_BORDER - ELEMENT_SIZE ||
        figure->e3->x == GAME_RIGHT_BORDER - ELEMENT_SIZE ||
        figure->e4->x == GAME_RIGHT_BORDER - ELEMENT_SIZE
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
    if (figure->e1 && figure->e1->y + ELEMENT_SIZE == GAME_BOTTOM_BORDER) {
        return 0;
    }

    if (figure->e2 && figure->e2->y + ELEMENT_SIZE == GAME_BOTTOM_BORDER) {
        return 0;
    }

    if (figure->e3 && figure->e3->y + ELEMENT_SIZE == GAME_BOTTOM_BORDER) {
        return 0;
    }

    if (figure->e4 && figure->e4->y + ELEMENT_SIZE == GAME_BOTTOM_BORDER) {
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
    if (figure->e1) {
        figure->e1->y -= ELEMENT_SIZE;
    }

    if (figure->e2) {
        figure->e2->y -= ELEMENT_SIZE;
    }

    if (figure->e3) {
        figure->e3->y -= ELEMENT_SIZE;
    }

    if (figure->e4) {
        figure->e4->y -= ELEMENT_SIZE;
    }

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

void move_figure_to_point(Figure *figure, int x, int y) {
    switch (figure->type) {
        case 'O':
            figure->e1->x = x;
            figure->e1->y = y;

            figure->e2->x = x + ELEMENT_SIZE;
            figure->e2->y = y;

            figure->e3->x = x;
            figure->e3->y = y + ELEMENT_SIZE;

            figure->e4->x = x + ELEMENT_SIZE;
            figure->e4->y = y + ELEMENT_SIZE;
            break;
        case 'I':
            figure->e1->x = x;
            figure->e1->y = y;

            figure->e2->x = x;
            figure->e2->y = y + ELEMENT_SIZE;

            figure->e3->x = x;
            figure->e3->y = y + ELEMENT_SIZE * 2;

            figure->e4->x = x;
            figure->e4->y = y + ELEMENT_SIZE * 3;
            break;
        case 'J':
            figure->e1->x = x;
            figure->e1->y = y;

            figure->e2->x = x;
            figure->e2->y = y + ELEMENT_SIZE;

            figure->e3->x = x;
            figure->e3->y = y + ELEMENT_SIZE * 2;

            figure->e4->x = x - ELEMENT_SIZE;
            figure->e4->y = y + ELEMENT_SIZE * 2;
            break;
        case 'L':
            figure->e1->x = x;
            figure->e1->y = y;

            figure->e2->x = x;
            figure->e2->y = y + ELEMENT_SIZE;

            figure->e3->x = x;
            figure->e3->y = y + ELEMENT_SIZE * 2;

            figure->e4->x = x + ELEMENT_SIZE;
            figure->e4->y = y + ELEMENT_SIZE * 2;
            break;
        case 'S':
            figure->e1->x = x;
            figure->e1->y = y + ELEMENT_SIZE;

            figure->e2->x = x + ELEMENT_SIZE;
            figure->e2->y = y;

            figure->e3->x = x + ELEMENT_SIZE;
            figure->e3->y = y + ELEMENT_SIZE;

            figure->e4->x = x + ELEMENT_SIZE * 2;
            figure->e4->y = y;
            break;
        case 'T':
            figure->e1->x = x;
            figure->e1->y = y;

            figure->e2->x = x + ELEMENT_SIZE;
            figure->e2->y = y;

            figure->e3->x = x + ELEMENT_SIZE;
            figure->e3->y = y + ELEMENT_SIZE;

            figure->e4->x = x + ELEMENT_SIZE * 2;
            figure->e4->y = y;
            break;
        case 'Z':
            figure->e1->x = x;
            figure->e1->y = y;

            figure->e2->x = x + ELEMENT_SIZE;
            figure->e2->y = y;

            figure->e3->x = x + ELEMENT_SIZE;
            figure->e3->y = y + ELEMENT_SIZE;

            figure->e4->x = x + ELEMENT_SIZE * 2;
            figure->e4->y = y + ELEMENT_SIZE;
            break;

        default:
            break;
    }
}


#ifndef FIGURE_TEST
#define FIGURE_TEST

#include <cmocka.h>
#include "../src/figure.h"
#include "../src/configuration.h"

static void test_create_figure_O(void **state) {
    Figure *figure = create_o_figure(0,0);

    assert_int_equal(figure->e1->x, 0);
    assert_int_equal(figure->e1->y, 0);

    assert_int_equal(figure->e2->x, ELEMENT_SIZE);
    assert_int_equal(figure->e2->y, 0);

    assert_int_equal(figure->e3->x, 0);
    assert_int_equal(figure->e3->y, ELEMENT_SIZE);

    assert_int_equal(figure->e4->x, ELEMENT_SIZE);
    assert_int_equal(figure->e4->y, ELEMENT_SIZE);
}
 
static void test_figure_move_left_on_edge_position(void **state) {
    Figure *figure = create_o_figure(GAME_LEFT_BORDER,0);

    int result = move_left(figure);

    assert_int_equal(result, 0);

    assert_int_equal(figure->e1->x, GAME_LEFT_BORDER);
    assert_int_equal(figure->e1->y, 0);

    assert_int_equal(figure->e2->x, GAME_LEFT_BORDER+ELEMENT_SIZE);
    assert_int_equal(figure->e2->y, 0);

    assert_int_equal(figure->e3->x, GAME_LEFT_BORDER);
    assert_int_equal(figure->e3->y, ELEMENT_SIZE);

    assert_int_equal(figure->e4->x, GAME_LEFT_BORDER+ELEMENT_SIZE);
    assert_int_equal(figure->e4->y, ELEMENT_SIZE);
}

static void test_figure_move_left_on_none_edge_position(void **state) {
    Figure *figure = create_o_figure(ELEMENT_SIZE,0);

    int result = move_left(figure);

    assert_int_equal(result, 1);

    assert_int_equal(figure->e1->x, 0);
    assert_int_equal(figure->e1->y, 0);

    assert_int_equal(figure->e2->x, ELEMENT_SIZE);
    assert_int_equal(figure->e2->y, 0);

    assert_int_equal(figure->e3->x, 0);
    assert_int_equal(figure->e3->y, ELEMENT_SIZE);

    assert_int_equal(figure->e4->x, ELEMENT_SIZE);
    assert_int_equal(figure->e4->y, ELEMENT_SIZE);
}

static void test_figure_move_right_on_edge_position(void **state) {
    Figure *figure = create_o_figure(GAME_RIGHT_BORDER-ELEMENT_SIZE-ELEMENT_SIZE,0);

    int result = move_right(figure);

    assert_int_equal(result, 0);

    assert_int_equal(figure->e1->x, GAME_RIGHT_BORDER-ELEMENT_SIZE-ELEMENT_SIZE);
    assert_int_equal(figure->e1->y, 0);

    assert_int_equal(figure->e2->x, GAME_RIGHT_BORDER-ELEMENT_SIZE);
    assert_int_equal(figure->e2->y, 0);

    assert_int_equal(figure->e3->x, GAME_RIGHT_BORDER-ELEMENT_SIZE-ELEMENT_SIZE);
    assert_int_equal(figure->e3->y, ELEMENT_SIZE);

    assert_int_equal(figure->e4->x, GAME_RIGHT_BORDER-ELEMENT_SIZE);
    assert_int_equal(figure->e4->y, ELEMENT_SIZE);
}

static void test_figure_move_right_on_none_edge_position(void **state) {
    Figure *figure = create_o_figure(0,0);

    int result = move_right(figure);

    assert_int_equal(result, 1);

    assert_int_equal(figure->e1->x, ELEMENT_SIZE);
    assert_int_equal(figure->e1->y, 0);

    assert_int_equal(figure->e2->x, ELEMENT_SIZE+ELEMENT_SIZE);
    assert_int_equal(figure->e2->y, 0);

    assert_int_equal(figure->e3->x, ELEMENT_SIZE);
    assert_int_equal(figure->e3->y, ELEMENT_SIZE);

    assert_int_equal(figure->e4->x, ELEMENT_SIZE+ELEMENT_SIZE);
    assert_int_equal(figure->e4->y, ELEMENT_SIZE);
}

static void test_figure_move_down(void **state) {
    Figure *figure = create_o_figure(20,0);

    int result = move_down_figure(figure);

    assert_int_equal(result, 1);

    assert_int_equal(figure->e1->x, 20);
    assert_int_equal(figure->e1->y, ELEMENT_SIZE);

    assert_int_equal(figure->e2->x, 20+ELEMENT_SIZE);
    assert_int_equal(figure->e2->y, ELEMENT_SIZE);

    assert_int_equal(figure->e3->x, 20);
    assert_int_equal(figure->e3->y, ELEMENT_SIZE+ELEMENT_SIZE);

    assert_int_equal(figure->e4->x, 20+ELEMENT_SIZE);
    assert_int_equal(figure->e4->y, ELEMENT_SIZE+ELEMENT_SIZE);
}

static void test_figure_move_down_on_edge_position(void **state) {
    Figure *figure = create_o_figure(20,GAME_BOTTOM_BORDER-ELEMENT_SIZE-ELEMENT_SIZE);

    int result = move_down_figure(figure);

    assert_int_equal(result, 0);

    assert_int_equal(figure->e1->x, 20);
    assert_int_equal(figure->e1->y, GAME_BOTTOM_BORDER-ELEMENT_SIZE-ELEMENT_SIZE);

    assert_int_equal(figure->e2->x, 20+ELEMENT_SIZE);
    assert_int_equal(figure->e2->y, GAME_BOTTOM_BORDER-ELEMENT_SIZE-ELEMENT_SIZE);

    assert_int_equal(figure->e3->x, 20);
    assert_int_equal(figure->e3->y, GAME_BOTTOM_BORDER-ELEMENT_SIZE);

    assert_int_equal(figure->e4->x, 20+ELEMENT_SIZE);
    assert_int_equal(figure->e4->y, GAME_BOTTOM_BORDER-ELEMENT_SIZE);
}

#endif
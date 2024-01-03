#ifndef FIGURE_LIST_TEST
#define FIGURE_LIST_TEST

#include "cmocka.h"
#include "../src/figure.h"
#include "../src/figure_list.h"
#include "../src/element.h"

static void test_fl_create_figure_list(void **state){
    FigureList *fl = create_figure_list();

    assert_non_null(fl);
    assert_int_equal(fl->size, 0);
    assert_int_equal(fl->maxSize, DEFAULT_FL_SIZE);
}

static void test_fl_delete_figure_list(void **state){
    FigureList *fl = create_figure_list();
    delete_figure_list(fl);
    fl = NULL;
    assert_int_equal(fl, NULL);
}

static void test_fl_push(void **state) {
    FigureList *fl = create_figure_list();
    Figure figure;
    figure.e1 = create_element(10, 20);
    fl_push(fl, &figure);

    assert_int_equal(fl->figures[0]->e1->x, 10);
    assert_int_equal(fl->figures[0]->e1->y, 20);

}

static void test_fl_is_figure_intersect_list(void **state) {
    FigureList *fl = create_figure_list();
    Figure figure;
    figure.e1 = create_element(200, 200);
    fl_push(fl, &figure);

    Figure figureToCheck;
    figureToCheck.e1 = create_element(200, 200);

    int expected = 1;
    int actual = is_figure_intersect_list(fl, &figureToCheck);

    assert_int_equal(expected, actual);
}

static void test_fl_is_figure_not_intersect_list(void **state) {
    FigureList *fl = create_figure_list();
    Figure figure;
    figure.e1 = create_element(200, 200);
    figure.e2 = create_element(200+ELEMENT_SIZE, 200);
    figure.e3 = create_element(200, 200+ELEMENT_SIZE);
    figure.e4 = create_element(200+ELEMENT_SIZE, 200+ELEMENT_SIZE);

    fl_push(fl, &figure);

    Figure figureToCheck;
    figureToCheck.e1 = create_element(500, 500);
    figureToCheck.e2 = create_element(500+ELEMENT_SIZE, 500);
    figureToCheck.e3 = create_element(500, 200+ELEMENT_SIZE);
    figureToCheck.e4 = create_element(500+ELEMENT_SIZE, 500+ELEMENT_SIZE);
    int expected = 0;
    int actual = is_figure_intersect_list(fl, &figureToCheck);

    assert_int_equal(expected, actual);
}

static void test_fl_figure_not_intersect_itself(void **state) {
    FigureList *fl = create_figure_list();
    Figure figure;
    figure.e1 = create_element(200, 200);
    figure.e2 = create_element(200+ELEMENT_SIZE, 200);
    figure.e3 = create_element(200, 200+ELEMENT_SIZE);
    figure.e4 = create_element(200+ELEMENT_SIZE, 200+ELEMENT_SIZE);

    fl_push(fl, &figure);

    int expected = 0;
    int actual = is_figure_intersect_list(fl, &figure);

    assert_int_equal(expected, actual);
}

static void test_fl_delete_one_line_elements(void **state) {
    FigureList *fl = create_figure_list();
    for (int i = 0; i < 10; i++) {
        Figure *figure = create_o_figure(200+ELEMENT_SIZE*2, 200);
        fl_push(fl, figure);
    }

    int actual = delete_one_line_elements(fl);
    printf("%s\n", "AFTER DELEE IN TEST");
    assert_int_equal(2, actual);
    assert_null(fl->figures[1]->e1);
    assert_null(fl->figures[2]->e1);
    assert_null(fl->figures[3]->e1);
    assert_null(fl->figures[4]->e1);
    assert_null(fl->figures[5]->e1);
    assert_null(fl->figures[6]->e1);
    assert_null(fl->figures[7]->e1);
    assert_null(fl->figures[8]->e1);
    assert_null(fl->figures[9]->e1);
}

#endif
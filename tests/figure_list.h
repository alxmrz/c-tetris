#ifndef FIGURE_LIST_TEST
#define FIGURE_LIST_TEST

#include "cmocka.h"
#include "../src/figure.h"
#include "../src/figure_list.h"

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

   /* assert_int_equal(fl->figures[0]->e1->x, 10);
    assert_int_equal(fl->figures[0]->e1->y, 20);*/

}

#endif
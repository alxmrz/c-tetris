#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/figure.h"
#include "../src/configuration.h"

#include "element_test.h"
#include "figure_test.h"
#include "figure_list.h"

/********************* Vector TESTS ********************************/

static void test_array(void **state) {
    int eSize = 10;
    Element *elements[eSize];

    for (int i = 0; i < eSize; i++) {
        Element * e = create_element(i, i);
        elements[i] = e;
    }

    for (int i = 0; i < eSize; i++) {
        if (elements[i]->x == 4) {
            free(elements[i]);
            elements[i] = NULL;   
        }
    }

    assert_null(elements[4]);
}



/****************************MAIN*****************************************/
int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_figure_O),
        cmocka_unit_test(test_element_moving_down),
        cmocka_unit_test(test_figure_move_left_on_edge_position),
        cmocka_unit_test(test_figure_move_left_on_none_edge_position),
        cmocka_unit_test(test_figure_move_right_on_edge_position),
        cmocka_unit_test(test_figure_move_right_on_none_edge_position),
        cmocka_unit_test(test_figure_move_down),
        cmocka_unit_test(test_figure_move_down_on_edge_position),
        cmocka_unit_test(test_array),
        cmocka_unit_test(test_fl_create_figure_list),
        cmocka_unit_test(test_fl_delete_figure_list),
        cmocka_unit_test(test_fl_push),
    };
 
    return cmocka_run_group_tests(tests, NULL, NULL);
}
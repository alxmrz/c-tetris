#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "element_test.h"
#include "figure_test.h"
#include "figure_list.h"
#include "game_test.h"

int main(void)
{
    const struct CMUnitTest figure_tests[] = {
        cmocka_unit_test(test_create_figure_O),
        cmocka_unit_test(test_create_figure_L),
        cmocka_unit_test(test_create_figure_J),
        cmocka_unit_test(test_create_figure_I),
        cmocka_unit_test(test_create_figure_S),
        cmocka_unit_test(test_create_figure_T),
        cmocka_unit_test(test_create_figure_Z),
        cmocka_unit_test(test_figure_move_left_on_edge_position),
        cmocka_unit_test(test_figure_move_left_on_none_edge_position),
        cmocka_unit_test(test_figure_move_right_on_edge_position),
        cmocka_unit_test(test_figure_move_right_on_none_edge_position),
        cmocka_unit_test(test_figure_move_down),
        cmocka_unit_test(test_figure_move_down_on_edge_position),
        cmocka_unit_test(test_figure_not_intersect_other_figure),
        cmocka_unit_test(test_figure_intersect_other_figure),
        cmocka_unit_test(test_figure_move_up),
        cmocka_unit_test(test_not_full_figure_move_up),
    };

    const struct CMUnitTest element_tests[] = {
        cmocka_unit_test(test_element_moving_down),
    };

    const struct CMUnitTest figure_list_tests[] = {
        cmocka_unit_test(test_fl_create_figure_list),
        cmocka_unit_test(test_fl_delete_figure_list),
        cmocka_unit_test(test_fl_is_figure_intersect_list),
        cmocka_unit_test(test_fl_is_figure_not_intersect_list),
        cmocka_unit_test(test_fl_figure_not_intersect_itself),
        cmocka_unit_test(test_fl_delete_one_line_elements),
        cmocka_unit_test(test_fl_push),
        cmocka_unit_test(test_fl_hashtable),
    };

    const struct CMUnitTest game_tests[] = {
        cmocka_unit_test(test_create_new_game),
        cmocka_unit_test(test_delete_game),
        cmocka_unit_test(test_stop_game),
    };

    int ft = cmocka_run_group_tests(figure_tests, NULL, NULL);
    int et = cmocka_run_group_tests(element_tests, NULL, NULL);
    int flt = cmocka_run_group_tests(figure_list_tests, NULL, NULL);
    int gt = cmocka_run_group_tests(game_tests, NULL, NULL);

    return (ft + et + flt + gt) >= 1;
}
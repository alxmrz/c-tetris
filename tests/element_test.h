#ifndef ELEMENT_TEST
#define ELEMENT_TEST

#include <cmocka.h>
#include "../src/figure.h"

static void test_element_moving_down(void **state) {
    Element element = {0, 0};

    move_down(&element);

    assert_int_equal(element.x, 0);
    assert_int_equal(element.y, ELEMENT_SIZE);
}

#endif
#ifndef GAME_TEST_MODULE
#define GAME_TEST_MODULE

#include "../src/game.h"
#include "cmocka.h"

static void test_create_new_game(void **state) {
    Game *game = create_new_game();

    assert_non_null(game->fl);
    assert_non_null(game->figure);
    assert_int_equal(0, game->score);
    assert_int_equal(0, game->isGameOver);
    assert_int_equal(0, game->downCounter);
    assert_int_equal(0, game->deleteCounter);

    delete_game(game);
}

static void test_delete_game(void **state) {
    Game *game = create_new_game();

    delete_game(game);
}

static void test_is_game_over(void **state) {
    Game *game = create_new_game();

    game->isGameOver = 1;

    assert_int_equal(1, is_game_over(game));

    delete_game(game);
}

#endif
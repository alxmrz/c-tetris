#include "malloc.h"
#include "game.h"

#include <SDL2/SDL_timer.h>

#include "figure_list.h"
#include "figure.h"
#include "configuration.h"

Game *create_new_game() {
    Game *game = malloc(sizeof(Game));
    game->fl = create_figure_list();
    game->figure = create_random_figure(FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
    game->nextFigure = create_random_figure(NEXT_FIGURE_START_X_POINT, NEXT_FIGURE_START_Y_POINT);
    game->score = 0;
    game->deleteCounter = 0;
    game->downCounter = 0;
    game->is_running = 1;
    game->is_restart_needed = 0;
    game->isGameOver = 0;

    return game;
}

void delete_game(Game *game) {
    if (game->fl) {
        delete_figure_list(game->fl);
    }

    if (game->figure) {
        delete_figure(game->figure);
    }

    if (game->nextFigure) {
        delete_figure(game->nextFigure);
    }

    free(game);
}

void update_game(Game *game) {
    if (is_game_over(game)) {
        return;
    }

    if (game->deleteCounter > 500) {
        game->score += delete_one_line_elements(game->fl) * 100;
        game->deleteCounter = 0;
    }

    if (game->downCounter >= 1000) {
        int res = move_down_figure(game->figure);
        if (res == 0) {
            fl_push(game->fl, game->figure);
            game->figure = game->nextFigure;
            move_figure_to_point(game->figure, FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
            game->nextFigure = create_random_figure(NEXT_FIGURE_START_X_POINT, NEXT_FIGURE_START_Y_POINT);
        } else {
            if (is_figure_intersect_list(game->fl, game->figure) == 1) {
                move_up_figure(game->figure);
                fl_push(game->fl, game->figure);
                game->figure = game->nextFigure;
                move_figure_to_point(game->figure, FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
                game->nextFigure = create_random_figure(NEXT_FIGURE_START_X_POINT, NEXT_FIGURE_START_Y_POINT);
            }
        }

        for (int i = 0; i < game->fl->size; i++) {
            const int result = move_down_figure(game->fl->figures[i]);
            if (result == 1) {
                if (is_figure_intersect_list(game->fl, game->fl->figures[i]) == 1) {
                    move_up_figure(game->fl->figures[i]);
                }
            }
        }

        game->downCounter = 0;
    }

    game->isGameOver = is_figure_intersect_list(game->fl, game->figure);
}

int is_game_over(Game *game) {
    return game->isGameOver;
}

void stop_game(Game *game) {
    game->is_running = 0;
}

void delay_game(Game *game) {
    SDL_Delay(FRAME_DELAY);
    increment_game_counters(game);
}

void increment_game_counters(Game *game) {
    game->downCounter += FRAME_DELAY;
    game->deleteCounter += FRAME_DELAY;
}

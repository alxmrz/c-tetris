#include <malloc.h>
#include <SDL2/SDL_timer.h>

#include "game.h"
#include "figure.h"
#include "figure_list.h"
#include "configuration.h"

#define MS_TO_DOWN_FIGURES      1000
#define MS_TO_DELETE_ONE_LINERS 500
#define SCORE_MULTIPLIER        100

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

void move_down_static_figures(Game *game) {
    for (int i = 0; i < game->fl->size; i++) {
        const int result = move_down_figure(game->fl->figures[i]);
        if (result == 1) {
            if (is_figure_intersect_list(game->fl, game->fl->figures[i]) == 1) {
                move_up_figure(game->fl->figures[i]);
            }
        }
    }
}

void update_game(Game *game) {
    if (is_game_over(game)) {
        return;
    }

    if (game->deleteCounter > MS_TO_DELETE_ONE_LINERS) {
        game->score += delete_one_line_elements(game->fl) * SCORE_MULTIPLIER;
        game->deleteCounter = 0;
    }

    if (game->downCounter >= MS_TO_DOWN_FIGURES) {
        move_down_game_figure(game);
        move_down_static_figures(game);
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

void create_next_figure(Game *game) {
    fl_push(game->fl, game->figure);
    game->figure = create_figure_by_type(game->nextFigure->type, FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
    delete_figure(game->nextFigure);
    game->nextFigure = create_random_figure(NEXT_FIGURE_START_X_POINT, NEXT_FIGURE_START_Y_POINT);
}

void move_down_game_figure(Game *game) {
    const int result = move_down_figure(game->figure);
    if (result == 0) {
        create_next_figure(game);
    } else {
        if (is_figure_intersect_list(game->fl, game->figure) == 1) {
            move_up_figure(game->figure);
            create_next_figure(game);
        }
    }
}

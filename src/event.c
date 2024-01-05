#include <SDL2/SDL.h>
#include "event.h"
#include "game.h"
#include "configuration.h"

void handle_events(Game *game) {
    SDL_Event windowEvent;

    while (SDL_PollEvent(&windowEvent)) {
        if (SDL_QUIT == windowEvent.type) {
            handle_game_exit_button_pressed(game);
            return;
        }

        if (SDL_KEYDOWN == windowEvent.type) {
            switch (windowEvent.key.keysym.sym) {
                case SDLK_LEFT:
                    handle_left_arrow_key_pressed(game);
                    break;
                case SDLK_RIGHT:
                    handle_right_arrow_key_pressed(game);
                    break;
                case SDLK_DOWN:
                    handle_down_arrow_key_pressed(game);
                    break;
                case SDLK_SPACE:
                    handle_space_key_pressed(game);
                    return;
                default:
                    break;
            }
        }
    }
}

void handle_game_exit_button_pressed(Game *game) {
    printf("Clicked Quit button\n");
    stop_game(game);
}

void handle_left_arrow_key_pressed(Game *game) {
    if (is_game_over(game)) {
        return;
    }

    move_left(game->figure);
    if (is_figure_intersect_list(game->fl, game->figure) == 1) {
        move_right(game->figure);
    }
}

void handle_right_arrow_key_pressed(Game *game) {
    if (is_game_over(game)) {
        return;
    }

    move_right(game->figure);
    if (is_figure_intersect_list(game->fl, game->figure) == 1) {
        move_left(game->figure);
    }
}

void handle_down_arrow_key_pressed(Game *game) {
    if (is_game_over(game)) {
        return;
    }

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
}

void handle_space_key_pressed(Game *game) {
    game->is_restart_needed = 1;
}

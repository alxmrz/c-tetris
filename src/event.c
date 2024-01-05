#include <SDL2/SDL.h>
#include "event.h"
#include "game.h"
#include "configuration.h"

void handle_events(Game *game) {
    SDL_Event windowEvent;

    while (SDL_PollEvent(&windowEvent)) {
        if (SDL_QUIT == windowEvent.type) {
            printf("Clicked Quit button");
            stop_game(game);
            return;
        }

        if (SDL_KEYDOWN == windowEvent.type) {
            switch (windowEvent.key.keysym.sym) {
                case SDLK_LEFT:
                    if (is_game_over(game)) {
                        break;
                    }

                    move_left(game->figure);
                    if (is_figure_intersect_list(game->fl, game->figure) == 1) {
                        move_right(game->figure);
                    }
                    break;
                case SDLK_RIGHT:
                    if (is_game_over(game)) {
                        break;
                    }

                    move_right(game->figure);
                    if (is_figure_intersect_list(game->fl, game->figure) == 1) {
                        move_left(game->figure);
                    }
                    break;
                case SDLK_DOWN:
                    if (is_game_over(game)) {
                        break;
                    }

                    int res = move_down_figure(game->figure);
                    if (res == 0) {
                        fl_push(game->fl, game->figure);
                        game->figure = create_random_figure(FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
                    } else {
                        if (is_figure_intersect_list(game->fl, game->figure) == 1) {
                            move_up_figure(game->figure);
                            fl_push(game->fl, game->figure);
                            game->figure = create_random_figure(FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
                        }
                    }
                    break;
                case SDLK_SPACE:
                    game->is_restart_needed = 1;
                    return;
                default:
                    break;
            }
        }
    }
}

void handle_game_exit_button_pressed(Game *game);

void handle_left_arrow_key_pressed(Game *game);

void handle_right_arrow_key_pressed(Game *game);

void handle_down_arrow_key_pressed(Game *game);

void handle_space_key_pressed(Game *game);

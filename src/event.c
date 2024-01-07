#include <SDL2/SDL.h>
#include "event.h"
#include "game.h"

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

    move_down_game_figure(game);
}

void handle_space_key_pressed(Game *game) {
    game->is_restart_needed = 1;
}

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>
#include <stdio.h>
#include "element.h"
#include "figure_list.h"
#include "configuration.h"
#include "event.h"
#include "game.h"
#include "graphics.h"

const int SCREEN_WIDTH = WINDOW_WIDTH;
const int SCREEN_HEIGHT = WINDOW_HEIGHT;

int main(int argc, char **args)
{
    if (!init_graphics())
    {
        return ERROR_CODE;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Tetris with SDL2!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("Can't create window: %s\n", SDL_GetError());
        return ERROR_CODE;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL)
    {
        printf("Can't create renderer: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return ERROR_CODE;
    }

    Game *game = create_new_game();

    while (game->is_running)
    {
        update_game(game);
        handle_events(game);

        if (game->is_restart_needed) {
            delete_game(game);
            game = create_new_game();
            continue;
        }

        render(window, ren, game);

        SDL_Delay(FRAME_DELAY);
        game->downCounter += FRAME_DELAY;
        game->deleteCounter += FRAME_DELAY;
    }

    delete_game(game);
    TTF_Quit();
    SDL_DestroyRenderer(ren);
    SDL_Quit();
    SDL_DestroyWindow(window);

    return 0;
};
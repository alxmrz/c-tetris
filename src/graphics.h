#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL2/SDL.h"
#include "figure.h"
#include "game.h"

typedef struct View {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int is_sdl_inited;
    int is_ttf_inited;
} View;

View *create_view();

void delete_view(View *);

int init_graphics();

int print_text(char *text, SDL_Rect *dst, SDL_Renderer *renderer, SDL_Color *color);

int print_score(int score, SDL_Renderer *renderer);

int print_next_figure_text(SDL_Renderer *renderer);

int print_title(SDL_Renderer *renderer);

int print_game_over(SDL_Renderer *renderer);

SDL_Color get_figure_color(Figure *figure);

void draw_figure(Figure *figure, SDL_Renderer *renderer);

int render_view(View *view, Game *game);

#endif

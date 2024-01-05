#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL2/SDL.h"
#include "figure.h"
#include "game.h"

int init_graphics();
int print_text(char *text, SDL_Rect *dst, SDL_Renderer *renderer, SDL_Color *color);
int print_score(int score, SDL_Renderer *renderer);
int print_title(SDL_Renderer *renderer);
int print_game_over(SDL_Renderer *renderer);
SDL_Color get_figure_color(Figure *figure);
void draw_figure(Figure *figure, SDL_Renderer *renderer);
int render(SDL_Window *window, SDL_Renderer *ren, Game *game);

#endif

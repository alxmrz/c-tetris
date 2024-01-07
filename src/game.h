#ifndef GAME_MODULE
#define GAME_MODULE

#include "figure.h"
#include "figure_list.h"

typedef struct Game {
    FigureList *fl;
    Figure *figure;
    Figure *nextFigure;
    int score;
    int downCounter;
    int deleteCounter;
    int isGameOver;
    int is_running;
    int is_restart_needed;
} Game;

Game *create_new_game();

void delete_game(Game *);

void update_game(Game *);

int is_game_over(Game *);

void stop_game(Game *);

void delay_game(Game *);

void increment_game_counters(Game *);

void create_next_figure(Game *game);

void move_down_game_figure(Game *game);

void move_down_static_figures(Game *game);
#endif

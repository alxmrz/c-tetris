#ifndef GAME_MODULE
#define GAME_MODULE

#include "figure.h"
#include "figure_list.h"

typedef struct Game {
    FigureList *fl;
    Figure *figure;
    int score;
    int downCounter;
    int deleteCounter;
    int isGameOver;
} Game;

Game *create_new_game();
void delete_game(Game *);

void update_game(Game *);
int is_game_over(Game *);

#endif
#ifndef EVENT_H
#define EVENT_H

#include "game.h"

void handle_events(Game *game);

void handle_game_exit_button_pressed(Game *game);

void handle_left_arrow_key_pressed(Game *game);

void handle_right_arrow_key_pressed(Game *game);

void handle_down_arrow_key_pressed(Game *game);

void handle_space_key_pressed(Game *game);

#endif //EVENT_H

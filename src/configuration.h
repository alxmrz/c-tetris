#ifndef CONFIGURATION_MODULE
#define CONFIGURATION_MODULE

#include "element.h"

#define SUCCESS_CODE              0
#define ERROR_CODE                1
#define WINDOW_WIDTH              480
#define WINDOW_HEIGHT             640
#define GAME_LEFT_BORDER          100
#define FRAME_DELAY               10  // milliseconds

#define NEXT_FIGURE_START_X_POINT 380
#define NEXT_FIGURE_START_Y_POINT 425
#define FIGURE_START_Y_POINT      100
#define FIGURE_START_X_POINT      GAME_LEFT_BORDER + ELEMENT_SIZE*5
#define GAME_RIGHT_BORDER         GAME_LEFT_BORDER + ELEMENT_SIZE*10
#define GAME_BOTTOM_BORDER        FIGURE_START_Y_POINT + ELEMENT_SIZE*20

#endif

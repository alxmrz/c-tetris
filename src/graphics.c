#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "configuration.h"
#include "figure.h"
#include "figure_list.h"
#include "game.h"
#include "graphics.h"

View *create_view() {
    if (!init_graphics()) {
        return NULL;
    }

    View *view = malloc(sizeof(View));
    if (view == NULL) {
        printf("Can't malloc View\n");
        TTF_Quit();
        SDL_Quit();

        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Tetris with SDL2!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Can't create window: %s\n", SDL_GetError());
        delete_view(view);

        return NULL;
    }

    view->is_ttf_inited = 1;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Can't create renderer: %s\n", SDL_GetError());
        delete_view(view);

        return NULL;
    }

    view->is_sdl_inited = 1;

    view->renderer = renderer;
    view->window = window;

    return view;
}

void delete_view(View *view) {
    if (view->is_ttf_inited) {
        TTF_Quit();
    }

    if (view->is_sdl_inited) {
        SDL_DestroyRenderer(view->renderer);
        SDL_Quit();
        SDL_DestroyWindow(view->window);
    }

    free(view);
}

int init_graphics() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != SUCCESS_CODE) {
        printf("Cant intitialize SDL: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() != SUCCESS_CODE) {
        printf("Cant intitialize TTF: %s\n", TTF_GetError());
        SDL_Quit();
        return 0;
    }

    return 1;
}

int print_text(char *text, SDL_Rect *dst, SDL_Renderer *renderer, SDL_Color *color) {
    TTF_Font *Sans = TTF_OpenFont("./resources/Sans.ttf", 24);
    if (Sans == NULL) {
        printf("Can't create font: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return ERROR_CODE;
    }

    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, text, *color);
    if (surfaceMessage == NULL) {
        printf("Can't create title surface: %s\n", TTF_GetError());
        TTF_CloseFont(Sans);
        TTF_Quit();
        SDL_Quit();
        return ERROR_CODE;
    }

    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (message == NULL) {
        printf("Can't create title message texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surfaceMessage);
        TTF_CloseFont(Sans);
        TTF_Quit();
        SDL_Quit();
        return ERROR_CODE;
    }

    SDL_RenderCopy(renderer, message, NULL, dst);

    TTF_CloseFont(Sans);
    SDL_DestroyTexture(message);
    SDL_FreeSurface(surfaceMessage);

    return SUCCESS_CODE;
}

int print_score(int score, SDL_Renderer *renderer) {
    char buf[20];
    snprintf(buf, 20, "Score: %d", score);
    SDL_Color color = {0, 0, 0xFF, 0};

    SDL_Rect messageRect = {360, 150, 100, 75};

    return print_text(buf, &messageRect, renderer, &color);
}

int print_next_figure_text(SDL_Renderer *renderer) {
    SDL_Color color = {0, 0, 0xFF, 0};

    SDL_Rect messageRect = {360, 350, 100, 75};

    return print_text("Next:", &messageRect, renderer, &color);
}

int print_title(SDL_Renderer *renderer) {
    SDL_Rect messageRect = {125, 0, 200, 100};
    SDL_Color color = {0, 0, 0xFF, 0};

    return print_text("Tetris", &messageRect, renderer, &color);
}

int print_game_over(SDL_Renderer *renderer) {
    SDL_Rect messageRect = {35, 260, 400, 100};
    SDL_Rect helperMessageRect = {100, 350, 300, 70};
    SDL_Color color = {0xFF, 0, 0, 0};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_Rect background = {30, 250, 420, 170};
    SDL_RenderFillRect(renderer, &background);

    print_text("Game Over", &messageRect, renderer, &color);
    print_text("Press <Space> to restart", &helperMessageRect, renderer, &color);

    return 1;
}

SDL_Color get_figure_color(Figure *figure) {
    SDL_Color color;
    switch (figure->type) {
        case 'O':
            color.r = 0xFF;
            color.g = 0x00;
            color.b = 0x00;
            break;
        case 'I':
            color.r = 0x00;
            color.g = 0xFF;
            color.b = 0x00;
            break;
        case 'J':
            color.r = 0x00;
            color.g = 0x00;
            color.b = 0xFF;
            break;
        case 'L':
            color.r = 0xFF;
            color.g = 0x00;
            color.b = 0xFF;
            break;
        case 'S':
            color.r = 0x00;
            color.g = 0xFF;
            color.b = 0xFF;
            break;
        case 'T':
            color.r = 0xFF;
            color.g = 0xFF;
            color.b = 0xFF;
            break;
        case 'Z':
            color.r = 0x30;
            color.g = 0x45;
            color.b = 0x55;
            break;

        default:
            color.r = 0xFF;
            color.g = 0x00;
            color.b = 0x00;
            break;
    }

    return color;
}

void draw_figure(Figure *figure, SDL_Renderer *renderer) {
    Element *elements[4];
    elements[0] = figure->e1;
    elements[1] = figure->e2;
    elements[2] = figure->e3;
    elements[3] = figure->e4;
    SDL_Color fColor = get_figure_color(figure);
    for (int j = 0; j < sizeof(elements) / sizeof(elements[0]); j++) {
        if (!elements[j]) {
            continue;
        }

        SDL_Rect rect = {elements[j]->x + 1, elements[j]->y + 1, ELEMENT_SIZE - 2, ELEMENT_SIZE - 2};
        SDL_SetRenderDrawColor(renderer, fColor.r, fColor.g, fColor.b, 0);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderDrawRect(renderer, &rect);
    }
}

int render_view(View *view, Game *game) {
    SDL_UpdateWindowSurface(view->window);
    SDL_SetRenderDrawColor(view->renderer, 160, 160, 160, 0);
    SDL_Rect mainRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    if (SDL_RenderFillRect(view->renderer, &mainRect) < 0) {
        printf("Can't resresh canvas: (%s)", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return ERROR_CODE;
    }

    draw_figure(game->figure, view->renderer);
    draw_figure(game->nextFigure, view->renderer);

    for (int i = 0; i < game->fl->size; i++) {
        if (game->fl->figures[i] == NULL) {
            break;
        }
        draw_figure(game->fl->figures[i], view->renderer);
    }

    SDL_Rect outer_rect = {GAME_LEFT_BORDER, FIGURE_START_Y_POINT, ELEMENT_SIZE * 10, ELEMENT_SIZE * 20};
    SDL_SetRenderDrawColor(view->renderer, 0, 0, 0, 0);
    SDL_RenderDrawRect(view->renderer, &outer_rect);

    print_next_figure_text(view->renderer);
    print_title(view->renderer);
    print_score(game->score, view->renderer);

    if (game->isGameOver) {
        print_game_over(view->renderer);
    }

    SDL_RenderPresent(view->renderer);

    return SUCCESS_CODE;
}

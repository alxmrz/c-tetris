#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>
#include <stdio.h>
#include "element.h"
#include "figure.h"
#include "figure_list.h"
#include "configuration.h"

#define SUCCESS_CODE 0
#define ERROR_CODE 1

const int SCREEN_WIDTH = WINDOW_WIDTH;
const int SCREEN_HEIGHT = WINDOW_HEIGHT;

int init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != SUCCESS_CODE)
    {
        printf("Cant intitialize SDL: %s\n", SDL_GetError());
        return ERROR_CODE;
    }

    if (TTF_Init() != SUCCESS_CODE)
    {
        printf("Cant intitialize TTF: %s\n", TTF_GetError());
        SDL_Quit();
        return ERROR_CODE;
    }

    return SUCCESS_CODE;
}

int print_text(char *text, SDL_Rect *dst, SDL_Renderer *renderer, SDL_Color *color)
{
    TTF_Font *Sans = TTF_OpenFont("./sources/Sans.ttf", 24);
    if (Sans == NULL)
    {
        printf("Can't create font: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return ERROR_CODE;
    }

    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, text, *color);
    if (surfaceMessage == NULL)
    {
        printf("Can't create title surface: %s\n", TTF_GetError());
        TTF_CloseFont(Sans);
        TTF_Quit();
        SDL_Quit();
        return ERROR_CODE;
    }

    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (message == NULL)
    {
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

int print_score(int score, SDL_Renderer *renderer)
{
    char buf[20];
    snprintf(buf, 20, "Score: %d", score);
    SDL_Color color = {0, 0, 0xFF, 0};

    SDL_Rect messageRect = {360, 150, 100, 75};

    return print_text(buf, &messageRect, renderer, &color);
}

int print_title(SDL_Renderer *renderer)
{
    SDL_Rect messageRect = {125, 0, 200, 100};
    SDL_Color color = {0, 0, 0xFF, 0};

    return print_text("Tetris", &messageRect, renderer, &color);
}

int print_game_over(SDL_Renderer *renderer)
{
    SDL_Rect messageRect = {35, 260, 400, 100};
    SDL_Rect helperMessageRect = {100, 350, 300, 70};
    SDL_Color color = {0xFF, 0, 0, 0};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_Rect background = {30, 250, 420, 170};
    SDL_RenderFillRect(renderer, &background);

    print_text("Game Over", &messageRect, renderer, &color);
    print_text("Press <Space> to restart", &helperMessageRect, renderer, &color);
}

SDL_Color get_figure_color(Figure *figure)
{
    SDL_Color color;
    switch (figure->type)
    {
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
        color.r = 0xFF;
        color.g = 0x0F;
        color.b = 0xF0;
        break;

    default:
        color.r = 0xFF;
        color.g = 0x00;
        color.b = 0x00;
        break;
    }

    return color;
}

void game_update(FigureList *fl, Figure **figure, SDL_Event *windowEvent, int *deleteCounter, int *downCounter, int *score)
{
    if (*deleteCounter > 500)
    {
        *score += delete_one_line_elements(fl) * 100;
        *deleteCounter = 0;
    }

    if (*downCounter >= 1000)
    {
        int res = move_down_figure(*figure);
        if (res == 0)
        {
            fl_push(fl, *figure);
            *figure = create_random_figure(FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
        }
        else
        {
            if (is_figure_intersect_list(fl, *figure) == 1)
            {
                move_up_figure(*figure);
                fl_push(fl, *figure);
                *figure = create_random_figure(FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
            }
        }

        for (int i = 0; i < fl->size; i++)
        {
            int res = move_down_figure(fl->figures[i]);
            if (res == 1)
            {
                if (is_figure_intersect_list(fl, fl->figures[i]) == 1)
                {
                    move_up_figure(fl->figures[i]);
                }
            }
        }

        *downCounter = 0;
    }
}

void start_new_game(FigureList **fl, Figure **figure, int *deleteCounter, int *downCounter, int *score)
{
    delete_figure_list(*fl);
    delete_figure(*figure);

    *fl = create_figure_list();
    *figure = create_random_figure(FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
    *deleteCounter = 0;
    *downCounter = 0;
    *score = 0;
}

int main(int argc, char **args)
{
    if (init() != 0)
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

    // Figure that can be moved by player
    Figure *figure = create_random_figure(FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
    // List of previous moved figures
    FigureList *fl = create_figure_list();
    int score = 0;

    SDL_Event windowEvent;

    int downCounter = 0;
    int deleteCounter = 0;
    int gameOver = 0;

    while (1)
    {
        if (!gameOver)
        {
            game_update(fl, &figure, &windowEvent, &deleteCounter, &downCounter, &score);
        }
        if (SDL_PollEvent(&windowEvent))
        {
            
            if (SDL_QUIT == windowEvent.type)
            {
                fprintf(stdout, "clickQuit");
                break;
            }
            if (SDL_KEYDOWN == windowEvent.type)
            {
                switch (windowEvent.key.keysym.sym)
                {
                case SDLK_LEFT:
                    if (gameOver) break;
                    move_left(figure);
                    if (is_figure_intersect_list(fl, figure) == 1)
                    {
                        move_right(figure);
                    }
                    break;
                case SDLK_RIGHT:
                    if (gameOver) break;
                    move_right(figure);
                    if (is_figure_intersect_list(fl, figure) == 1)
                    {
                        move_left(figure);
                    }
                    break;
                case SDLK_DOWN:
                    if (gameOver) break;
                    int res = move_down_figure(figure);
                    if (res == 0)
                    {
                        fl_push(fl, figure);
                        figure = create_random_figure(FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
                    }
                    else
                    {
                        if (is_figure_intersect_list(fl, figure) == 1)
                        {
                            move_up_figure(figure);
                            fl_push(fl, figure);
                            figure = create_random_figure(FIGURE_START_X_POINT, FIGURE_START_Y_POINT);
                        }
                    }
                    break;
                case SDLK_SPACE:
                    start_new_game(&fl, &figure, &deleteCounter, &downCounter, &score);
                    gameOver = 0;
                    continue;
                default:
                    break;
                }
            }

            if (SDL_MOUSEBUTTONDOWN == windowEvent.type)
            {
                fprintf(stdout, "MOUSE BOTTON CLICKED");
            }
        }
        SDL_UpdateWindowSurface(window);
        SDL_SetRenderDrawColor(ren, 160, 160, 160, 0);
        SDL_Rect mainRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        if (SDL_RenderFillRect(ren, &mainRect) < 0)
        {
            printf("Can't resresh canvas: (%s)", SDL_GetError());
            TTF_Quit();
            SDL_Quit();
            return ERROR_CODE;
        }

        Element *elements[4];
        elements[0] = figure->e1;
        elements[1] = figure->e2;
        elements[2] = figure->e3;
        elements[3] = figure->e4;
        SDL_Color fColor = get_figure_color(figure);
        for (int j = 0; j < sizeof(elements) / sizeof(elements[0]); j++)
        {
            SDL_Rect rect = {elements[j]->x + 1, elements[j]->y + 1, ELEMENT_SIZE - 2, ELEMENT_SIZE - 2};
            SDL_SetRenderDrawColor(ren, fColor.r, fColor.g, fColor.b, 0);
            SDL_RenderFillRect(ren, &rect);
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
            SDL_RenderDrawRect(ren, &rect);
        }

        for (int i = 0; i < fl->size; i++)
        {
            if (fl->figures[i] == NULL)
            {
                break;
            }
            Element *elements[4];
            elements[0] = fl->figures[i]->e1;
            elements[1] = fl->figures[i]->e2;
            elements[2] = fl->figures[i]->e3;
            elements[3] = fl->figures[i]->e4;
            SDL_Color fColor = get_figure_color(fl->figures[i]);
            for (int j = 0; j < sizeof(elements) / sizeof(elements[0]); j++)
            {
                if (!elements[j]) continue;

                SDL_Rect rect = {elements[j]->x + 1, elements[j]->y + 1, ELEMENT_SIZE - 2, ELEMENT_SIZE - 2};
                SDL_SetRenderDrawColor(ren, fColor.r, fColor.g, fColor.b, 0);
                SDL_RenderFillRect(ren, &rect);
                SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
                SDL_RenderDrawRect(ren, &rect);
            }
        }

        SDL_Rect outer_rect = {GAME_LEFT_BORDER, FIGURE_START_Y_POINT, ELEMENT_SIZE * 10, ELEMENT_SIZE * 20};
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
        SDL_RenderDrawRect(ren, &outer_rect);

        if (is_figure_intersect_list(fl, figure))
        {
            gameOver = 1;
            print_game_over(ren);
        }

        print_title(ren);
        print_score(score, ren);
        SDL_RenderPresent(ren);

        fflush(stdout);
        SDL_Delay(10);
        downCounter += 10;
        deleteCounter += 10;
    }
    delete_figure(figure);

    TTF_Quit();
    SDL_DestroyRenderer(ren);
    SDL_Quit();
    SDL_DestroyWindow(window);

    return 0;
};
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>
#include <stdio.h>
#include "element.h"
#include "figure.h"
#include "figure_list.h"
#include "configuration.h"

const int SCREEN_WIDTH = WINDOW_WIDTH;
const int SCREEN_HEIGHT = WINDOW_HEIGHT;

int main (int argc, char ** args) {
    
    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        return 1;
    }

    if (TTF_Init() != 0)
    {
        printf("%s", "Cant intitialize TTF_init");
        SDL_Quit();
        return 1;
    }

    SDL_Surface* screen_surface = NULL;

    SDL_Window* window = NULL;

    window = SDL_CreateWindow("Hello, SDL 2!",SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 
    SDL_WINDOW_SHOWN);
    
    if (window == NULL) {
        return 1;
    }

    TTF_Font* Sans = TTF_OpenFont("./sources/Sans.ttf", 24);
    if (Sans == NULL) {
        printf("Error on font creation: %s", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL) {
        return 0;
    }

    FigureList *fl = create_figure_list();
    Figure *figure = create_random_figure(FIGURE_START_X_POINT,FIGURE_START_Y_POINT);
    
    SDL_Event windowEvent;
    float downCounter = 0.0;
    float deleteCounter = 0.0;


    SDL_Color titleColor = {0, 0, 0xFF, 0};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Tetris", titleColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
    if (message == NULL) {
        printf("Cant init texture: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Rect messageRect = {125, 0, 200, 100};

    while (1) {
        SDL_UpdateWindowSurface(window);
        //SDL_FillRect(screen_surface, NULL, SDL_MapRGB( screen_surface->format, 0, 255, 0));
        SDL_SetRenderDrawColor(ren, 255, 255, 0, 0);
        SDL_Rect mainRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        if (SDL_RenderFillRect(ren, &mainRect) < 0) {
            printf("ERROR: (%s)", SDL_GetError());
        }

        if (deleteCounter >500) {
            delete_one_line_elements(fl);
            deleteCounter=0;
        }

        if (downCounter >= 1000) {
            int res = move_down_figure(figure);
            if (res == 0) {
                fl_push(fl, figure);
                figure = create_random_figure(FIGURE_START_X_POINT,FIGURE_START_Y_POINT);
            } else {
                if (is_figure_intersect_list(fl, figure) == 1) {
                    move_up_figure(figure);
                    fl_push(fl, figure);
                    figure = create_random_figure(FIGURE_START_X_POINT,FIGURE_START_Y_POINT);
                }
            }

            for (int i = 0; i < fl->size; i++) {
                int res = move_down_figure(fl->figures[i]);
                if (res == 1) {
                    if (is_figure_intersect_list(fl, fl->figures[i]) == 1) {
                        move_up_figure(fl->figures[i]);
                    }
                }
            }


            downCounter = 0;
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
                        move_left(figure);
                        if (is_figure_intersect_list(fl, figure) == 1) {
                            move_right(figure);
                        }
                        break;
                    case SDLK_RIGHT:
                        move_right(figure);
                        if (is_figure_intersect_list(fl, figure) == 1) {
                            move_left(figure);
                        }
                        break;
                    case SDLK_DOWN:
                        int res = move_down_figure(figure);
                        if (res == 0) {
                            fl_push(fl, figure);
                            figure = create_random_figure(FIGURE_START_X_POINT,FIGURE_START_Y_POINT);
                        } else {
                            if (is_figure_intersect_list(fl, figure) == 1) {
                                move_up_figure(figure);
                                fl_push(fl, figure);
                                figure = create_random_figure(FIGURE_START_X_POINT,FIGURE_START_Y_POINT);
                            }
                        }
                        break;        
                    default:
                      break;
                }

            }

            if (SDL_MOUSEBUTTONDOWN == windowEvent.type)
            {
                fprintf(stdout, "MOUSE BOTTON CLICKED");
            }
        }
        
            Element *elements[4];
            elements[0] = figure->e1;
            elements[1] = figure->e2;
            elements[2] = figure->e3;
            elements[3] = figure->e4;
            for (int j = 0; j < sizeof(elements) / sizeof(elements[0]); j++) {
                SDL_Rect rect= {elements[j]->x, elements[j]->y,ELEMENT_SIZE,ELEMENT_SIZE};
                SDL_Rect inrect= {elements[j]->x+1, elements[j]->y+1,ELEMENT_SIZE-1,ELEMENT_SIZE-1};

                SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
                SDL_RenderFillRect(ren, &rect);

                SDL_SetRenderDrawColor(ren, 0xFF, 0, 0, 0);
                SDL_RenderFillRect(ren, &inrect); 
            }

        for (int i = 0; i < fl->size; i++) {
            if (fl->figures[i] == NULL) {
                break;
            }
            Element *elements[4];
            elements[0] = fl->figures[i]->e1;
            elements[1] = fl->figures[i]->e2;
            elements[2] = fl->figures[i]->e3;
            elements[3] = fl->figures[i]->e4;
            for (int j = 0; j < sizeof(elements) / sizeof(elements[0]); j++) {
                if (!elements[j])continue;
                SDL_Rect rect= {elements[j]->x, elements[j]->y,ELEMENT_SIZE,ELEMENT_SIZE};
                SDL_Rect inrect= {elements[j]->x+1, elements[j]->y+1,ELEMENT_SIZE-1,ELEMENT_SIZE-1};

                SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
                SDL_RenderFillRect(ren, &rect);

                SDL_SetRenderDrawColor(ren, 0xFF, 0, 0, 0);
                SDL_RenderFillRect(ren, &inrect);

            }


        }

        SDL_Rect outer_rect = {GAME_LEFT_BORDER, FIGURE_START_Y_POINT, ELEMENT_SIZE * 10 , ELEMENT_SIZE * 20};
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
        SDL_RenderDrawRect(ren, &outer_rect);
        
        if (SDL_RenderCopy(ren, message, NULL, &messageRect) != 0 ) {
            printf("Error on render copy: %s\n", SDL_GetError());
        };

        SDL_RenderPresent(ren);

        fflush(stdout); 
        SDL_Delay(10);
        downCounter += 10;
        deleteCounter +=10;

    }
    TTF_CloseFont(Sans);
    TTF_Quit();
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
    SDL_DestroyRenderer(ren);
    delete_figure(figure);
    SDL_Quit();
    SDL_DestroyWindow(window);


    return 0;
   

};
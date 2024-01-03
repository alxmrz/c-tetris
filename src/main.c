#include <SDL2/SDL.h>
#include <unistd.h>
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

    SDL_Surface* screen_surface = NULL;

    SDL_Window* window = NULL;

    window = SDL_CreateWindow("Hello, SDL 2!",SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 
    SDL_WINDOW_SHOWN);
    
    if (window == NULL) {
        return 1;
    }

    screen_surface = SDL_GetWindowSurface(window);
    /*SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL) {
        return 0;
    }*/

    FigureList *fl = create_figure_list();
    Figure *figure = create_o_figure(FIGURE_START_X_POINT,FIGURE_START_Y_POINT);

    SDL_Event windowEvent;
    float downCounter = 0.0;
    while (1) {
        SDL_UpdateWindowSurface(window);
        SDL_FillRect(screen_surface, NULL, SDL_MapRGB( screen_surface->format, 0, 255, 0));

        if (downCounter >= 1000) {
            /*for (int i = 0; i < sizeof(elements) / sizeof(Element); i++) {
                elements[i]->y += ELEMENT_SIZE;
            }*/
            delete_one_line_elements(fl);

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
                            figure = create_o_figure(FIGURE_START_X_POINT,FIGURE_START_Y_POINT);
                        } else {
                            if (is_figure_intersect_list(fl, figure) == 1) {
                                move_up_figure(figure);
                                fl_push(fl, figure);
                                figure = create_o_figure(FIGURE_START_X_POINT,FIGURE_START_Y_POINT);
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

                SDL_FillRect(screen_surface, &rect, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));
                SDL_FillRect(screen_surface, &inrect, SDL_MapRGB(screen_surface->format, 0xFF, 0x00, 0x00));

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

                SDL_FillRect(screen_surface, &rect, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));
                SDL_FillRect(screen_surface, &inrect, SDL_MapRGB(screen_surface->format, 0xFF, 0x00, 0x00));

            }


        }
        SDL_Rect rect1 = {GAME_LEFT_BORDER, FIGURE_START_Y_POINT, 1, GAME_BOTTOM_BORDER-FIGURE_START_Y_POINT};
        SDL_Rect rect2 = {GAME_LEFT_BORDER, GAME_BOTTOM_BORDER, GAME_RIGHT_BORDER-GAME_LEFT_BORDER, 1};
        SDL_Rect rect3 = {GAME_RIGHT_BORDER, FIGURE_START_Y_POINT, 1, GAME_BOTTOM_BORDER-FIGURE_START_Y_POINT};

        SDL_FillRect(screen_surface, &rect1, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));
        SDL_FillRect(screen_surface, &rect2, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));
        SDL_FillRect(screen_surface, &rect3, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));


        /*SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawLine(ren, 0, 0, 50, 50);*/

        fflush(stdout); 
        SDL_Delay(10);
        downCounter += 10;
    }

    delete_figure(figure);
    SDL_Quit();
    SDL_DestroyWindow(window);


    return 0;
   

};
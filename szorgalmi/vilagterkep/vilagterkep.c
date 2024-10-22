#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <../../src/include/SDL2/SDL.h>
#include <../../src/include/SDL2/SDL2_gfxPrimitives.h>

int main(int argc, char *argv[])
{

    /*szelesseg, magassagertek meghatarozasa*/
    const int WIDTH = 1080, HEITH = 540;

    /* SDL inicializalasa, hibak kezelese, az infoc-n talalhato anyagok alapjan*/
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    /*az ablak letrehozasa*/
    SDL_Window *window = SDL_CreateWindow("Elso grafikus szorgalmi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEITH, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    // csucsok
    Sint16 x[] = {100, 150, 180, 400};
    Sint16 y[] = {111, 200, 115, 80};

    /* a poligonok */
    aapolygonRGBA(renderer, x, y, 4, 255, 0, 255, 255);

    /* az ez utani resz is az infoc-n talalhato programreszleten alapul */
    SDL_RenderPresent(renderer);

    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT && ev.type != SDL_MOUSEBUTTONDOWN)
    {
    }

    SDL_Quit();

    return 0;
}
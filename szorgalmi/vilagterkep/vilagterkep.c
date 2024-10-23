#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <../../src/include/SDL2/SDL.h>
#include <../../src/include/SDL2/SDL2_gfxPrimitives.h>
#include <../../src/include/debugmalloc.h>



typedef struct Kordinata
{
    Sint16 x;
    Sint16 y;
} Kordinata;



Kordinata** kordinata(float* const fokok, int* hany_sokszog, int** hany_pont_egy_alakzat);


int main(int argc, char* argv[])
{
    extern float vilag[];
    /*szelesseg, magassagertek meghatarozasa*/
    const int WIDTH = 1080, HEITH = 540;

    /* SDL inicializalasa, hibak kezelese, az infoc-n talalhato anyagok alapjan
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    //az ablak letrehozasa
    SDL_Window* window = SDL_CreateWindow("Elso grafikus szorgalmi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEITH, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    // csucsok
    Sint16 x[] = { 100, 150, 180, 400 };
    Sint16 y[] = { 111, 200, 115, 80 };

    //a poligonok
    aapolygonRGBA(renderer, x, y, 4, 255, 0, 255, 255);

    // az ez utani resz is az infoc-n talalhato programreszleten alapul
    SDL_RenderPresent(renderer);

    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT && ev.type != SDL_MOUSEBUTTONDOWN)
    {
    }

    SDL_Quit();
    */
    int poligonok = 0;
    int* pontok_soronkent = NULL;
    Kordinata** kesz_kordinata = kordinata(vilag, &poligonok, &pontok_soronkent);
    if (kesz_kordinata != NULL && pontok_soronkent != NULL) {
        for (int i = 0; i < poligonok; i++) {
            for (int j = 0; j < pontok_soronkent[i]; j++) {
                printf("Polygon %d, Point %d: (%d, %d)\n",
                    i, j, kesz_kordinata[i][j].x, kesz_kordinata[i][j].y);
            }
        }
        for (int i = 0; i < poligonok; i++) {
            free(kesz_kordinata[i]);
        }
        free(kesz_kordinata);
        free(pontok_soronkent);
    }
    return 0;
}

//visszaadja a hany sokszog int-ben hogy hany alakzatot olvasott be, es a hany_pont.. tombben, hogy egy alakzatban hany pont van.
Kordinata** kordinata(float* const fokok, int* hany_sokszog, int** hany_pont_egy_alakzat)
{
    //szamoljuk meg hany kordinata van az adott tombokben-a foglalt 2D tomb magassaga
    int alakzatok_szama = 0;
    for (int i = 0;fokok[i] != -1; i++) {
        if (i % 2 == 0 && fokok[i] == 0 && fokok[i + 1] == 0) { /*azert kell a plusz i paros feltetel, hogy ne szamoljuk bele ha valamelyik kordinata 0-ra vegzodik*/
            alakzatok_szama++;
        }
    }
    /*visszadom az alakzatok szamat*/
    *hany_sokszog = alakzatok_szama;
    if (alakzatok_szama == 0) {
        return NULL;
    }



    Kordinata** ujkordinatak = (Kordinata**)malloc(alakzatok_szama * sizeof(Kordinata*));
    if (ujkordinatak == NULL) {
        return NULL;
    }
    /*egy tombot csinalok amiben tarolom mekkora egy alakzat*/
    *hany_pont_egy_alakzat = (int*)malloc(alakzatok_szama * sizeof(int));
    if (*hany_pont_egy_alakzat == NULL) {
        free(ujkordinatak);
        return NULL;
    }
    //szamoljuk meg hogy milyen hosszuak azok a sorok
    int sorok_hossza = 0;
    alakzatok_szama = 0;
    for (int i = 0;fokok[i] != -1; i++) {
        if (i % 2 == 1) { /*azert kell 2 soronkent egyszer, mert 2 adat fer el egy kordinata strukturaba*/
            sorok_hossza++;
        }
        if (i % 2 == 0 && fokok[i] == 0 && fokok[i + 1] == 0) {
            ujkordinatak[alakzatok_szama] = (Kordinata*)malloc(sorok_hossza * sizeof(Kordinata));
            if (ujkordinatak[alakzatok_szama] == NULL) {
                // Clean up on allocation failure
                for (int j = 0; j < alakzatok_szama; j++) {
                    free(ujkordinatak[j]);
                }
                free(ujkordinatak);
                free(*hany_pont_egy_alakzat);
                return NULL;
            }
            *hany_pont_egy_alakzat[alakzatok_szama] = sorok_hossza;
            sorok_hossza = 0;
            alakzatok_szama++;
        }
    }
    //Mentsuk el az adatokat a regi tommbol egy megfelelo 2D tombbe 
    alakzatok_szama = 0;

    for (int i = 0; fokok[i] != -1; i++)
    {
        if (i % 2 == 0 && fokok[i] == 0 && fokok[i + 1] == 0) {
            sorok_hossza = 0;
            alakzatok_szama++;
            i++;
        }
        if (i % 2 == 0) {
            ujkordinatak[alakzatok_szama][sorok_hossza].x = (Sint16)fokok[i];
            sorok_hossza++;
        }
        if (i % 2 == 1) {
            ujkordinatak[alakzatok_szama][sorok_hossza].y = (Sint16)fokok[i];
            sorok_hossza++;
        }
    }
    return ujkordinatak;
}

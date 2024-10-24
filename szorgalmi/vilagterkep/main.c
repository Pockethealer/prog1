#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <../../src/include/SDL2/SDL.h>
#include <../../src/include/SDL2/SDL2_gfxPrimitives.h>
#include <../../src/include/debugmalloc.h>

/*a tavak.c es vilag.c fileokbol nem masoltam at a tomboket,
csak extern-el hivatkozom rajok, es compile soran behivatkoztam a file-t*/

/*csak azert hozom ki globalis valtozonak hogy ne kelljen tobb argumentumba bevinni a fv-eknek.*/
const int WIDTH = 1080, HEIGHT = 540;

/*az egyes file-okon beluli poligonoknak a strukturaja, x es y kordinata tombokkel*/
typedef struct Alakzat
{
    Sint16* x;
    Sint16* y;
    int pontok_szama;
} Alakzat;
/*az adott poligonok tombjenek a strukturaja*/
typedef struct Terkep
{
    Alakzat* alakzatok;
    int alakzatok_szama;
} Terkep;

/*Megszamolja hany alakzat van a tombben, es megnezi hogy hany kordinataja
van a legnagyobb alakzatnak hogy azt hasznalja buffernek*/
int alakzatot_szamol(const float* kordinatak, int* max_buffer_meret)
{
    int alakzatok_szama = 0;
    int i = 0;
    *max_buffer_meret = 0;
    int buffer = 0;
    /*elmegyek a tomb vegeig, minden egyes 0,0-nal iteralom a szamlalot kozte pedig iteralom a buffert*/
    while (!(kordinatak[i] == -1 && kordinatak[i + 1] == -1))
    {
        if (kordinatak[i] == 0 && kordinatak[i + 1] == 0)
        {
            alakzatok_szama++;
            if (*max_buffer_meret < buffer) {
                *max_buffer_meret = buffer;
            }
            buffer = 0;
        }
        i += 2;
        buffer++;
    }
    return alakzatok_szama;
}
/*lemasolja a tombbol az argumentumban kapott terkep strukturanak az adott alakzataba a pontokat, majd visszadja hany pontot masolt*/
int pontot_masol(const float* kordinatak, int keresett_alakzat, int buffer_meret, Terkep* terkep)
{
    int pontok_szama = 0;
    int aktualis_alakzat = 0;
    int i = 0;
    /*elmegy a keresett helyre:*/
    while (aktualis_alakzat < keresett_alakzat && !(kordinatak[i] == -1 && kordinatak[i + 1] == -1)) {
        if (kordinatak[i] == 0 && kordinatak[i + 1] == 0) {
            aktualis_alakzat++;
        }
        i += 2;
    }

    if (kordinatak[i] == -1 && kordinatak[i + 1] == -1) {
        return 0;
    }
    /*buffert csinal a pontoknak*/
    Sint16* bufferx = (Sint16*)malloc(buffer_meret * sizeof(Sint16));
    Sint16* buffery = (Sint16*)malloc(buffer_meret * sizeof(Sint16));
    if (bufferx == NULL || buffery == NULL) {
        printf("Nem sikerult lefoglalni a buffert");
        return -1;
    }
    /*bemasolja a keresett kordinatakat a bufferbe, es leszamolja mekkora helyet kell foglalni tanylegesen,
    kozben atvaltja a fokot tenyleges kepernyo kordinatara*/
    while (!(kordinatak[i] == 0 && kordinatak[i + 1] == 0))
    {


        bufferx[pontok_szama] = (Sint16)(((kordinatak[i] + 180) / 360) * WIDTH);
        buffery[pontok_szama] = (Sint16)(((90 - kordinatak[i + 1]) / 180) * HEIGHT);
        pontok_szama++;
        i += 2;
    }
    /*atmasolja a bufferbol a tenylegesen foglalt helyre a kordinatakat:*/
    terkep->alakzatok[keresett_alakzat].x = (Sint16*)malloc(pontok_szama * sizeof(Sint16));
    terkep->alakzatok[keresett_alakzat].y = (Sint16*)malloc(pontok_szama * sizeof(Sint16));
    if (terkep->alakzatok[keresett_alakzat].x == NULL || terkep->alakzatok[keresett_alakzat].y == NULL) {
        printf("Nem sikerult lefoglalni a kordinatak tombjet.");
        return -1;
    }

    for (int j = 0; j < pontok_szama; j++) {
        terkep->alakzatok[keresett_alakzat].x[j] = bufferx[j];
        terkep->alakzatok[keresett_alakzat].y[j] = buffery[j];
    }
    /*felszabaditja a buffert:*/
    free(bufferx);
    free(buffery);
    return pontok_szama;
}
/*elkesziti a hasznalt terkep strukturat*/
Terkep beolvas(const float* tomb)
{
    Terkep terkep = { NULL, 0 };
    int pontok_buffer;
    terkep.alakzatok_szama = alakzatot_szamol(tomb, &pontok_buffer);
    terkep.alakzatok = malloc(terkep.alakzatok_szama * sizeof(Alakzat));
    if (terkep.alakzatok == NULL)
        return terkep;
    for (int i = 0; i < terkep.alakzatok_szama; i++)
    {
        terkep.alakzatok[i].pontok_szama = pontot_masol(tomb, i, pontok_buffer, &terkep);
        /*Ha nem sikerul a foglalas barmelyik sorra, fel kell szabaditani az osszes elozo sorra lefoglalt memoriat.*/
        if (terkep.alakzatok[i].pontok_szama == -1) {
            printf("Nem sikerult atmasolni a kordinatakat");
            for (int j = i;j >= 0;j--) {
                free(terkep.alakzatok[i].x);
                free(terkep.alakzatok[i].y);
            }
            free(terkep.alakzatok);
            return terkep;
        }
    }
    return terkep;
}
/*felszabaditja az adott terkep strukturat*/
void terkep_felszabadit(Terkep* terkep)
{
    if (terkep == NULL)
        return;

    for (int i = 0; i < terkep->alakzatok_szama; i++)
    {
        free(terkep->alakzatok[i].x);
        free(terkep->alakzatok[i].y);

    }
    free(terkep->alakzatok);
    terkep->alakzatok = NULL;
    terkep->alakzatok_szama = 0;
}
/*kirajzolja az adott renderen a terkepet.*/
void rajzol(SDL_Renderer* renderer, Terkep* terkep, int* szin) {
    for (int i = 0; i < terkep->alakzatok_szama; i++)
    {
        aapolygonRGBA(renderer, terkep->alakzatok[i].x, terkep->alakzatok[i].y, terkep->alakzatok[i].pontok_szama, 0, 0, 0, 0);
        filledPolygonRGBA(renderer, terkep->alakzatok[i].x, terkep->alakzatok[i].y, terkep->alakzatok[i].pontok_szama, szin[0], szin[1], szin[2], szin[3]);
    }
}
int main(int argc, char** argv) {
    extern float vilag[];
    extern float tavak[];
    int KEK[] = { 0,0,139,255 };
    int ZOLD[] = { 95,200,0,255 };
    /*a ket terkep struktura beolvasasa, a megfelelo tombbol, illetve ellenorzes hogy sikerult-e beolvasni*/
    Terkep terkepv = beolvas(vilag);
    Terkep terkept = beolvas(tavak);
    if (terkepv.alakzatok == NULL || terkept.alakzatok == NULL) {
        return -1;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window* window = SDL_CreateWindow("Vilagterkep", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
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
    /*Kek hatter beallitasa*/
    SDL_SetRenderDrawColor(renderer, KEK[0], KEK[1], KEK[2], KEK[3]);
    SDL_RenderClear(renderer);
    /*a poligonok kirajzolasa*/
    rajzol(renderer, &terkepv, ZOLD);
    rajzol(renderer, &terkept, KEK);
    SDL_RenderPresent(renderer);
    SDL_Event ev;
    /*Varakozas a kilepesre, bezarassal, vagy kattintassal*/
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT && ev.type != SDL_MOUSEBUTTONDOWN)
    {
    }
    SDL_Quit();
    /*Memoria felszabaditasa*/
    terkep_felszabadit(&terkepv);
    terkep_felszabadit(&terkept);

    return 0;

}

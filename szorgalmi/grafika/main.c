#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    /*szelesseg, magassag, es epszilon ertek meghatarozasa*/
    int w=640, h=480;
    double eps=1;

    /* SDL inicializalasa, hibak kezelese, az elso resz vazlata az infoc-n talalhato programreszleten alapul*/
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    /*az ablak merete 640*480pixel*/
    SDL_Window *window = SDL_CreateWindow("Elso grafikus szorgalmi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    /*a tavolsagok osszehasonlitasanal nem lehet teljes egyenloseget varni,
    *mivel a felbontas veges ezert nem lesznek olyan diszkret ertekek,
    *ahol ket tavolsag pontosan megegyezik, ezert kozeliteni kell:
    *|tav1-tav2|<epsilon. Magasabb felbontasnal lehet csokkenteni az erteket.
    *En most 1-nek valasztottam, mert a 0.1 meg tul kicsi, tul nagy eps meg torz kepet eredmenyez.*/

    /*mivel egy floating point erteket varunk majd az epsilonhoz valo viszonyitasnal
    *ezert nem hasznalhatjuk az abs() fv-t ami intet ad vissza, ezert a fabs() fv-t fogom hasznalni.
    *Ket pont tavolsaganal nem kell abszolut ertek, hiszen az automatikusan egy pozitiv szam.*/

    for(int i=0;i<w;++i){

        for(int j=0;j<h;++j){

            if(fabs(sqrt(pow(320-i,2)+pow(240-j,2))-200)<eps){
                pixelRGBA(renderer, i, j, 255, 0, 0, 255);}

            if(fabs((sqrt(pow(240-i,2)+pow(200-j,2))+sqrt(pow(400-i,2)+pow(280-j,2)))-250)<eps){
                pixelRGBA(renderer, i, j, 0, 255, 0, 255);}

            if(fabs(fabs(sqrt(pow(240-i,2)+pow(240-j,2))-sqrt(pow(400-i,2)+pow(240-j,2)))-100)<eps){
                pixelRGBA(renderer, i, j, 0, 0, 255, 255);}

            if(fabs(sqrt(pow(320-i,2)+pow(240-j,2))-fabs(400-i))<eps){
                pixelRGBA(renderer, i, j, 255, 255, 255, 255);}

    }}


    /* a szoveg */
    stringRGBA(renderer, 90, 240, "Kor", 255, 0, 0, 255);
    stringRGBA(renderer, 130, 270, "Ellipszis", 0, 255, 0, 255);
    stringRGBA(renderer, 350, 120, "Hiperbola", 0, 0, 255, 255);
    stringRGBA(renderer, 290, 240, "Parabola", 255, 255, 255, 255);

    /* az ez utani resz is az infoc-n talalhato programreszleten alapul */
    SDL_RenderPresent(renderer);

    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
    }

    SDL_Quit();

    return 0;
}

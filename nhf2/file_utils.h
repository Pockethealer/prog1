#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"


typedef struct Osszetevo {
    char nev[51];
    char tipus[51];
    double mennyiseg;
} Osszetevo;
typedef struct Etel {
    char nev[51];
    int osszetevok_szama;
    Osszetevo* osszetevok;
    char elkeszites[1000];
} Etel;
typedef struct Receptkonyv {
    int etelek_szama;
    Etel* etelek;
} Receptkonyv;

typedef struct Egyedi_osszetevok {
    Osszetevo* egyedi_osszetevok;
    int egyedi_osszetevok_szama;
}Egyedi_osszetevok;

Receptkonyv* receptek_beolvas(void);
void receptet_fileba_ment(Receptkonyv* r);
void receptkonyv_felszabadit(Receptkonyv* r);

Egyedi_osszetevok* osszetevo_beolvas(void);
void osszetevo_fileba_ment(Receptkonyv* r);
void egyedi_osszetevo_felszabadit(Egyedi_osszetevok* e);

Receptkonyv* program_megnyit(void);
void program_bezar(Receptkonyv* r);


#endif

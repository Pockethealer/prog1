#ifndef FILE_UTILS_H
#define FILE_UTILS_H
typedef struct Osszetevo
{
    char nev[50];
    char tipus[50];
    int mennyiseg;
} Osszetevo;
typedef struct Etel
{
    char nev[50];
    int osszetevok_szama;
    Osszetevo* osszetevok;
    char elkeszites[1000];
} Etel;
typedef struct Receptkonyv
{
    int etelek_szama;
    Etel* etelek;
} Receptkonyv;

Receptkonyv* receptek_beolvas(void);
void fileba_ment(Receptkonyv receptek);
void receptkonyv_felszabadit(Receptkonyv* r);

#endif

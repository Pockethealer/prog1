#include <stdio.h>
#include <stdlib.h>

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
    Osszetevo *osszetevok;
    char elkeszites[1000];
} Etel;
typedef struct Receptkonyv
{
    int etelek_szama;
    Etel *etelek;
} Receptkonyv;

Receptkonyv *receptek_beolvas(void);
void fileba_ment(Receptkonyv receptek);

Receptkonyv *receptek_beolvas(void)
{
    Receptkonyv *r = (Receptkonyv *)malloc(sizeof(Receptkonyv));
    if (r == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!");
        return NULL;
    }
    FILE *f = fopen("receptek.txt", "r");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni a file-t!");
        return NULL;
    }
    fscanf(f, "%d", r->etelek_szama);
    r->etelek = (Etel *)malloc((r->etelek_szama) * sizeof(Etel));
    if (r->etelek == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!");
        return NULL;
    }
    int beolvasott_etelek_szama = 0;
    for (int i = 0; i < r->etelek_szama; i++)
    {
    }
    fclose(f);
}
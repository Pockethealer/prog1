#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"


typedef struct Osszetevo
{
    char nev[51];
    char tipus[51];
    double mennyiseg;
} Osszetevo;
typedef struct Etel
{
    char nev[51];
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

Receptkonyv* receptek_beolvas(void)
{
    Receptkonyv* r = (Receptkonyv*)malloc(sizeof(Receptkonyv));
    if (r == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        free(r);
        return NULL;
    }
    FILE* f;
    f = fopen("receptek.txt", "r");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni a file-t!\n");
        free(r);
        return NULL;
    }
    fscanf(f, "%d", &(r->etelek_szama));
    r->etelek = (Etel*)malloc((r->etelek_szama) * sizeof(Etel));
    if (r->etelek == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        free(r);
        free(r->etelek);
        fclose(f);
        return NULL;
    }
    printf("%d", r->etelek_szama);
    for (int i = 0; i < r->etelek_szama; i++)
    {
        if (fscanf(f, " %[^,],%d", r->etelek[i].nev, &(r->etelek[i].osszetevok_szama)) != 2) {
            printf("Hibas a receptek.txt file tartalma!");
            free(r->etelek);
            free(r);
            fclose(f);
            return NULL;
        }
        r->etelek[i].osszetevok = (Osszetevo*)malloc(r->etelek[i].osszetevok_szama * sizeof(Osszetevo));
        if (r->etelek[i].osszetevok == NULL)
        {
            printf("Nem lehetett lefoglalni a memoriat!\n");
            for (int j = 0; j < i; j++)
            {
                free(r->etelek[j].osszetevok);
            }
            free(r->etelek);
            fclose(f);
            free(r);
            return NULL;
        }
        for (int j = 0; j < r->etelek[i].osszetevok_szama; j++)
        {
            fscanf(f, " %[^,],%[^,],%lf",
                r->etelek[i].osszetevok[j].nev,
                r->etelek[i].osszetevok[j].tipus,
                &r->etelek[i].osszetevok[j].mennyiseg);
        }
        fscanf(f, " %[^\n]", r->etelek[i].elkeszites);
    }
    fclose(f);
    return r;
}
void receptkonyv_felszabadit(Receptkonyv* r)
{
    if (r == NULL)
    {
        return;
    }
    for (int i = 0; i < r->etelek_szama; i++)
    {
        free(r->etelek[i].osszetevok);
    }
    free(r->etelek);
    free(r);
}
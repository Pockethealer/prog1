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




void receptet_fileba_ment(Receptkonyv* r) {
    if (r == NULL) {
        printf("Nincs adat a receptkonyvben!\n");
        return;
    }

    FILE* f = fopen("receptek2.txt", "w");
    if (f == NULL) {
        printf("Nem lehet megnyitni a fájlt írásra.\n");
        return;
    }
    fprintf(f, "%d\n", r->etelek_szama);

    for (int i = 0; i < r->etelek_szama; i++) {
        Etel* etel = &r->etelek[i];

        fprintf(f, "%s,%d\n", etel->nev, etel->osszetevok_szama);

        for (int j = 0; j < etel->osszetevok_szama; j++) {
            Osszetevo* osszetevo = &etel->osszetevok[j];
            fprintf(f, "%s,%s,%.2lf\n", osszetevo->nev, osszetevo->tipus, osszetevo->mennyiseg);
        }
        fprintf(f, "%s\n", etel->elkeszites);
    }
    fclose(f);
}
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
    f = fopen("receptek2.txt", "r");
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
            fscanf(f, " %[^,], %[^,],%lf",
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



int osszetevo_letezik(char** egyedi_osszetevok, int darab, const char* osszetevo_neve) {
    /*Megnézi hogy az adott összetevő létezik-e, az osszetevok listazasahoz segédfüggvény*/
    for (int i = 0; i < darab; i++) {
        if (strcmp(egyedi_osszetevok[i], osszetevo_neve) == 0) {
            return 1;
        }
    }
    return 0;
}
void egyedi_osszetevo_felszabadit(Egyedi_osszetevok* e) {
    {
        if (e == NULL)
        {
            return;
        }
        free(e->egyedi_osszetevok);
        free(e);
    }
}
Egyedi_osszetevok* osszetevo_beolvas(void) {
    Egyedi_osszetevok* e = (Egyedi_osszetevok*)malloc(sizeof(Egyedi_osszetevok));
    if (e == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        free(e);
        return NULL;
    }
    FILE* f;
    f = fopen("osszetevok.txt", "r");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni a file-t!\n");
        free(e);
        return NULL;
    }
    fscanf(f, " %d", &(e->egyedi_osszetevok_szama));
    e->egyedi_osszetevok = (Osszetevo*)malloc(e->egyedi_osszetevok_szama * sizeof(Osszetevo));
    if (e->egyedi_osszetevok == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        free(e->egyedi_osszetevok);
        fclose(f);
        free(e);
        return NULL;
    }
    for (int i = 0; i < e->egyedi_osszetevok_szama; i++) {
        e->egyedi_osszetevok[i].nev[51] = 0;
        e->egyedi_osszetevok[i].tipus[51] = 0;
        fscanf(f, " %[^,], %[^\n]", e->egyedi_osszetevok[i].nev, e->egyedi_osszetevok[i].tipus);
    }

    fclose(f);
    return e;
}





/*
void osszetevo_fileba_ment(Receptkonyv* r) {
    if (r == NULL || r->etelek == NULL) {
        printf("Hibás vagy üres receptkönyv!\n");
        return;
    }

    FILE* f = fopen("osszetevok.txt", "w");
    if (f == NULL) {
        printf("Nem lehetett megnyitni a file-t!\n");
        return;
    }

    int max_osszetevok = 100;  // Assume a safe upper limit on unique ingredients
    char** egyedi_osszetevo = (char**)malloc(max_osszetevok * sizeof(char*));
    if (egyedi_osszetevo == NULL) {
        printf("Nem sikerült lefoglalni a memóriát az összetevők listájához!\n");
        fclose(f);
        return;
    }

    int darabszam = 0;

    for (int i = 0; i < r->etelek_szama; i++) {
        Etel* etel = &(r->etelek[i]);
        for (int j = 0; j < etel->osszetevok_szama; j++) {
            Osszetevo* osszetevo = &(etel->osszetevok[j]);

            if (!osszetevo_letezik(egyedi_osszetevo, darabszam, osszetevo->nev)) {
                fprintf(f, "%s,%s\n", osszetevo->nev, osszetevo->tipus);

                if (darabszam >= max_osszetevok) {
                    max_osszetevok *= 2;
                    char** temp = (char**)realloc(egyedi_osszetevo, max_osszetevok * sizeof(char*));
                    if (temp == NULL) {
                        printf("Nem sikerült kibővíteni az egyedi összetevők listáját!\n");
                        for (int k = 0; k < darabszam; k++) {
                            free(egyedi_osszetevo[k]);
                        }
                        free(egyedi_osszetevo);
                        fclose(f);
                        return;
                    }
                    egyedi_osszetevo = temp;
                }

                egyedi_osszetevo[darabszam] = (char*)malloc((strlen(osszetevo->nev) + 1) * sizeof(char));
                if (egyedi_osszetevo[darabszam] == NULL) {
                    printf("Nem sikerült lefoglalni a memóriát az összetevő nevéhez!\n");
                    for (int k = 0; k < darabszam; k++) {
                        free(egyedi_osszetevo[k]);
                    }
                    free(egyedi_osszetevo);
                    fclose(f);
                    return;
                }

                strcpy(egyedi_osszetevo[darabszam], osszetevo->nev);
                darabszam++;
            }
        }
    }

    for (int i = 0; i < darabszam; i++) {
        free(egyedi_osszetevo[i]);
    }
    free(egyedi_osszetevo);
    fclose(f);
}*/


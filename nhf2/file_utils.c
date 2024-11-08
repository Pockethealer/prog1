#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <locale.h>
#include <wchar.h>
#include <windows.h>
#include <locale.h>
#include <fcntl.h>
#include <io.h>
#endif
#include "debugmalloc.h"
/*Ebben a modulban kaptak helyet a filokból beolvasó illetve azokba kiíró fv-k,
*illetve az általánosan használt stdin/stdout olvasó író fv-ek */

/*Az általános adatstruktúráim, a kettős indirekció ott van benne,
* hogy egy ételnek bárhány összetevője lehet illetve bárhány étel lehet a receptkönyvben.*/

/*Összetevők struckt tartalmazza az összetevő nevét (max 50 karakter),
*típusát(max 50 karakter), és mennyiségét(double)*/
typedef struct Osszetevo
{
    char nev[51];
    char tipus[51];
    double mennyiseg;
} Osszetevo;
/*Étel struktúra tartalmazza az étel nevét(max 50 karakter) az összetevőinek számát,
*az összetevők tömbjének pointerét, és az elkészítési útmutatót(max 1000 karakter) */
typedef struct Etel
{
    char nev[51];
    int osszetevok_szama;
    Osszetevo* osszetevok;
    char elkeszites[1001];
} Etel;
/*receptkönyv struktúra tartalmazza a benne levő ételek számát és az ételek tömbjére egy mutatót*/
typedef struct Receptkonyv
{
    int etelek_szama;
    Etel* etelek;
} Receptkonyv;
/*Egyedi összetevőket tartalmazó lista minden összetevő egyszer
*kell hogy szerepeljen benne tartalmazza az összetevők számát és az összetevők tömbjére mutató pointert.
*A benne levő összetevők rendszerint nem tartalmaznak mennyiségeket csak a nevet és típust*/
typedef struct Egyedi_osszetevok
{
    Osszetevo* egyedi_osszetevok;
    int egyedi_osszetevok_szama;
} Egyedi_osszetevok;


Receptkonyv* receptek_beolvas(void);
void receptet_fileba_ment(Receptkonyv* r);
void receptkonyv_felszabadit(Receptkonyv* r);
int recept_letezik(Receptkonyv* r, const char* etel_neve);
void recept_kiir(Etel* m);

Egyedi_osszetevok* osszetevo_beolvas(void);
void osszetevo_fileba_ment(Egyedi_osszetevok* e, Receptkonyv* r);
void egyedi_osszetevo_felszabadit(Egyedi_osszetevok* e);
int osszetevo_letezik(Egyedi_osszetevok* e, const char* osszetevo_neve);

Osszetevo o_beolvas1(void);
Osszetevo o_beolvas2(void);
Osszetevo o_beolvas3(void);
Etel i_beolvas(void);

/*Kap egy receptek structot és egy stringet és megnézi hogy a string egyezik e valamely r.etelek.nev stringgel
*elvileg case független, de mivel utf karakterek ezért néha bugos, az esetek 99%ában működik.
*Ezután visszatér a keresett elem tömbbeli indexével plusz 1(i+1-el), vagy nullával ha nem található
(azért kell az i+1 hogy a 0. elemet is helyesen kezelje).*/
int recept_letezik(Receptkonyv* r, const char* etel_neve) {
    if (r == NULL)
    {
        printf("A receptkönyv üres!");
        return 0;
    }

    for (int i = 0; i < r->etelek_szama; i++)
    {
        if (strcasecmp(r->etelek[i].nev, etel_neve) == 0)
        {
            return i + 1;
        }
    }
    return 0;
}
/*elmenti a kapott r struktúrát az előre megadott formátumban a receptek.txt fileba, ha nem létezik létrehozza a program gyökérkönyvtárába*/
void receptet_fileba_ment(Receptkonyv* r)
{
    if (r == NULL)
    {
        printf("Nincs adat a receptkonyvben!\n");
        return;
    }

    FILE* f = fopen("receptek.txt", "w");
    if (f == NULL)
    {
        printf("Nem lehet megnyitni a fájlt írásra.\n");
        return;
    }
    fprintf(f, "%d\n", r->etelek_szama);

    for (int i = 0; i < r->etelek_szama; i++)
    {
        Etel* etel = &r->etelek[i];

        fprintf(f, "%s,%d\n", etel->nev, etel->osszetevok_szama);

        for (int j = 0; j < etel->osszetevok_szama; j++)
        {
            Osszetevo* osszetevo = &etel->osszetevok[j];
            fprintf(f, "%s,%s,%.2lf\n", osszetevo->nev, osszetevo->tipus, osszetevo->mennyiseg);
        }
        fprintf(f, "%s\n", etel->elkeszites);
    }
    fclose(f);
}
/*beolvassa a recepteket az előre megadott receptek.txt fileból az r receptkönyv struktúrába
(lehetett volna argumentum a filenév de felesleges)*/
Receptkonyv* receptek_beolvas(void)
{
    Receptkonyv* r = (Receptkonyv*)malloc(sizeof(Receptkonyv));
    if (r == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        return NULL;
    }
    FILE* f = fopen("receptek.txt", "r");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni a receptek file-t!\n");
        free(r);
        return NULL;
    }
    if (fscanf(f, "%d", &(r->etelek_szama)) != 1 || r->etelek_szama <= 0)
    {
        printf("Hibás a receptek.txt file tartalma, az első sorba az ételek száma kell hogy kerüljön.\n");
        free(r);
        fclose(f);
        return NULL;
    }
    r->etelek = (Etel*)malloc((r->etelek_szama) * sizeof(Etel));
    if (r->etelek == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        free(r);
        fclose(f);
        return NULL;
    }
    for (int i = 0; i < r->etelek_szama; i++)
    {
        if (fscanf(f, " %[^,],%d", r->etelek[i].nev, &(r->etelek[i].osszetevok_szama)) != 2)
        {
            printf("Hibás a receptek.txt file tartalma, nem sikerült az összes receptet beolvasni, csak %d db-ot!", i + 1);

            r->etelek_szama = i;
            r->etelek = (Etel*)realloc(r->etelek, r->etelek_szama * sizeof(Etel));

            fclose(f);
            return r;
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
            if (fscanf(f, " %[^,], %[^,],%lf",
                r->etelek[i].osszetevok[j].nev,
                r->etelek[i].osszetevok[j].tipus,
                &r->etelek[i].osszetevok[j].mennyiseg) != 3)
            {
                r->etelek[i].osszetevok_szama = j;
                r->etelek[i].osszetevok = (Osszetevo*)realloc(r->etelek[i].osszetevok, r->etelek->osszetevok_szama * sizeof(Osszetevo));

            }
        }
        fscanf(f, " %[^\n]", r->etelek[i].elkeszites);
    }
    fclose(f);
    return r;
}
/*felszabadítja a kapott r struktúrát és minden alstruktúráját*/
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
/*kiirja az adott etel struktura adatait(név összetevők elkészítés)*/
void recept_kiir(Etel* m) {
    if (m == NULL)
    {
        printf("Null pointert adott meg az étel kiíráshoz!\n");
        return;
    }
    printf("Az étel neve: %s\n", m->nev);
    printf("Az étel összetevőinek száma: %d\n", m->osszetevok_szama);
    for (int i = 0;i < m->osszetevok_szama;i++) {
        printf("Az %d. összetevő: %s, mennyisége: %.3lf(%s).\n", i + 1, m->osszetevok[i].nev, m->osszetevok[i].mennyiseg, m->osszetevok[i].tipus);
    }
    printf("Az Étel elkészítése:\n%s", m->elkeszites);
    return;
}

/*Kap egy egyedi osszetevok structot és egy stringet és megnézi hogy a string egyezik-e valamely r.osszetevok.nev stringgel
*elvileg case független, de mivel utf karakterek ezért néha bugos, az esetek 99%ában működik.
*Ezután visszatér a keresett elem tömbbeli poziciójával, vagy nullával ha nem található.*/
int osszetevo_letezik(Egyedi_osszetevok* e, const char* osszetevo_neve)
{
    if (e == NULL)
    {
        printf("Az összetevők listája üres!");
        return 0;
    }
    /*Megnézi hogy az adott összetevő létezik-e, és visszatér az elem sorszámával, vigyázat egyel nagyobb mint az index*/
    for (int i = 0; i < e->egyedi_osszetevok_szama; i++)
    {
        if (strcasecmp(e->egyedi_osszetevok[i].nev, osszetevo_neve) == 0)
        {
            return i + 1;
        }
    }
    return 0;
}
/*felszabadítja a kapott e struktúrát és minden alstruktúráját*/
void egyedi_osszetevo_felszabadit(Egyedi_osszetevok* e)
{
    {
        if (e == NULL)
        {
            printf("Üres az összetevők tartalma, nem lehet mit felszabadítani!");
            return;
        }
        free(e->egyedi_osszetevok);
        free(e);
    }
}
/*beolvassa az összetevőket az előre megadott osszetevok.txt fileból az e egyedi összetevők tömbbe*/
Egyedi_osszetevok* osszetevo_beolvas(void)
{
    Egyedi_osszetevok* e = (Egyedi_osszetevok*)malloc(sizeof(Egyedi_osszetevok));
    if (e == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        return NULL;
    }
    FILE* f;
    f = fopen("osszetevok.txt", "r");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni az összetevők file-t!\n");
        free(e);
        return NULL;
    }
    fscanf(f, " %d", &(e->egyedi_osszetevok_szama));
    e->egyedi_osszetevok = (Osszetevo*)malloc(e->egyedi_osszetevok_szama * sizeof(Osszetevo));
    if (e->egyedi_osszetevok == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        fclose(f);
        free(e);
        return NULL;
    }
    for (int i = 0; i < e->egyedi_osszetevok_szama; i++)
    {
        e->egyedi_osszetevok[i].nev[51] = 0;
        e->egyedi_osszetevok[i].tipus[51] = 0;
        if (fscanf(f, " %[^,], %[^\n]", e->egyedi_osszetevok[i].nev, e->egyedi_osszetevok[i].tipus) != 2)
        {
            e->egyedi_osszetevok_szama = i;
            e->egyedi_osszetevok = (Osszetevo*)realloc(e->egyedi_osszetevok, e->egyedi_osszetevok_szama * sizeof(Osszetevo));
        }
    }

    fclose(f);
    return e;
}
/*osszefésüli az e struktúrában található összetevőket a receptkönyv struktúra ételeinek az összetevőivel,
*hogy az egyedi összetevő struktúra pontosan egyszer tartalmazzon minden összetevőt, majd elmenti azt
*az előre megadott formátumban az osszetevok.txt fileba, ha nem létezik létrehozza a program gyökérkönyvtárába.*/
void osszetevo_fileba_ment(Egyedi_osszetevok* e, Receptkonyv* r)
{
    if (e == NULL)
    {
        printf("Üres az összetevők listája!\n");
        return;
    }
    FILE* f = fopen("osszetevok.txt", "w");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni a file-t!\n");
        return;
    }
    if (r != NULL) {
        for (int i = 0; i < r->etelek_szama; i++)
        {
            Etel* etel = &(r->etelek[i]);
            for (int j = 0; j < etel->osszetevok_szama; j++)
            {
                Osszetevo* osszetevo = &(etel->osszetevok[j]);
                if (!osszetevo_letezik(e, osszetevo->nev))
                {
                    e->egyedi_osszetevok_szama++;
                    e->egyedi_osszetevok = realloc(e->egyedi_osszetevok, e->egyedi_osszetevok_szama * sizeof(Osszetevo));
                    if (e->egyedi_osszetevok == NULL)
                    {
                        printf("Nem sikerült a memória bővítése az összetevőknek!\n");
                        fclose(f);
                        return;
                    }
                    strcpy(e->egyedi_osszetevok[e->egyedi_osszetevok_szama - 1].nev, osszetevo->nev);
                    strcpy(e->egyedi_osszetevok[e->egyedi_osszetevok_szama - 1].tipus, osszetevo->tipus);
                }
            }
        }
    }
    /*kiírjuk a fileba az összetevők számát*/
    fprintf(f, "%d\n", e->egyedi_osszetevok_szama);
    /*fileba írjuk a már létező öszetevőket*/
    for (int i = 0; i < e->egyedi_osszetevok_szama; i++)
    {
        fprintf(f, "%s,%s\n", e->egyedi_osszetevok[i].nev, e->egyedi_osszetevok[i].tipus);
    }
    fclose(f);
}

/*windows-os bohóckodás utf-8-as beolvasáshoz, elvileg működik,
*3 különböző verziójú windowson néztem, mingw32 compilerrel. Nem teljesen megbízható, de az idő 99%ában működik
azert struktúrát adnak vissza mert így egyszerűbb volt fix hosszúságú stringet visszaadni*/
#ifdef _WIN32
/*beolvassa egy összetevőnek a nevét(max 50 karakter), és visszaadja osszetevok struktúrában*/
Osszetevo o_beolvas1(void) {
    Osszetevo o;
    wchar_t wstr1[51] = { 0 };

    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    /*wchar_t line[51];
    _getws_s(line, 51);
    swscanf(line, L" %51[^\n]", wstr1);*/

    wscanf(L" %50l[^\n]", wstr1);

    //wprintf(L"A beolvasott karakter: %ls, %ls, %lf\n", wstr1, wstr2, d);

    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stdin), _O_TEXT);

    char utf8_str1[51] = { 0 };
    WideCharToMultiByte(CP_UTF8, 0, wstr1, -1, utf8_str1, sizeof(utf8_str1), NULL, NULL);


    printf("az utf karakter: %s\n", utf8_str1);
    strcpy(o.nev, utf8_str1);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return o;

}
/*beolvassa egy összetevőnek a nevét(max 50 karakter) és típusát(max 50 karakter) és visszaadja egy osszetevők struktúrában*/
Osszetevo o_beolvas2(void) {
    Osszetevo o;
    wchar_t wstr1[51] = { 0 }, wstr2[51] = { 0 };


    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    /*wchar_t line[102];
    _getws_s(line, 102);
    swscanf(line, L" %50[^,], %50[^\n]", wstr1, wstr2);*/
    wscanf(L" %50l[^,], %50l[^\n]", wstr1, wstr2);


    //wprintf(L"A beolvasott karakter: %ls, %ls, %lf\n", wstr1, wstr2, d);

    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stdin), _O_TEXT);

    char utf8_str1[51] = { 0 }, utf8_str2[51] = { 0 };
    WideCharToMultiByte(CP_UTF8, 0, wstr1, -1, utf8_str1, sizeof(utf8_str1), NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, wstr2, -1, utf8_str2, sizeof(utf8_str2), NULL, NULL);

    printf("az utf karakter: %s, %s\n", utf8_str1, utf8_str2);
    strcpy(o.nev, utf8_str1);
    strcpy(o.tipus, utf8_str2);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return o;

}
/*Beolvassa egy összetevőnek a nevét(max 50 karakter) típusát(max 50 karakter) és mennyiségét és visszaadja egy összetevők struktúrában*/
Osszetevo o_beolvas3(void) {
    Osszetevo o;
    wchar_t wstr1[51] = { 0 }, wstr2[51] = { 0 };
    double d;

    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    wscanf(L" %50l[^,], %50l[^,], %lf", wstr1, wstr2, &d);

    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stdin), _O_TEXT);

    char utf8_str1[51] = { 0 }, utf8_str2[51] = { 0 };
    WideCharToMultiByte(CP_UTF8, 0, wstr1, -1, utf8_str1, sizeof(utf8_str1), NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, wstr2, -1, utf8_str2, sizeof(utf8_str2), NULL, NULL);

    printf("az utf karakter: %s, %s, %lf\n", utf8_str1, utf8_str2, d);
    strcpy(o.nev, utf8_str1);
    strcpy(o.tipus, utf8_str2);
    o.mennyiseg = d;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return o;

}

Etel i_beolvas(void) {
    Etel o;
    wchar_t wstr1[1001] = { 0 };

    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    /*wchar_t line[51];
    _getws_s(line, 51);
    swscanf(line, L" %51[^\n]", wstr1);*/

    wscanf(L" %1000l[^\n]", wstr1);

    //wprintf(L"A beolvasott karakter: %ls, %ls, %lf\n", wstr1, wstr2, d);

    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stdin), _O_TEXT);

    char utf8_str1[1001] = { 0 };
    WideCharToMultiByte(CP_UTF8, 0, wstr1, -1, utf8_str1, sizeof(utf8_str1), NULL, NULL);


    printf("az utf karakter: %s\n", utf8_str1);
    strcpy(o.elkeszites, utf8_str1);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return o;

}
#endif
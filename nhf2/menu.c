#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include "beolvas.h"
#include <locale.h>
#endif
#include "file_utils.h"
#include "debugmalloc.h"

void osszetevok_almenu(Egyedi_osszetevok *e);
int main_menu(void);
int kilepes(Egyedi_osszetevok *e, Receptkonyv *r);
void menu_kiir(void);
void osszetevo_felvesz(Egyedi_osszetevok *e);
void osszetevo_kiir(Egyedi_osszetevok *e);
void osszetevok_keres(Egyedi_osszetevok *e);
void osszetevo_torol(Egyedi_osszetevok *e);

void menu_kiir(void)
{
    printf("Add meg a választott opciót (1-6): \n");
    printf("1.Összetevők kezelése\n");
    printf("2.Receptek kezelése\n");
    printf("3.Qol funkciók\n");
    printf("4.Bevásárló lista kezelése\n");
    printf("5.Kedvencek kezelése\n");
    printf("6.Kilépni\n");
    return;
}
int kilepes(Egyedi_osszetevok *e, Receptkonyv *r)
{
    receptet_fileba_ment(r);
    osszetevo_fileba_ment(e, r);
    egyedi_osszetevo_felszabadit(e);
    receptkonyv_felszabadit(r);
    return 0;
}
int main_menu(void)
{
    /*locale beállítása windowson*/
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "hu_HU.UTF-8");
#endif
    /*struktúrák inicializálása*/
    Egyedi_osszetevok *osszetevo = osszetevo_beolvas();
    if (osszetevo == NULL)
    {
        printf("nem sikerült az összetevők beolvasása!, kilépés");
        return -1;
    }
    Receptkonyv *konyv = receptek_beolvas();
    if (konyv == NULL)
    {
        printf("nem sikerült az összetevők beolvasása!, kilépés");
        kilepes(osszetevo, NULL);
        return -1;
    }
    /*történések*/
    int vege = 0;
    int opcio = 0;
    do
    {
        menu_kiir();
        int sikeres = scanf("%d", &opcio);

        while (sikeres != 1 || opcio < 1 || opcio > 6)
        {
            printf("Hibás bevitel. Csak számot adj meg 1 és 6 között.\n");

            while (getchar() != '\n')
            {
            };

            printf("Add meg a választott opciót (1-6): ");
            sikeres = scanf("%d", &opcio);
        }

        switch (opcio)
        {
        case 1:
            system("@cls||clear");
            printf("Összetevők kezelése\n");
            osszetevok_almenu(osszetevo);
            break;
        case 2:
            system("clear");
            printf("Receptek kezelése\n");
            break;
        case 3:
            system("@cls||clear");
            printf("Qol funkciók\n");
            break;
        case 4:
            system("@cls||clear");
            printf("Bevásárló lista kezelése\n");
            break;
        case 5:
            system("@cls||clear");
            printf("Kedvencek kezelése\n");
            break;
        case 6:
            system("@cls||clear");
            printf("Kilépés\n");
            vege = 1;
            break;

        default:
            system("@cls||clear");
            printf("Ervenytelen parnacs\n");
            break;
        }
    } while (!vege);
    /*debug
    printf("%s\n%s\n%d\n", konyv->etelek[1].osszetevok[2].tipus, konyv->etelek[1].osszetevok[2].nev, strlen(konyv->etelek[1].osszetevok[2].nev));*/
    /*program bezárása*/
    kilepes(osszetevo, konyv);
    return 0;
}

void osszetevok_almenu(Egyedi_osszetevok *e)
{

    int vege = 0;
    int opcio = 0;
    do
    {
        printf("Mit szeretnél csinálni? A megfelelő számot írd be!\n\n");
        printf("1.Új összetevőt felvenni\n");
        printf("2.Összetevőt törölni\n");
        printf("3.Az összetevőket kilistázni\n");
        printf("4.Összetevőt keresni\n");
        printf("5.Kilépni a főmenübe\n");
        int sikeres = scanf("%d", &opcio);

        while (sikeres != 1 || opcio < 1 || opcio > 5)
        {
            printf("Hibás bevitel. Csak számot adj meg 1 és 5 között.\n");

            while (getchar() != '\n')
            {
            };

            printf("Add meg a választott opciót (1-6): ");
            sikeres = scanf("%d", &opcio);
        }
        switch (opcio)
        {
        case 1:
            printf("Összetevők felvétele\n");
            osszetevo_felvesz(e);
            break;
        case 2:
            printf("Összetevőt törölése\n");
            osszetevo_torol(e);
            break;
        case 3:
            printf("3.Az összetevőket kilistázása\n");
            osszetevo_kiir(e);
            break;
        case 4:
            printf("Összetevőt keresése\n");
            osszetevok_keres(e);
            break;
        case 5:
            printf("Kilépés\n");
            vege = 1;
            break;

        default:
            printf("Ervenytelen parnacs\n");
            break;
        }
    } while (!vege);
    return;
}

void osszetevo_felvesz(Egyedi_osszetevok *e)
{
    /*ékezetes karaktert lehet csak teljesen máshogy windowson és unixon*/
    printf("Írd be az összetevő nevét, és mértékegységét, vesszővel elválasztva!\n");

#ifdef _WIN32
    Osszetevo a = o_beolvas2();
#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf(" %[^,],%[^\n]", a.nev, a.tipus) != 2)
    {
        printf("Hibás név, nem sikerült az összetevőt felvenni!\n");
        return;
    };
#endif

    if (!osszetevo_letezik(e, a.nev))
    {
        e->egyedi_osszetevok_szama++;
        Osszetevo *temp = realloc(e->egyedi_osszetevok, e->egyedi_osszetevok_szama * sizeof(Osszetevo));
        if (temp == NULL)
        {
            printf("Nem sikerült a memória bővítése az összetevőknek!\n");
            e->egyedi_osszetevok_szama--;
            return;
        }
        e->egyedi_osszetevok = temp;
        strcpy(e->egyedi_osszetevok[e->egyedi_osszetevok_szama - 1].nev, a.nev);
        strcpy(e->egyedi_osszetevok[e->egyedi_osszetevok_szama - 1].tipus, a.tipus);
        printf("Az összetevőt sikeresen hozzáadtad!\n");
    }
    else
    {
        printf("A beírt összetevő már létezik\n");
    }

    return;
}
void osszetevo_kiir(Egyedi_osszetevok *e)
{
    for (int i = 0; i < e->egyedi_osszetevok_szama; i++)
    {
        printf("%d. Összetevő: %s, mértékegysége: %s.\n", i + 1, e->egyedi_osszetevok[i].nev, e->egyedi_osszetevok[i].tipus);
    }
    return;
}
void osszetevok_keres(Egyedi_osszetevok *e)
{
    printf("Írd be a keresett összetevő nevét!\n");
#ifdef _WIN32
    Osszetevo a = o_beolvas1();

#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf(" %[^\n],", a.nev) <= 0)
    {
        printf("Hibás név, nem sikerült az összetevőt felvenni!\n");
        return;
    };

#endif
    int i = osszetevo_letezik(e, a.nev) - 1;
    if (i >= 0)
    {
        printf("A keresett összetevő(%s) a %d. helyen van a listában, mértékegysége: %s\n", a.nev, i + 1, e->egyedi_osszetevok[i].tipus);
    }
    else
        printf("A keresett összetevő nem található!\n");
    return;
}
void osszetevo_torol(Egyedi_osszetevok *e)
{
    /*ékezetes karaktert lehet csak teljesen máshogy windowson és unixon*/
    printf("Írd be a törlendő összetevő nevét!\n");
#ifdef _WIN32
    Osszetevo a = o_beolvas1();

#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf(" %[^\n]", a.nev) <= 0)
    {
        printf("Hibás név, nem sikerült az összetevőt felvenni!\n");
        return;
    };

#endif
    int j = osszetevo_letezik(e, a.nev) - 1;
    if (j >= 0)
    {
        Osszetevo *temp = malloc((e->egyedi_osszetevok_szama - 1) * sizeof(Osszetevo));
        if (temp == NULL)
        {
            printf("Nem sikerült a memória foglalás az összetevő törléséhez!\n");
            return;
        }
        int poz = 0;
        for (int i = 0; i < e->egyedi_osszetevok_szama; i++)
        {
            if (i != j)
            {
                temp[poz] = e->egyedi_osszetevok[i];
                poz++;
            }
        }
        free(e->egyedi_osszetevok);
        e->egyedi_osszetevok = temp;
        e->egyedi_osszetevok_szama--;
        printf("Az összetevőt sikeresen törölted!\n");
    }
    else
    {
        printf("A keresett összetevő nem található!\n");
    }

    return;
}
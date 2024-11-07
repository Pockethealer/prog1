#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "file_utils.h"
#include "debugmalloc.h"

void receptek_almenu(Receptkonyv** r);
void recept_felvesz(Receptkonyv** r);
void recept_keres(Receptkonyv* r);
void recept_torol(Receptkonyv* r);

void receptek_almenu(Receptkonyv** r)
{
    int vege = 0;
    int opcio = 0;
    do
    {
        printf("Mit szeretnél csinálni? A megfelelő számot írd be!\n\n");
        printf("1.Új receptet felvenni\n");
        printf("2.Receptet törölni\n");
        printf("3.Receptet keresni\n");
        printf("4.Kilépni a főmenübe\n");

        int sikeres = scanf("%d", &opcio);

        while (sikeres != 1 || opcio < 1 || opcio > 4)
        {
            printf("Hibás bevitel. Csak számot adj meg 1 és 4 között.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Add meg a választott opciót (1-4): ");
            sikeres = scanf("%d", &opcio);
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        switch (opcio)
        {
        case 1:
            system("@cls||clear");
            printf("Új receptet felvenni\n");
            //recept_felvesz(r);
            while ((c = getchar()) != '\n' && c != EOF) {}
            system("@cls||clear");
            break;
        case 2:
            system("@cls||clear");
            printf("2.Receptet törölni\n");
            //recept_torol(*r);
            while ((c = getchar()) != '\n' && c != EOF) {}
            system("@cls||clear");
            break;
        case 3:
            system("@cls||clear");
            printf("3.Receptet keresni\n");
            recept_keres(*r);
            while ((c = getchar()) != '\n' && c != EOF) {}
            system("@cls||clear");
            break;
        case 4:
            system("@cls||clear");
            printf("Kilépés\n");
            vege = 1;
            break;

        default:
            printf("Érvénytelen parnacs\n");
            break;
        }
    } while (!vege);
    return;
}
/*void recept_felvesz(Receptkonyv** r)
{

    if (*e == NULL)
    {
        printf("Nincs recept a listában!\n");
        *e = (Egyedi_osszetevok*)malloc(sizeof(Egyedi_osszetevok));
        if (*e == NULL)
        {
            printf("Nem lehetett lefoglalni a memoriat az összetevőknek!\n");
            return;
        }
        (*e)->egyedi_osszetevok_szama = 0;
        (*e)->egyedi_osszetevok = NULL;
    }
    printf("Írd be az összetevő nevét, és mértékegységét, vesszővel elválasztva!\n");
#ifdef _WIN32
    Osszetevo a = o_beolvas2();
#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf("%[^,],%[^\n]", a.nev, a.tipus) != 2) {
        printf("Hibás név, nem sikerült az összetevőt felvenni!\n");
        return;
    };
#endif

    if (!osszetevo_letezik(*e, a.nev))
    {
        (*e)->egyedi_osszetevok_szama++;
        Osszetevo* temp = realloc((*e)->egyedi_osszetevok, (*e)->egyedi_osszetevok_szama * sizeof(Osszetevo));
        if (temp == NULL)
        {
            printf("Nem sikerült a memória bővítése az összetevőknek!\n");
            free((*e)->egyedi_osszetevok);
            (*e)->egyedi_osszetevok = NULL;
            return;
        }
        (*e)->egyedi_osszetevok = temp;
        strcpy((*e)->egyedi_osszetevok[(*e)->egyedi_osszetevok_szama - 1].nev, a.nev);
        strcpy((*e)->egyedi_osszetevok[(*e)->egyedi_osszetevok_szama - 1].tipus, a.tipus);
        printf("Az összetevőt sikeresen hozzáadtad! Nyomj egy entert a továbblépéshez!\n");
    }
    else
    {
        printf("A beírt összetevő már létezik\n");
    }

    return;
}*/
void recept_keres(Receptkonyv* r) {
    if (r == NULL)
    {
        printf("Nincs recept a listában! Nyomj egy entert a továbblépéshez!\n");
        return;
    }
    printf("Írd be a keresett étel nevét!\n");
#ifdef _WIN32
    /*Lehetne saját függvényt írni rá, de felesleges*/
    Osszetevo a = o_beolvas1();

#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf("%[^,],", a.nev) <= 0) {
        printf("Hibás név, nem sikerült az összetevőt felvenni!\n");
        return;
    };

#endif
    int i = recept_letezik(r, a.nev) - 1;
    if (i >= 0) {
        recept_kiir(&(r->etelek[i]));
    }
    else printf("A keresett összetevő nem található!\n");
    return;
}
/*void recept_torol(Receptkonyv* r)
{
    if (e == NULL)
    {
        printf("Nincs recept a listában! Nyomj egy entert a továbblépéshez!\n");
        return;
    }
    printf("Írd be a törlendő összetevő nevét!\n");
#ifdef _WIN32
    Osszetevo a = o_beolvas1();

#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf("%[^,]", a.nev) <= 0) {
        printf("Hibás név, nem sikerült az összetevőt felvenni!\n");
        return;
    };

#endif
    int j = osszetevo_letezik(e, a.nev) - 1;
    if (j >= 0)
    {
        Osszetevo* temp = malloc((e->egyedi_osszetevok_szama - 1) * sizeof(Osszetevo));
        if (temp == NULL)
        {
            printf("Nem sikerült a memória foglalás az összetevő törléséhez!\n");
            return;
        }
        int poz = 0;
        for (int i = 0;i < e->egyedi_osszetevok_szama;i++) {
            if (i != j)
            {
                temp[poz] = e->egyedi_osszetevok[i];
                poz++;
            }

        }
        free(e->egyedi_osszetevok);
        e->egyedi_osszetevok = temp;
        e->egyedi_osszetevok_szama--;
        printf("Az összetevőt sikeresen törölted!Nyomj egy entert a továbblépéshez!\n");
    }
    else
    {
        printf("A keresett összetevő nem található!\n");
    }

    return;
}*/


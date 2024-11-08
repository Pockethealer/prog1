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
void recept_listaz(Receptkonyv* r);

void receptek_almenu(Receptkonyv** r)
{
    if (*r == NULL) {
        printf("Nincs recept a receptkönyben!");
    }
    int vege = 0;
    int opcio = 0;
    do
    {
        printf("Mit szeretnél csinálni? A megfelelő számot írd be!\n\n");
        printf("1.Új receptet felvenni\n");
        printf("2.Receptet törölni\n");
        printf("3.Ételek listázása\n");
        printf("4.Receptet keresni\n");
        printf("5.Kilépni a főmenübe\n");

        int sikeres = scanf("%d", &opcio);

        while (sikeres != 1 || opcio < 1 || opcio > 5)
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
            recept_felvesz(r);
            while ((c = getchar()) != '\n' && c != EOF) {}
            system("@cls||clear");
            break;
        case 2:
            system("@cls||clear");
            printf("2.Receptet törölni\n");
            recept_torol(*r);
            while ((c = getchar()) != '\n' && c != EOF) {}
            system("@cls||clear");
            break;
        case 3:
            system("@cls||clear");
            printf("3.Ételek listázása\n");
            recept_listaz(*r);
            while ((c = getchar()) != '\n' && c != EOF) {}
            system("@cls||clear");
            break;
        case 4:
            system("@cls||clear");
            printf("4.Receptet keresni\n");
            recept_keres(*r);
            while ((c = getchar()) != '\n' && c != EOF) {}
            system("@cls||clear");
            break;
        case 5:
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
void recept_felvesz(Receptkonyv** r)
{

    if (*r == NULL)
    {
        printf("Nincs recept a listában!\n");
        *r = (Receptkonyv*)malloc(sizeof(Receptkonyv));
        if (*r == NULL)
        {
            printf("Nem lehetett lefoglalni a memoriat az recepteknek!\n");
            return;
        }
        (*r)->etelek_szama = 0;
        (*r)->etelek = NULL;
    }
    printf("Írd be az étel nevét!\n");
#ifdef _WIN32
    /*igen hülyén néz ki hogy osszetevők struktúrába olvasom be az étel nevét de nem akartam egy külön fv-t írni csak erre*/
    Osszetevo nev = o_beolvas1();
    if (recept_letezik(*r, nev.nev))
    {
        printf("Már létezik recept ezzel a névvel!\n");
        return;
    }

    int osszetevok_szama;
    printf("Nem létezik ezen a néven recept, a hozzáadáshoz nyomj egy entert!");//utf-8-kezelés miatt kell
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    printf("Írd be hány összetevője lesz!\n");

    if (scanf("%d", &osszetevok_szama) != 1)
    {
        printf("Rossz formátumú megadás, nem sikerült hozzáadni!\n");
        return;
    }
    printf("Sikeresen beolvastad az összetevők darabszámát: %d. Nyomj egy entert a folytatáshoz!\n", osszetevok_szama);
    while ((c = getchar()) != '\n' && c != EOF) {}
    Osszetevo* osszetevok = (Osszetevo*)malloc(osszetevok_szama * sizeof(Osszetevo));
    if (osszetevok == NULL)
    {
        printf("Nem sikerült lefoglalni a memóriát az összetevőknek!\n");
        return;
    }
    for (int i = 0; i < osszetevok_szama;i++) {
        printf("Írd be a %d. összetevő nevét, mértékegységét, és mennyiségét, vesszővel elválasztva(törtszámnál tizedes pontot használj!)\n", i + 1);
        osszetevok[i] = o_beolvas3();
        printf("Összetevő siekresen beolvasva, nyomj egy entert a folytatáshoz!\n");
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
    printf("Írd be a recept elkészítéséhez az instrukciókat, egy sorba!\n");

    Etel etel = i_beolvas();
    printf("Sikeresen hozzáadtad a receptet, nyomj egy entert a folytatáshoz!\n");
#endif
#ifdef __linux__
    /*TODO*/
#endif

    (*r)->etelek_szama++;
    Etel* temp = realloc((*r)->etelek, (*r)->etelek_szama * sizeof(Etel));
    if (temp == NULL)
    {
        printf("Nem sikerült a memória bővítése a recepthez!\n");
        free(osszetevok);
        (*r)->etelek_szama--;
        return;
    }
    (*r)->etelek = temp;
    strcpy((*r)->etelek[(*r)->etelek_szama - 1].nev, nev.nev);
    (*r)->etelek[(*r)->etelek_szama - 1].osszetevok_szama = osszetevok_szama;
    strcpy((*r)->etelek[(*r)->etelek_szama - 1].elkeszites, etel.elkeszites);
    (*r)->etelek[(*r)->etelek_szama - 1].osszetevok = osszetevok;

    return;
}
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
void recept_listaz(Receptkonyv* r) {
    if (r == NULL) {
        printf("A receptkonyv üres!\n");
        return;
    }
    for (int i = 0; i < r->etelek_szama;i++) {
        printf("%d.: %s\n", i + 1, r->etelek[i].nev);
    }
    printf("Az ételek nevét sikeresen kilistáztad! Nyomj egy entert a továbblépéshez!\n");
    return;
}
void recept_torol(Receptkonyv* r)
{
    if (r == NULL)
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
    int j = recept_letezik(r, a.nev) - 1;
    if (j >= 0)
    {
        Etel* temp_r = (Etel*)malloc((r->etelek_szama - 1) * sizeof(Etel));
        if (temp_r == NULL)
        {
            printf("Nem sikerült a memória foglalás az összetevő törléséhez!\n");
            return;
        }
        int poz = 0;
        for (int i = 0;i < r->etelek_szama;i++) {
            if (i != j)
            {
                temp_r[poz] = r->etelek[i];
                poz++;

            }
            else {
                free(r->etelek[i].osszetevok);
            }
        }
        free(r->etelek);
        r->etelek = temp_r;
        r->etelek_szama--;
        printf("A receptet sikeresen törölted! Nyomj egy entert a továbblépéshez!\n");
    }
    else
    {
        printf("A keresett összetevő nem található!\n");
    }
    return;
}


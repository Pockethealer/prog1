/**
 * @file o_menu.c
 * @brief Az összetevők almenühöz tartozó fv-ek, egy külön modulba szétszedve.
 * @date 2024-11-08
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "file_utils.h"
#include "debugmalloc.h"

void osszetevok_almenu(Egyedi_osszetevok** e);
void osszetevo_felvesz(Egyedi_osszetevok** e);
void osszetevo_kiir(Egyedi_osszetevok* e);
void osszetevok_keres(Egyedi_osszetevok* e);
void osszetevo_torol(Egyedi_osszetevok* e);

/**
 * @brief Az összetevők almenü vezérlőegysége, azért kell **e-t kapnia hogy hozzáférjen az eredeti pointerhez ha azon akar módosítani
 * Tartalmaz egy összetevő felvétel, törlés, listázás, és keresés menüpontot.
 * @param e A korábban beolvasott összetevők listáját tartalmazó egyedi összetevők struct.
 */
void osszetevok_almenu(Egyedi_osszetevok** e)
{

    int vege = 0;
    int opcio = 0;
    do
    {
        printf("\nMit szeretnél csinálni? A megfelelő számot írd be!\n\n");
        printf("1.Új összetevőt felvenni\n");
        printf("2.Összetevőt törölni\n");
        printf("3.Az összetevőket kilistázni\n");
        printf("4.Összetevőt keresni\n");
        printf("5.Kilépni a főmenübe\n");

        int sikeres = scanf("%d", &opcio);

        while (sikeres != 1 || opcio < 1 || opcio > 5)
        {
            printf("Hibás bevitel. Csak számot adj meg 1 és 5 között.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("Add meg a választott opciót (1-5): ");
            sikeres = scanf("%d", &opcio);
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        switch (opcio)
        {
        case 1:
            system("@cls||clear");
            printf("Összetevők felvétele\n");
            osszetevo_felvesz(e);
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            break;
        case 2:
            system("@cls||clear");
            printf("Összetevőt törölése\n");
            osszetevo_torol(*e);
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            break;
        case 3:
            system("@cls||clear");
            printf("3.Az összetevőket kilistázása\n");
            osszetevo_kiir(*e);
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            break;
        case 4:
            system("@cls||clear");
            printf("Összetevőt keresése\n");
            osszetevok_keres(*e);
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
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
/**
 * @brief Megnézi hogy van e összetevő a listában, ha nincs akkor inicializálja a listát. Ezután beolvas egy nevet,
 * ha tartalmazza már a tömb akkor nem engedi újra felvenni egyébként hozzáadja a tömbhöz átméretezés után.
 * @param e Receptek listája
 */
void osszetevo_felvesz(Egyedi_osszetevok** e)
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
    if (scanf("%[^,],%[^\n]", a.nev, a.tipus) != 2)
    {
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
}
/**
 * @brief Kiírja az argumentumban kapot struct összetevő elemeinek a listáját.
 * @param e
 */
void osszetevo_kiir(Egyedi_osszetevok* e)
{
    if (e == NULL)
    {
        printf("Nincs recept a listában! Nyomj egy entert a továbblépéshez!\n");
        return;
    }

    for (int i = 0; i < e->egyedi_osszetevok_szama; i++)
    {
        printf("%d. Összetevő: %s, mértékegysége: %s.\n", i + 1, e->egyedi_osszetevok[i].nev, e->egyedi_osszetevok[i].tipus);
    }
    printf("Az összetevőt sikeresen kilistáztad! Nyomj egy entert a továbblépéshez!\n");
    return;
}
/**
 * @brief Keres az adott struktúrában a név alapján amit stdin-ről olvas be.
 * @param e
 */
void osszetevok_keres(Egyedi_osszetevok* e)
{
    if (e == NULL)
    {
        printf("Nincs recept a listában! Nyomj egy entert a továbblépéshez!\n");
        return;
    }
    printf("Írd be a keresett összetevő nevét!\n");
#ifdef _WIN32
    Osszetevo a = o_beolvas1();

#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf("%[^\n]", a.nev) <= 0)
    {
        printf("Hibás név, nem sikerült az összetevőt felvenni!\n");
        return;
    };

#endif
    int i = osszetevo_letezik(e, a.nev) - 1;
    if (i >= 0)
    {
        printf("A keresett összetevő(%s) a %d. helyen van a listában, mértékegysége: %s\nNyomj egy entert a továbblépéshez",
            a.nev, i + 1, e->egyedi_osszetevok[i].tipus);
    }
    else
        printf("A keresett összetevő nem található!\n");
    return;
}
/**
 * @brief Törli az adott összetevőt amit a nevével kell megadni, amennyiben létezik az e structban.
 * Készít egy ideiglenes struckt pointert, lefoglalja neki az új hoszzát, majd átmásolja az összes elemet kivéve a törlendőt, végül felszabadítja az eredetit.
 * @param e
 */
void osszetevo_torol(Egyedi_osszetevok* e)
{
    if (e == NULL)
    {
        printf("Nincs recept a listában! Nyomj egy entert a továbblépéshez!\n");
        return;
    }
    /*ékezetes karaktert lehet csak teljesen máshogy windowson és unixon*/
    printf("Írd be a törlendő összetevő nevét!\n");
#ifdef _WIN32
    Osszetevo a = o_beolvas1();

#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf("%[^\n]", a.nev) <= 0)
    {
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
        printf("Az összetevőt sikeresen törölted! Nyomj egy entert a továbblépéshez!\n");
    }
    else
    {
        printf("A keresett összetevő nem található!\n");
    }

    return;
}

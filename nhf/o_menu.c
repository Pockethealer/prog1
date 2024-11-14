/**
 * @file o_menu.c
 * @brief Az összetevők és receptek almenühöz tartozó fv-ek, egy külön modulba szétszedve.
 * @date 2024-11-08
 */

#include "o_menu.h"

 /**
  * @brief Kilistázza az összetevők menüopciókat, stdio-n.
  */
void o_menu_kiir(void)
{
    for (int i = 0;i < 80;i++) printf("=");
    printf(COLOR_BOLD"\n%*.s%s\n"COLOR_RESET, 32, " ", "ÖSZETEVŐK ALMENÜ");
    for (int i = 0;i < 80;i++) printf("=");
    printf("\n%*.s"COLOR_UNDERLINE"Mit szeretnél csinálni? A megfelelő számot írd be!"COLOR_RESET"\n\n", 15, " ");
    printf(COLOR_GREEN"1.    ➤ Új összetevőt felvenni\n");
    printf("2.    ➤ Összetevőt törölni\n");
    printf("3.    ➤ Az összetevőket kilistázni\n");
    printf("4.    ➤ Összetevőt keresni\n");
    printf(COLOR_BRIGHT_RED"5.    ➤ Kilépni a főmenübe\n"COLOR_RESET);
    return;
}

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
        int c;
        printf("Sikeresen beléptél az almenübe, nyomj egy entert a folytatáshoz!");
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        o_menu_kiir();
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
    if (scanf("%50[^,],%50[^\n]", a.nev, a.tipus) != 2)
    {
        printf("Hibás név, nem sikerült az összetevőt felvenni!\n");
        return;
    };
#endif

    if (!osszetevo_letezik(*e, a.nev))
    {
        (*e)->egyedi_osszetevok_szama++;
        //Azért temp-be hogy ha nem sikerül foglalni akkor az eredeti ne vesszen el
        Osszetevo* temp = realloc((*e)->egyedi_osszetevok, (*e)->egyedi_osszetevok_szama * sizeof(Osszetevo));
        if (temp == NULL)
        {
            printf("Nem sikerült a memória bővítése az összetevőknek!\n");
            (*e)->egyedi_osszetevok_szama--;
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
    if (scanf("%50[^\n]", a.nev) <= 0)
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
    printf("Írd be a törlendő összetevő nevét!\n");
#ifdef _WIN32
    Osszetevo a = o_beolvas1();

#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf("%50[^\n]", a.nev) <= 0)
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Innentől kezdődik a receptek almenü
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Kilistázza a receptek menüopciókat, stdio-n.
 */
void r_menu_kiir(void)
{
    for (int i = 0;i < 80;i++) printf("=");
    printf(COLOR_BOLD"\n%*.s%s\n"COLOR_RESET, 33, " ", "RECEPTEK ALMENÜ");
    for (int i = 0;i < 80;i++) printf("=");
    printf("\n%*.s"COLOR_UNDERLINE"Mit szeretnél csinálni? A megfelelő számot írd be!"COLOR_RESET"\n\n", 15, " ");
    printf(COLOR_GREEN"1.    ➤ Új receptet felvenni\n");
    printf("2.    ➤ Receptet törölni\n");
    printf("3.    ➤ Ételek listázása\n");
    printf("4.    ➤ Receptet keresni\n");
    printf(COLOR_BRIGHT_RED"5.    ➤ Kilépni a főmenübe\n"COLOR_RESET);
    return;
}
/**
 * @brief A receptek almenü vezérlőegysége, azért kell **r-t kapnia hogy hozzáférjen az eredeti pointerhez ha azon akar módosítani
 * Tartalmaz egy receptek felvétel, törlés, listázás, és keresés menüpontot.
 * @param r A korábban beolvasott receptek listáját tartalmazó Receptköny struct.
 */
void receptek_almenu(Receptkonyv** r)
{
    if (*r == NULL)
    {
        printf("Nincs recept a receptkönyben!\n");
    }
    int vege = 0;
    int opcio = 0;
    do
    {
        int c;
        printf("Sikeresen beléptél az almenübe, nyomj egy entert a folytatáshoz!");
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        r_menu_kiir();
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
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        switch (opcio)
        {
        case 1:
            system("@cls||clear");
            printf("Új receptet felvenni\n");
            recept_felvesz(r);
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            break;
        case 2:
            system("@cls||clear");
            printf("2.Receptet törölni\n");
            recept_torol(*r);
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            break;
        case 3:
            system("@cls||clear");
            printf("3.Ételek listázása\n");
            recept_listaz(*r);
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            break;
        case 4:
            system("@cls||clear");
            printf("4.Receptet keresni\n");
            recept_keres(*r);
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
 * @brief Megnézi hogy van-e recept a listában, ha nincs akkor inicializálja a listát. Ezután beolvas egy nevet,
 * ha tartalmazza már a tömb akkor nem engedi újra felvenni, egyébként hozzáadja a tömbhöz átméretezés után.
 * @param r Receptek listája
 */
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
#ifdef __linux__
    Osszetevo nev;
    scanf("%50[^\n]", nev.nev);
    if (recept_letezik(*r, nev.nev))
    {
        printf("Már létezik recept ezzel a névvel!\n");
        return;
    }
    int osszetevok_szama;
    printf("Írd be hány összetevője lesz!\n");
    if (scanf("%d", &osszetevok_szama) != 1)
    {
        printf("Rossz formátumú megadás, nem sikerült hozzáadni!\n");
        return;
    }
    printf("Sikeresen beolvastad az összetevők darabszámát: %d.\n", osszetevok_szama);
    Osszetevo* osszetevok = (Osszetevo*)malloc(osszetevok_szama * sizeof(Osszetevo));
    if (osszetevok == NULL)
    {
        printf("Nem sikerült lefoglalni a memóriát az összetevőknek!\n");
        return;
    }
    for (int i = 0; i < osszetevok_szama; i++)
    {
        printf("\nÍrd be a %d. összetevő nevét, mértékegységét, és mennyiségét, vesszővel elválasztva(törtszámnál tizedes pontot használj!)\n", i + 1);
        scanf("%50[^,],%50[^,],%lf", osszetevok->nev, osszetevok->tipus, &(osszetevok->mennyiseg));
        printf("Összetevő siekresen beolvasva!\n");
    }
    printf("Írd be a recept elkészítéséhez az instrukciókat, egy sorba!\n");
    Etel etel;
    scanf("%1000[\n]", etel.elkeszites);
    printf("Sikeresen hozzáadtad a receptet, nyomj egy entert a folytatáshoz!\n");
#endif

#ifdef _WIN32
    Osszetevo nev = o_beolvas1();
    if (recept_letezik(*r, nev.nev))
    {
        printf("Már létezik recept ezzel a névvel!\n");
        return;
    }

    int osszetevok_szama;
    printf("Nem létezik ezen a néven recept, a hozzáadáshoz nyomj egy entert!\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
    printf("Nyomj egy entert, majd írd be hány összetevője lesz!");
    while ((c = getchar()) != '\n' && c != EOF){}
    if (scanf(" %d", &osszetevok_szama) != 1)
    {
        printf("Rossz formátumú megadás, nem sikerült hozzáadni!\n");
        return;
    }
    printf("Sikeresen beolvastad az összetevők darabszámát: %d. Nyomj egy entert a folytatáshoz!\n", osszetevok_szama);
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
    Osszetevo *osszetevok = (Osszetevo *)malloc(osszetevok_szama * sizeof(Osszetevo));
    if (osszetevok == NULL)
    {
        printf("Nem sikerült lefoglalni a memóriát az összetevőknek!\n");
        return;
    }
    for (int i = 0; i < osszetevok_szama; i++)
    {   
        printf("\nÍrd be a %d. összetevő nevét, mértékegységét, és mennyiségét, vesszővel elválasztva(törtszámnál tizedes pontot használj!)\n", i + 1);
        osszetevok[i] = o_beolvas3();
        printf("Összetevő sikeresen beolvasva, nyomj egy entert a folytatáshoz!\n");
        while ((c = getchar()) != '\n' && c != EOF)
        {}
        while ((c = getchar()) != '\n' && c != EOF){}
    }
    printf("Írd be a recept elkészítéséhez az instrukciókat, egy sorba!\n");

    Etel etel = i_beolvas();
    printf("Sikeresen hozzáadtad a receptet, nyomj egy entert a folytatáshoz!\n");
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
/**
 * @brief Keres az adott struktúrában a név alapján amit stdin-ről olvas be.
 * @param r
 */
void recept_keres(Receptkonyv* r)
{
    if (r == NULL)
    {
        printf("Nincs recept a listában! Nyomj egy entert a továbblépéshez!\n");
        return;
    }
    printf("Írd be a keresett étel nevét!\n");
#ifdef _WIN32
    Osszetevo a = o_beolvas1();

#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf("%50[^\n]", a.nev) <= 0)
    {
        printf("Hibás név, nincs ilyen étel a listában!\n");
        return;
    };

#endif
    int i = recept_letezik(r, a.nev) - 1;
    if (i >= 0)
    {
        recept_kiir(&(r->etelek[i]));
        printf("\nA receptet sikeresen kiírtad! Nyomj egy entert a továbblépéshez!\n");

    }
    else
        printf("A keresett étel nem található! Nyomj egy entert a továbblépéshez!\n");
    return;
}
/**
 * @brief Kiírja az argumentumban kapot struct receptekben lévő ételek neveit.
 * @param r
 */
void recept_listaz(Receptkonyv* r)
{
    if (r == NULL)
    {
        printf("A receptkonyv üres!\n");
        return;
    }
    for (int i = 0; i < r->etelek_szama; i++)
    {
        printf("%d.: %s\n", i + 1, r->etelek[i].nev);
    }
    printf("Az ételek nevét sikeresen kilistáztad! Nyomj egy entert a továbblépéshez!\n");
    return;
}
/**
 * @brief Törli az adott receptet amit az étel nevével kell megadni, amennyiben létezik az r structban.
 * Készít egy ideiglenes struckt pointert, lefoglalja neki az új hoszzát, majd átmásolja az összes elemet kivéve a törlendőt, végül felszabadítja az eredetit.
 * @param r
 */
void recept_torol(Receptkonyv* r)
{
    if (r == NULL)
    {
        printf("Nincs recept a listában! Nyomj egy entert a továbblépéshez!\n");
        return;
    }
    printf("Írd be a törlendő recept nevét!\n");
#ifdef _WIN32
    Osszetevo a = o_beolvas1();

#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf("%50[^\n]", a.nev) <= 0)
    {
        printf("Hibás név, nem sikerült az összetevőt felvenni!\n");
        return;
    };

#endif
    int j = recept_letezik(r, a.nev) - 1;
    if (j >= 0)
    {
        Etel* temp_r = (Etel*)malloc((r->etelek_szama - 1) * sizeof(Etel));
        if (temp_r == NULL && r->etelek_szama - 1 != 0)
        {
            printf("Nem sikerült a memória foglalás az összetevő törléséhez!\n");
            return;
        }
        int poz = 0;
        for (int i = 0; i < r->etelek_szama; i++)
        {
            if (i != j)
            {
                temp_r[poz] = r->etelek[i];
                poz++;
            }
        }
        free(r->etelek[j].osszetevok);
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

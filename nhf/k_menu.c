/**
 * @file r_menu.c
 * @brief A qol és a kedvencek/bevásárlólista modulja, tartalmazza az almenüket és az azokhoz szükséges funkciókat.
 * @date 2024-11-08
 */

#include "k_menu.h"
 /**
  * @brief Kilistázza a Qol almenü pontjait stdio-n.
  */
void q_menu_kiir(void)
{
    for (int i = 0;i < 80;i++) printf("=");
    printf(COLOR_BOLD"\n%*.s%s\n"COLOR_RESET, 35, " ", "QOL ALMENÜ");
    for (int i = 0;i < 80;i++) printf("=");
    printf("\n%*.s"COLOR_UNDERLINE"Mit szeretnél csinálni? A megfelelő számot írd be!"COLOR_RESET"\n\n", 15, " ");
    printf(COLOR_GREEN"1.    ➤ Random recept\n");
    printf("2.    ➤ Receptek keresése összetevő alapján\n");
    printf(COLOR_BRIGHT_RED"3.    ➤ Kilépni a főmenübe\n"COLOR_RESET);
    return;
}
/**
 * @brief A qol almenü vezérlője, két fő opciót tartalmaz, random keresést, és összetevő alapján történő keresést.
 * @param r A korábban beolvasott receptek listáját tartalmazó Receptköny struct.
 */
void qol_almenu(Receptkonyv* r)
{
    if (r == NULL || r->etelek_szama == 0)
    {
        printf("Nincs recept a receptkönyben! Receptek nélkül ezek a funkciók nem működnek, visszalépés a főmenübe!\n");
        return;

    }
    int vege = 0;
    int opcio = 0;
    int c;
    do
    {
        printf("Sikeresen beléptél az almenübe, nyomj egy entert a folytatáshoz!");
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        q_menu_kiir();
        int sikeres = scanf("%d", &opcio);

        while (sikeres != 1 || opcio < 1 || opcio > 3)
        {
            printf("Hibás bevitel. Csak számot adj meg 1 és 3 között.\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Add meg a választott opciót (1-3): ");
            sikeres = scanf("%d", &opcio);
        }
        while ((c = getchar()) != '\n' && c != EOF) {}
        switch (opcio)
        {
        case 1:
            system("@cls||clear");
            printf("Random recept\n");
            recept_random(r);
            while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        case 2:
            system("@cls||clear");
            printf("Receptek keresése összetevő alapján\n");
            receptek_szures(r);
            while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        case 3:
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
 * @brief Random választ egy receptet, kiírja a nevét, majd ha azt elfogadja a felhasználó kiírja a receptjét.
 * @param r receptkönyv struktúra, tartalmazza a recepteket
 */
void recept_random(Receptkonyv* r)
{   //a c amibe ürítem az stdin-t az o meg a keresett opció
    char c;
    char o;
    srand(time(0));
    int random = (rand() % r->etelek_szama);
    do {
        printf("A generált étel: "COLOR_RED"%s\n"COLOR_RESET, r->etelek[random].nev);
        printf("Nyomj egy I/i-t az elfogadáshoz, vagy N/n-t, ha szeretnél újat generálni.\n");
        int sikeres = scanf("%c", &o);
        while (sikeres != 1 || (tolower(o) != 'n' && tolower(o) != 'i'))
        {
            printf("Hibás bevitel. Csak I/i-t vagy N/n-t írhatsz be. Nyomj egy entert a folytatáshoz!\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Add meg a választott opciót: ");
            sikeres = scanf("%c", &o);
        }
        if (tolower(o) == 'n')     random = (rand() % r->etelek_szama);
        while ((c = getchar()) != '\n' && c != EOF) {}
    } while (tolower(o) != 'i');
    recept_kiir(&(r->etelek[random]));
    printf("\nAz étel receptjét sikeresen kiírtad! Nyomj egy entert a továbblépéshez!\n");
    return;
}
/**
 * @brief Bekér egy összetevőt majd kiírja a listát amit arra az összetevőre szűrt, ha talált
 * elemetket amik tartalmazzák az adott összetevőt akkor megkérdezi hogy folytassa-e a szűkitést.
 * A szűréshez készit egy boolean-okból álló tömböt és ezzel maszkolja az eredeti listát.
 * Ha igen akkor megint kér egy elemet, ha nem akkor egy étel nevét kéri aminek kiírja a receptjét vagy nullát a visszalépéshez.
 * @param r
 */
void receptek_szures(Receptkonyv* r) {
    // Csinal egy "hash"-tablat hogy melyik receptre igaz hogy van benne az adott összetevő
    bool* egyezo_receptek = (bool*)malloc(r->etelek_szama * sizeof(bool));
    int c;
    if (egyezo_receptek == NULL) {
        printf("Nem sikerült a memória foglalás a szűréshez! Nyomj egy entert a folytatáshoz!\n");
        return;
    }

    // Elősször minden igaz
    for (int i = 0; i < r->etelek_szama; i++) {
        egyezo_receptek[i] = true;
    }

    int egyezo_db = r->etelek_szama;
    char folytatas = 'i';

    while (folytatas == 'i' && egyezo_db > 0) {
        printf("\nÍrd be a keresett összetevő nevét:\n");
#ifdef _WIN32
        Osszetevo a = o_beolvas1();
        printf("Nyomj egy entert a folytatáshoz!");
        while ((c = getchar()) != '\n' && c != EOF) {}

#endif
#ifdef __linux__
        Osszetevo a;
        if (scanf("%50[^\n]", a.nev) <= 0)
        {
            printf("Hibás név, nem sikerült az összetevőt felvenni!\n");
            return;
        };
#endif

        // Az a-ba beolvasott név alapján szűrünk
        egyezo_db = 0;
        for (int i = 0; i < r->etelek_szama; i++) {
            if (egyezo_receptek[i]) {  // Csak az előzőleg még a listában levő elemek között keres
                bool tartalmaz = false;
                for (int j = 0; j < r->etelek[i].osszetevok_szama; j++) {
                    if (strcasecmp(r->etelek[i].osszetevok[j].nev, a.nev) == 0) {
                        tartalmaz = true;
                        break;
                    }
                }
                egyezo_receptek[i] = tartalmaz;
                if (tartalmaz) egyezo_db++;
            }
        }

        // Kiírja a talált recepteket
        printf("\nTalált receptek (%d db):\n", egyezo_db);
        if (egyezo_db > 0) {
            for (int i = 0; i < r->etelek_szama; i++) {
                if (egyezo_receptek[i]) {
                    printf("%s\n", r->etelek[i].nev);
                }
            }
            printf("Sikeresen kilistáztad a recepteket, nyomj egy entert a folytatáshoz!");
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("\nSzeretnéd másik összetevővel szűkiteni a szűrést? (i/I v n/N): ");
            int sikeres = scanf("%c", &folytatas);
            while (sikeres != 1 || (tolower(folytatas) != 'n' && tolower(folytatas) != 'i'))
            {
                printf("Hibás bevitel. Csak I/i-t vagy N/n-t írhatsz be.\n");
                while ((folytatas = getchar()) != '\n' && folytatas != EOF) {}
                printf("Add meg a választott opciót: ");
                sikeres = scanf("%c", &folytatas);
            }
            printf("A választott opció: %c. Nyomj egy entert a folytatáshoz!\n", folytatas);
            while ((c = getchar()) != '\n' && c != EOF) {}

        }
        else {
            printf("Nincs több recept ami tartalmazza az összes keresett összetevőt. Nyomj egy entert a folytatáshoz!\n");
            free(egyezo_receptek);
            return;
        }

    }
    printf("Írd be a keresett étel nevét, vagy '0'-át a kilépéshez!\n");
#ifdef _WIN32
    Osszetevo b = o_beolvas1();

#endif
#ifdef __linux__
    Osszetevo b;
    if (scanf(" %50[^\n]", b.nev) <= 0)
    {
        printf("Hibás név!\n");
        return;
    };

#endif
    if (!(strcmp("0", b.nev))) {
        free(egyezo_receptek);
        printf("Sikeresen kiléptél, nyomj egy entert a folytatáshoz!");
        return;
    }
    int i = recept_letezik(r, b.nev) - 1;
    if (i >= 0) {
        recept_kiir(&(r->etelek[i]));
        printf("\nA receptet sikeresen kiírtad! Nyomj egy entert a továbblépéshez!\n");
    }
    else {
        printf("A keresett étel nem található, rosszul írtad be a nevét! Nyomj egy entert a folytatáshoz!\n");
    }
    free(egyezo_receptek);
    return;
}
/////////////////////////////////////////////////////////////////////////////
//Bevásárló lista almenü itt kezdődik
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief Kilistázza a bevásárlólista almenü pontjait stdio-n.
 */
void bl_menu_kiir(void)
{
    for (int i = 0;i < 80;i++) printf("=");
    printf(COLOR_BOLD"\n%*.s%s\n"COLOR_RESET, 23, " ", "BEVÁSÁRLÓLISTA és KEDVENCEK ALMENÜ");
    for (int i = 0;i < 80;i++) printf("=");
    printf("\n%*.s"COLOR_UNDERLINE"Mit szeretnél csinálni? A megfelelő számot írd be!"COLOR_RESET"\n\n", 15, " ");
    printf(COLOR_GREEN"1.    ➤ Recept hozzáadása a bevásárló listához\n");
    printf("2.    ➤ A bevásárló lista tartalmának törlése\n");
    printf("3.    ➤ A bevásárló lista mentése file-ba\n");
    printf(COLOR_CYAN"4.    ➤ Étel hozzáadása a kedvencek listához\n");
    printf("5.    ➤ Étel törlése a kedvencek listából\n");
    printf("6.    ➤ A kedvencek lista kiírása\n");
    printf(COLOR_BRIGHT_RED"7.    ➤ Kilépni a főmenübe\n"COLOR_RESET);
    return;
}
/**
 * @brief A bevásárlólista almenü vezérlője, három fő opciót tartalmaz, étel összetevőinek hozzáadása
 * a listához a recept neve alapján, a lista törlését, és a lista file-ba mentésének lehetőségét.
 * Ebben az almenüben kaptak helyet a kedvencek is, mivel így kényelmesebb rögtön a bevásálólistához adni őket mintha menüket kellene váltani.
 * A kedvencek szekció a következő almenüket tartalmazza: étel hozzáadása és törlése a kedvencek listából, illetve a kedvencek lista kiírása.
 * @param r A korábban beolvasott receptek listáját tartalmazó Receptköny struct.
 */
void bl_almenu(Receptkonyv* r)
{
    if (r == NULL || r->etelek_szama == 0)
    {
        printf("Nincs recept a receptkönyben! Receptek nélkül ezek a funkciók nem működnek, visszalépés a főmenübe!\n");
        return;

    }
    //bevasarlo lista struct inicializálása
    Egyedi_osszetevok* bl = (Egyedi_osszetevok*)malloc(sizeof(Egyedi_osszetevok));
    if (bl == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriát az bevásárlólistának!\n");
        return;
    }
    bl->egyedi_osszetevok_szama = 0;
    bl->egyedi_osszetevok = NULL;
    //kedvencek struct inicializálása
    Receptkonyv* kedvenc = receptek_beolvas("kedvencek.txt");
    int vege = 0;
    int opcio = 0;
    int c;
    do
    {
        printf("Sikeresen beléptél az almenübe, nyomj egy entert a folytatáshoz!");
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        bl_menu_kiir();
        int sikeres = scanf("%d", &opcio);
        while (sikeres != 1 || opcio < 1 || opcio > 7)
        {
            printf("Hibás bevitel. Csak számot adj meg 1 és 7 között.\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Add meg a választott opciót (1-7): ");
            sikeres = scanf("%d", &opcio);
        }
        while ((c = getchar()) != '\n' && c != EOF) {}
        switch (opcio)
        {
        case 1:
            system("@cls||clear");
            printf("Recept hozzáadása a bevásárló listához\n");
            bl_hozzaad(r, bl);
            while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        case 2:
            system("@cls||clear");
            printf("A bevásárló lista tartalmának törlése,nyomj egy entert a folytatáshoz!\n");
            bl_torol(bl);
            while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        case 3:
            system("@cls||clear");
            printf("A bevásárló lista sikeresen mentve, nyomj egy entert a folytatáshoz!\n");
            bl_ment(bl);
            while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        case 4:
            system("@cls||clear");
            printf("Étel hozzáadása a kedvencek listához\n");
            kedvenc_hozzáad(r, &kedvenc);
            while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        case 5:
            system("@cls||clear");
            printf("Étel törlése a kedvencek listából\n");
            recept_torol(kedvenc);
            while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        case 6:
            system("@cls||clear");
            printf("A kedvencek lista kiírása\n");
            recept_listaz(kedvenc);
            recept_keres(kedvenc);
            while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        case 7:
            system("@cls||clear");
            printf("Kilépés\n");
            vege = 1;
            break;
        default:
            printf("Érvénytelen parnacs\n");
            break;
        }
    } while (!vege);
    receptet_fileba_ment(kedvenc, "kedvencek.txt");
    receptkonyv_felszabadit(kedvenc);
    egyedi_osszetevo_felszabadit(bl);
    return;
}
/**
 * @brief Az összetevő hozzáad fv mintájára megnézi hogy az étel létezik e, majd megnézi hogy az összetevő a listában van e,
 * ha igen akkor hozzáadja a mennyiséget ha nem akkor az egészet hozzáadja. Realloccal megy, nem a legszebb de nem kifejezetten lassú, csak ezért nem gyártottam ll-t.
 * @param r A receptek listája
 * @param e A bevásárló lista
 */
void bl_hozzaad(Receptkonyv* r, Egyedi_osszetevok* e) {
    printf("Írd be a hozzáadni kívánt étel nevét!\n");
#ifdef _WIN32
    Osszetevo a = o_beolvas1();
#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf("%50[^\n]", a.nev) != 1)
    {
        printf("Hibás név, nem sikerült a receptet felvenni!\n");
        return;
    };
#endif
    int recept_szam = recept_letezik(r, a.nev) - 1;
    //megnézzük létezik e a recept
    if (recept_szam != -1)
    {
        for (int i = 0; i < r->etelek[recept_szam].osszetevok_szama; i++) {
            int osszetevo_szam = osszetevo_letezik(e, r->etelek[recept_szam].osszetevok[i].nev) - 1;
            //Minden összetevőre megnézzük létezik-e
            if (osszetevo_szam == -1)
            {
                e->egyedi_osszetevok_szama++;
                //Azért tempbe hogy ha nem sikerül foglalni akkor az eredeti ne vesszen el
                Osszetevo* temp = realloc(e->egyedi_osszetevok, e->egyedi_osszetevok_szama * sizeof(Osszetevo));
                if (temp == NULL)
                {
                    printf("Nem sikerült a memória bővítése az összetevőknek!\n");
                    e->egyedi_osszetevok_szama--;
                    return;
                }
                e->egyedi_osszetevok = temp;
                //átmásoljuk a megfelelő struktúrába
                strcpy(e->egyedi_osszetevok[e->egyedi_osszetevok_szama - 1].nev, r->etelek[recept_szam].osszetevok[i].nev);
                strcpy(e->egyedi_osszetevok[e->egyedi_osszetevok_szama - 1].tipus, r->etelek[recept_szam].osszetevok[i].tipus);
                e->egyedi_osszetevok[e->egyedi_osszetevok_szama - 1].mennyiseg = r->etelek[recept_szam].osszetevok[i].mennyiseg;

            }
            //ha létezik akkor csak a mennyiséget adjuk hozzá 
            else {
                e->egyedi_osszetevok[osszetevo_szam].mennyiseg += r->etelek[recept_szam].osszetevok[i].mennyiseg;
            }
        }
        printf("Az ételt sikeresen hozzáadtad! Nyomj egy entert a továbblépéshez!\n");
    }
    else {
        printf("Az étel nincs a receptkönyvben!\n");
    }
    return;
}
/**
 * @brief Elmenti a kész bevásárló listát egy blista.txt file-ba. Ha létezett korábban akkor felülírja.
 * @param e bevásárló lista structja
 */
void bl_ment(Egyedi_osszetevok* e) {
    if (e->egyedi_osszetevok == NULL)
    {
        printf("Üres a bevásárlólista!\n");
        return;
    }
    FILE* f = fopen("blista.txt", "w");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni a file-t!\n");
        return;
    }
    for (int i = 0; i < e->egyedi_osszetevok_szama; i++)
    {
        fprintf(f, "%s: %.1lf %s\n", e->egyedi_osszetevok[i].nev, e->egyedi_osszetevok[i].mennyiseg, e->egyedi_osszetevok[i].tipus);
    }
    fclose(f);
}
/**
 * @brief Kitörli a bevásárlólista tartalmát, felszabadítja ha volt benne összetevő, beállítja a pointerüket null-ra, és az összetevők számát is null-ra
 * @param e A bevásárlólista strucktja
 */
void bl_torol(Egyedi_osszetevok* e) {
    if (e->egyedi_osszetevok == NULL)
    {
        printf("Üres a bevásárlólista!\n");
        return;
    }
    free(e->egyedi_osszetevok);
    e->egyedi_osszetevok = NULL;
    e->egyedi_osszetevok_szama = 0;
    FILE* f = fopen("blista.txt", "w");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni a file-t!\n");
        return;
    }
    fprintf(f, " ");
    fclose(f);
}
/**
 * @brief Hozzáadja a beírt ételt az r-ből a k structba, amennyiben az szerepel az r-ben és még nem szerepel a k-ban.
 * Amennyiben a k null pointer létrehoz egy üres k-t és ahhoz adja hozzá.
 * @param k kedvencek struktúra
 * @param r receptkönyv struktúra
 */
void kedvenc_hozzáad(Receptkonyv* r, Receptkonyv** k) {
    //ha nincs semmi a kedvencekben akkor létrehozunk egy üres structot
    if (*k == NULL)
    {
        printf("Nincs recept a listában!\n");
        *k = (Receptkonyv*)malloc(sizeof(Receptkonyv));
        if (*k == NULL)
        {
            printf("Nem lehetett lefoglalni a memoriat az kedvenceknek!\n");
            return;
        }
        (*k)->etelek_szama = 0;
        (*k)->etelek = NULL;
    }
    printf("Írd be a hozzáadni kívánt étel nevét!\n");

#ifdef _WIN32
    Osszetevo a = o_beolvas1();
#endif
#ifdef __linux__
    Osszetevo a;
    if (scanf("%50[^\n]", a.nev) != 1)
    {
        printf("Hibás név, nem sikerült a receptet felvenni!\n");
        return;
    };
#endif
    int recept_szam = recept_letezik(r, a.nev) - 1;
    //megnézzük létezik e a recept
    if (recept_szam != -1)
    {
        //megnézzük benne van e már a kedvencekben
        if (!(recept_letezik(*k, a.nev))) {
            (*k)->etelek_szama++;
            Etel* temp = realloc((*k)->etelek, (*k)->etelek_szama * sizeof(Etel));
            if (temp == NULL)
            {
                printf("Nem sikerült a memória bővítése a recepthez!\n");
                (*k)->etelek_szama--;
                return;
            }
            (*k)->etelek = temp;
            //recept részeinek másolása
            strcpy((*k)->etelek[(*k)->etelek_szama - 1].nev, r->etelek[recept_szam].nev);
            (*k)->etelek[(*k)->etelek_szama - 1].osszetevok_szama = r->etelek[recept_szam].osszetevok_szama;
            strcpy((*k)->etelek[(*k)->etelek_szama - 1].elkeszites, r->etelek[recept_szam].elkeszites);
            (*k)->etelek[(*k)->etelek_szama - 1].osszetevok = (Osszetevo*)malloc(r->etelek[recept_szam].osszetevok_szama * sizeof(Osszetevo));
            if ((*k)->etelek[(*k)->etelek_szama - 1].osszetevok == NULL) {
                printf("Nem sikerült a kedvencek listában a hozzáadott ételhez memóriát foglalni.\n");
                (*k)->etelek_szama--;
                //igen csúnya de így meg tudom őrizni az eredeti listát, bár ehhez a mallochoz már nem írok hibakezelést
                (*k)->etelek = (Etel*)realloc((*k)->etelek, (*k)->etelek_szama * sizeof(Etel));
                return;
            }
            //összetevők másolása
            for (int i = 0; i < r->etelek[recept_szam].osszetevok_szama; i++) {
                (*k)->etelek[(*k)->etelek_szama - 1].osszetevok[i] = r->etelek[recept_szam].osszetevok[i];
            }
            printf("Sikeresen hozzáadva, nyomj egy entert a folytatáshoz!\n");
        }
        else {
            printf("Ez a recept már a kedvencek listában van!\n");
        }
    }
    else {
        printf("Ez a recept nem létezik a receptkönyvben!\n");
    }
    return;
}

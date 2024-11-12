/**
 * @file r_menu.c
 * @brief A qol, a kedvencek és a bevásárlólista modulja tartalmazza az almenüket és az azokhoz szükséges funkciókat.
 * @date 2024-11-08
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "file_utils.h"
#include "debugmalloc.h"


void recept_random(Receptkonyv* r);
void qol_almenu(Receptkonyv* r);
void receptek_szures(Receptkonyv* r);


/**
 * @brief Kilistázza a Qol almenü pontjait stdio-n.
 */
void q_menu_kiir(void)
{
    for (int i = 0;i < 80;i++) printf("=");
    printf(COLOR_BOLD"\n%*.s%s\n"COLOR_RESET, 33, " ", "RECEPTEK ALMENÜ");
    for (int i = 0;i < 80;i++) printf("=");
    printf("\n%*.s"COLOR_UNDERLINE"Mit szeretnél csinálni? A megfelelő számot írd be!"COLOR_RESET"\n\n", 15, " ");
    printf(COLOR_GREEN"1.    ➤ Random recept\n");
    printf("2.    ➤ Receptek keresése összetevő alapján\n");
    printf("3.    ➤ Kilépni a főmenübe\n"COLOR_RESET);
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
        q_menu_kiir();
        int sikeres = scanf("%d", &opcio);

        while (sikeres != 1 || opcio < 1 || opcio > 3)
        {
            printf("Hibás bevitel. Csak számot adj meg 1 és 5 között.\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Add meg a választott opciót (1-3): ");
            sikeres = scanf("%d", &opcio);
        }
        while ((c = getchar()) != '\n' && c != EOF) {}
        switch (opcio)
        {
        case 1:
            system("@cls||clear");
            printf("Új receptet felvenni\n");
            recept_random(r);
            while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        case 2:
            system("@cls||clear");
            printf("2.Receptet törölni\n");
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
{
    char c;
    srand(time(0));
    int random = (rand() % r->etelek_szama);
    do {
        printf("A generált étel: %s\n", r->etelek[random].nev);
        printf("Nyomj egy I/i-t az elfogadáshoz, vagy N/n-t, ha szeretnél újat generálni.\n");
        int sikeres = scanf("%c", &c);
        while (sikeres != 1 || (tolower(c) != 'n' && tolower(c) != 'i'))
        {
            printf("Hibás bevitel. Csak I/i-t vagy N/n-t írhatsz be.\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Add meg a választott opciót: ");
            sikeres = scanf("%c", &c);
        }
        if (tolower(c) == 'n')     random = (rand() % r->etelek_szama);
    } while (tolower(c) != 'i');
    recept_kiir(&(r->etelek[random]));
    printf("\nAz étel receptjét sikeresen kiírtad! Nyomj egy entert a továbblépéshez!\n");
    return;
}

/**
 * @brief Bekér egy összetevőt majd kiírja a listát amit arra az összetevőre szűrt, ha talált
 * elemetket amik tartalmazzák az adott összetevőt akkor megkérdezi hogy folytassa-e a szűkitést.
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

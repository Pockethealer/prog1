/**
 * @file menu.c
 * @brief A főmenüt kezelő modul, csak a főmenü, és a kilépés funkcionalitását tartalmazza.
 *
 * @date 2024-11-08
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /*A helyes konzolmegjelenítéshez kell windowson*/
#ifdef _WIN32
#include <windows.h>
#include <locale.h>
#endif
/*Saját modulok*/
#include "file_utils.h"
#include "o_menu.h"
#include "r_menu.h"
#include "k_menu.h"
#include "debugmalloc.h"

int main_menu(void);
int kilepes(Egyedi_osszetevok* e, Receptkonyv* r);
void menu_kiir(void);

/**
 * @brief Kilistázza a menüopciókat, stdio-n.
 */
void menu_kiir(void)
{
    for (int i = 0;i < 80;i++) printf("=");
    printf(COLOR_BOLD"\n%*.s%s\n"COLOR_RESET, 37, " ", "FŐMENÜ");
    for (int i = 0;i < 80;i++) printf("=");
    printf("\n%*.s"COLOR_UNDERLINE"Mit szeretnél csinálni? A megfelelő számot írd be!"COLOR_RESET"\n\n", 15, " ");
    printf(COLOR_YELLOW"1.    ➤ Összetevők kezelése\n");
    printf("2.    ➤ Receptek kezelése\n");
    printf("3.    ➤ Qol funkciók\n");
    printf("4.    ➤ Bevásárló lista kezelése\n");
    printf("5.    ➤ Kedvencek kezelése\n");
    printf("6.    ➤ Kilépni\n"COLOR_RESET);
    return;
}

/**
 * @brief Meghívja a kilépés előtti fv-eket: elmenti a recepteket és
 * összetevőket és meghívja a megfelelő felszabadító fv-eket.
 * @param e Egyedi_osszetevo struktúra, amiben az összes összetevő van.
 * @param r Receptkony struktúra, amiben az összes receptet tárolom.
 * @return int visszatér nullával ha sikerült minden, majd később hibakezeléshez kell.
 */
int kilepes(Egyedi_osszetevok* e, Receptkonyv* r)
{
    receptet_fileba_ment(r);
    osszetevo_fileba_ment(e, r);
    egyedi_osszetevo_felszabadit(e);
    receptkonyv_felszabadit(r);
    return 0;
}

/**
 * @brief A főmenü logikájával foglalkozó fv. Beolvassa a fileokból az összetevők listáját(továbbiakban e), és receptek listáját(továbbiakban r).
 * A véletlenszerűnek tűnően elhelyezett "while (getchar() != '\n') {}" az utf-8 as beolvasás miatt kellenek,
 * mivel inkonzisztensen olvassa az stdio streamet ezért ezzel törlöm az esetlegesen bennmaradt adatot a következő beolvasás előtt,
 * mivel az fflush nem definiált c-ben és vicces dolgokat művel néha.
 * A "system("@cls||clear");" csak kozmetikai célok miatt van ott, törli a konzolablakot az átláthatóság kedvéért.
 * Tartalmaz egy összetevők, receptek, qol, bev. lista, és kedvencek menüpontot.
 * @return int ha minden rendben visszatér nullával, majd később hibakezeléshez.
 */
int main_menu(void)
{
    /*locale beállítása windowson*/
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "hu_HU.UTF-8");
    /*Ansi engedélyezés a consolnak */
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
    /*struktúrák inicializálása*/
    Egyedi_osszetevok* osszetevo = osszetevo_beolvas();
    Receptkonyv* konyv = receptek_beolvas();
    int vege = 0;
    int opcio = 0;
    /*fő menülogika*/
    do
    {
        menu_kiir();
        int sikeres = scanf("%d", &opcio);
        while (sikeres != 1 || opcio < 1 || opcio > 6)
        {
            printf("Hibás bevitel. Csak számot adj meg 1 és 6 között.\n");
            while (getchar() != '\n') {}
            printf("Add meg a választott opciót (1-6): ");
            sikeres = scanf("%d", &opcio);
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        switch (opcio)
        {
        case 1:
            system("@cls||clear");
            printf("Összetevők kezelése\n");
            osszetevok_almenu(&osszetevo);
            break;
        case 2:
            system("@cls||clear");
            printf("Receptek kezelése\n");
            receptek_almenu(&konyv);
            break;
        case 3:
            system("@cls||clear");
            printf("Qol funkciók\n");
            qol_almenu(konyv);
            break;
        case 4:
            system("@cls||clear");
            printf("Bevásárló lista kezelése\n");
            //TODO
            break;
        case 5:
            system("@cls||clear");
            printf("Kedvencek kezelése\n");
            //TODO
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
    /*program bezárása*/
    kilepes(osszetevo, konyv);
    return 0;
}

int main(void) {
    main_menu();
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <locale.h>
#endif
#include "file_utils.h"
#include "debugmalloc.h"
#include "o_menu.h"
#include "r_menu.h"

int main_menu(void);
int kilepes(Egyedi_osszetevok* e, Receptkonyv* r);
void menu_kiir(void);


void menu_kiir(void)
{
    printf("Mit szeretnél csinálni? A megfelelő számot írd be!\n\n");
    printf("1.Összetevők kezelése\n");
    printf("2.Receptek kezelése\n");
    printf("3.Qol funkciók\n");
    printf("4.Bevásárló lista kezelése\n");
    printf("5.Kedvencek kezelése\n");
    printf("6.Kilépni\n");
    return;
}

/**
 * @brief Meghívja a kilépés előtti fv-eket: elmenti a recepteket és
 * összetevőket és meghívja a megfelelő felszabadító fv-eket.
 * @param e Egyedi_osszetevo struktúra
 * @param r Receptkony struktúra
 * @return int visszatér nullával ha sikerült minden
 */
int kilepes(Egyedi_osszetevok* e, Receptkonyv* r)
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
    Egyedi_osszetevok* osszetevo = osszetevo_beolvas();
    Receptkonyv* konyv = receptek_beolvas();
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

#include <stdio.h>
#include <stdbool.h>
#include "include/osszetevo.h"
#include "include/menu.h"

int main(int argc, char** argv) {
    bool vege = false;
    int a = 0;
    Osszetevo osszetevok[200];

    int osszetevo_db = osszetevo_beolvas(osszetevok);

    Osszetevo uj = { "Erős pista", osszetevo_db + 1, "g", 700 };
    osszetevo_fileba_ir(uj, osszetevok);
    osszetevo_kiir(osszetevok, 1, 100);

    do {
        menu_kiir();
        if (scanf("%d", &a) == 0)
            break;
        switch (a) {
        case 1:
            printf("ide jonnek majd a receptek\n");
            break;
        case 2:
            printf("itt lehe majd keresni\n");
            break;
        case 3:
            printf("itt lesz majd a recept torles\n");
            break;
        case 4:
            printf("Kilepes\n");
            vege = true;
            break;
        default:
            printf("Ervenytelen parnacs");
            break;
        }
    } while (!vege);

    return 0;
}
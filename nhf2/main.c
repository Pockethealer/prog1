#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"
#include "debugmalloc.h"
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    setlocale(LC_ALL, "hu_HU.UTF-8");
    Receptkonyv* konyv = receptek_beolvas();
    printf("%s\n%s\n%d\n", konyv->etelek[1].osszetevok[2].tipus, konyv->etelek[1].osszetevok[2].nev, strlen(konyv->etelek[1].osszetevok[2].nev));
    receptet_fileba_ment(konyv);
    Egyedi_osszetevok* osszetevo = osszetevo_beolvas();
    printf("%s\n", osszetevo->egyedi_osszetevok[5].tipus);
    osszetevo_fileba_ment(osszetevo, konyv);
    egyedi_osszetevo_felszabadit(osszetevo);
    receptkonyv_felszabadit(konyv);
    return 0;
}

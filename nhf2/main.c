#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"
#include "debugmalloc.h"
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, "hu_HU.UTF-8");
    Receptkonyv* konyv = receptek_beolvas();
    printf("%s, \n%s\n %s\n", konyv->etelek[3].nev, konyv->etelek[5].elkeszites, konyv->etelek[9].osszetevok[0].nev);
    receptkonyv_felszabadit(konyv);
    return 0;
}
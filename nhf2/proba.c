#include "file_utils.h"
#include "menu.h"
#include <stdio.h>

int main(void)
{

    /*struktúrák inicializálása*/
    Egyedi_osszetevok *osszetevo = osszetevo_beolvas();
    if (osszetevo == NULL)
    {
        printf("nem sikerült az összetevők beolvasása!, kilépés");
        return -1;
    }
    Receptkonyv *konyv = receptek_beolvas();
    if (konyv == NULL)
    {
        printf("nem sikerült az összetevők beolvasása!, kilépés");
        kilepes(osszetevo, NULL);
        return -1;
    }
    kilepes(osszetevo, konyv);
    return 0;
}
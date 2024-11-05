#include <stdio.h>
#include "beolvas.h"
#include"file_utils.h"

int main(void) {
    printf("proba");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "hu_HU.UTF-8");
    Osszetevo o = beolvas();
    printf("második próba\n %s, %s", o.nev, o.tipus);
    return 0;
}
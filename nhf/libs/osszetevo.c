#include <stdio.h>
#include "../include/osszetevo.h"
#include "../include/file_utils.h"

int osszetevo_beolvas(Osszetevo* osszetevok) {
    FILE* osszetevo_file = file_megnyit("osszetevok.txt", "r");
    if (osszetevo_file != NULL) {
        Osszetevo* p_osszetevo = osszetevok;
        int osszetevo_db = 0;
        while (fscanf(osszetevo_file, " %49[^;];%d;%9[^;];%d",
            p_osszetevo->nev,
            &(p_osszetevo->sorszam),
            p_osszetevo->tipus,
            &(p_osszetevo->ar)) == 4) {
            p_osszetevo++;
            osszetevo_db++;
        }
        fclose(osszetevo_file);
        return osszetevo_db;
    }
    else
        return -1;
}

void osszetevo_kiir(Osszetevo* osszetevok, int mit, int hanyadik) {
    switch (mit) {
    case 1:
        printf("%s", osszetevok[hanyadik].nev);
        break;
    case 2:
        printf("%d", osszetevok[hanyadik].sorszam);
        break;
    case 3:
        printf("%s", osszetevok[hanyadik].tipus);
        break;
    case 4:
        printf("%d", osszetevok[hanyadik].ar);
        break;
    default:
        break;
    }
}

int osszetevo_fileba_ir(Osszetevo osszetevo, Osszetevo* osszetevok) {
    FILE* file = file_megnyit("osszetevok.txt", "a");
    if (file != NULL) {
        fprintf(file, " \n%s;%d;%s;%d", osszetevo.nev,
            osszetevo.sorszam, osszetevo.tipus, osszetevo.ar);
        fclose(file);
        osszetevo_beolvas(osszetevok);
        return 0;
    }
    return -1;
}
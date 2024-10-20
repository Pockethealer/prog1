#ifndef OSSZETEVO_H
#define OSSZETEVO_H

typedef struct Osszetevo {
    char nev[50];
    int sorszam;
    char tipus[10];
    int ar;
} Osszetevo;

int osszetevo_beolvas(Osszetevo* osszetevok);
void osszetevo_kiir(Osszetevo* osszetevok, int mit, int hanyadik);
int osszetevo_fileba_ir(Osszetevo osszetevo, Osszetevo* osszetevok);

#endif
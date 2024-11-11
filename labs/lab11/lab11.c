#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"

typedef struct BiFa {
    int ertek;
    struct BiFa* bal, * jobb;
} BiFa;

BiFa* beszur(BiFa* gyoker, int ertek) {
    if (gyoker == NULL) {
        BiFa* uj = (BiFa*)malloc(sizeof(BiFa));
        uj->ertek = ertek;
        uj->bal = uj->jobb = NULL;
        return uj;
    }
    if (ertek < gyoker->ertek) {        /* balra szur */
        gyoker->bal = beszur(gyoker->bal, ertek);
    }
    else if (ertek > gyoker->ertek) {   /* jobbra szur */
        gyoker->jobb = beszur(gyoker->jobb, ertek);
    }
    else {
        /* mar benne van */
    }
    return gyoker;
}
/*fa kiírása*/
void kiir(BiFa* gyoker) {
    if (gyoker == NULL) {
        return;
    }
    kiir(gyoker->bal);
    printf("%d ", gyoker->ertek);
    kiir(gyoker->jobb);
    return;
}
/*fa törlése */
void torol(BiFa* gyoker) {
    if (gyoker == NULL) return;
    torol(gyoker->bal);
    torol(gyoker->jobb);
    free(gyoker);
    return;
}
/*keres*/
BiFa* keres(BiFa* gyoker, int keresett) {

    if (gyoker == NULL) return NULL;
    if (gyoker->ertek > keresett) return keres(gyoker->bal, keresett);
    if (gyoker->ertek < keresett) return keres(gyoker->jobb, keresett);
    return gyoker;
}
/*negálás*/
void negal(BiFa* gyoker) {
    if (gyoker == NULL) return;
    gyoker->ertek *= -1;
    negal(gyoker->bal);
    negal(gyoker->jobb);
    return;
}
/*tükrözés*/
void tukroz(BiFa* gyoker) {
    if (gyoker == NULL) return;
    tukroz(gyoker->bal);
    tukroz(gyoker->jobb);
    BiFa* tmp = gyoker->bal;
    gyoker->bal = gyoker->jobb;
    gyoker->jobb = tmp;
}

int main(void) {
    int minta[] = { 15, 96, 34, 12, 14, 56, 21, 11, 10, 9, 78, 43, 0 };
    BiFa* gyoker = NULL;
    for (int i = 0; minta[i] > 0; i++)
        gyoker = beszur(gyoker, minta[i]);
    /* Ide tedd be a kipróbálandó függvények hívásait! */
    kiir(gyoker);
    printf("\n");
    /*keres*/
    int a = (keres(gyoker, 14)->ertek);
    printf("%d\n", a);
    /*tükröz*/
    negal(gyoker);
    kiir(gyoker);
    printf("\n");
    /*fordítani kéne a reláción hogy működjön a keresés*/
    tukroz(gyoker);
    kiir(gyoker);
    printf("\n");
    a = (keres(gyoker, -14)->ertek);
    printf("%d\n", a);
    torol(gyoker);
    return 0;
}
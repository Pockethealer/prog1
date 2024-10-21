#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "debugmalloc.h"

/*szamok visszafele
int main(void) {
    int meret;
    double* tomb;
    printf("Mekkora legyen a tomb merete?\n");
    scanf("%d", &meret);
    tomb = malloc(meret * sizeof(double));
    if (tomb == NULL) {
        printf("Nem sikerult lefoglalni\n");
        return 1;
    }
    printf(" Irja be az elemeket.\n");
    int i = 0;
    while (i < meret) {
        scanf("%lf", &tomb[i]);
        i++;
    }

    for (int i = meret; i > 0;i--) {
        printf("%lf ", tomb[i - 1]);
    }
    free(tomb);
    return 0;
}*/

/*debugmalloc

int main(void) {
    char txt[] = "hello";

    char* p = malloc(strlen(txt) * sizeof(char));//strlen(txt)-vel kellene
    strcpy(p, txt);
    printf("TXT: %s\n", p);
    //free(p);

    return 0;
}*/

/*szamok visszafele-ujra
int main(void) {
    double* tomb = malloc(sizeof(double));
    if (tomb == NULL) {
        printf("Nem sikerult lefoglalni\n");
        return 1;
    }

    printf("Irja be az elemeket.\n");
    int aktualis_meret = 1;
    scanf("%lf", &tomb[aktualis_meret - 1]);

    while (tomb[aktualis_meret - 1] != -1) {
        aktualis_meret++;
        double* tmp = malloc(aktualis_meret * sizeof(double));
        if (tmp == NULL) {
            printf("Nem sikerult lefoglalni\n");
            free(tomb);
            return 1;
        }
        for (int i = 0; i < aktualis_meret - 1; i++) {
            tmp[i] = tomb[i];
        }
        scanf("%lf", &tmp[aktualis_meret - 1]);
        free(tomb);
        tomb = tmp;
    }

    for (int i = aktualis_meret - 2; i >= 0; i--) {
        printf("%.4lf ", tomb[i]);
    }
    printf("\n");

    free(tomb);
    return 0;
}*/

/*string beolvasasa
int main(void) {
    char* tomb = malloc(sizeof(char) * 2);
    if (tomb == NULL) {
        printf("Nem sikerult lefoglalni\n");
        return 1;
    }

    printf("Irja be az elemeket.\n");
    int aktualis_meret = 1;
    scanf("%c", &tomb[aktualis_meret - 1]);

    while (tomb[aktualis_meret - 1] != '\n') {
        aktualis_meret++;
        char* tmp = malloc((aktualis_meret + 1) * sizeof(char));
        if (tmp == NULL) {
            printf("Nem sikerult lefoglalni\n");
            free(tomb);
            return 1;
        }
        for (int i = 0; i < aktualis_meret - 1; i++) {
            tmp[i] = tomb[i];
        }
        scanf("%c", &tmp[aktualis_meret - 1]);
        free(tomb);
        tomb = tmp;
    }
    tomb[aktualis_meret] = '\0';

    printf("\n%s ", tomb);
    printf("\n");

    free(tomb);
    return 0;
}*/

/*hosszu_sort_olvas() fv.
char* hosszu_sort_olvas(void) {
    printf("Irja be az elemeket.\n");
    char* tomb = malloc(sizeof(char) * 2);
    if (tomb == NULL) {
        printf("Nem sikerult lefoglalni\n");
        return NULL;
    }
    int aktualis_meret = 1;
    scanf("%c", &tomb[aktualis_meret - 1]);

    while (tomb[aktualis_meret - 1] != '\n') {
        aktualis_meret++;
        char* tmp = malloc((aktualis_meret + 1) * sizeof(char));
        if (tmp == NULL) {
            printf("Nem sikerult lefoglalni\n");
            free(tomb);
            return NULL;
        }
        for (int i = 0; i < aktualis_meret - 1; i++) {
            tmp[i] = tomb[i];
        }
        scanf("%c", &tmp[aktualis_meret - 1]);
        free(tomb);
        tomb = tmp;
    }
    tomb[aktualis_meret] = '\0';
    return tomb;
}

int main(void) {

    char* tomb = hosszu_sort_olvas();
    if (tomb == NULL)
    {
        printf("Astringet nem sikerult beolvasni!");
        return 1;
    }

    printf("\n%s ", tomb);
    printf("\n");

    free(tomb);
    return 0;
}*/
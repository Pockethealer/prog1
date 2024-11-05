#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* stringet_beolvas(int n) {
    /*azert getc-t hasznalok es nem scanf-t mert a scanf nem olvas eof-ot vagy newline-t*/
    char c = getc(stdin);
    char* string;
    if (c == '\n' || c == EOF) {
        string = malloc((n + 1) * sizeof(char));
        if (string == NULL) {
            printf("Nem lehetett lefoglalni a memoriat!");
            return NULL;
        }
        string[n] = '\0';
        return string;
    }
    string = stringet_beolvas(n + 1);
    /*Hibakezeles, hogy ne legyen tulindexeles, ha nem volt semmi beolvasva vagy nem sikerult lefoglalni a memoriat.*/
    if (string == NULL) {
        printf("Nem lehetett lefoglalni a memoriat!");
        return NULL;
    }
    string[n] = c;
    return string;
}
/*Azert kell ez a fuggveny is mert a feladat egy void argumentumu fv-t kert.*/
char* sort_beolvas(void) {
    char* string = stringet_beolvas(0);
    return string;
}
int main(void) {
    printf("Irja be a beolvasando szoveget!\n");
    char* s = sort_beolvas();
    printf("A beolvasott szoveg:\n%s", s);
    free(s);
    return 0;
}
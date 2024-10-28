#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "../../src/include/debugmalloc.h"

//dinamikus string masolas
char* masolat(char* sztring) {
    int hossz = strlen(sztring) + 1;
    char* uj = malloc(hossz * sizeof(char));
    strcpy(uj, sztring);
    return uj;
}

//dinamikus string nyújtás, eredeti argumentumban csak dinamikusan 
//foglalt tomb lehet mert csak azt fogja tudni felszabaditani
char* hozzafuz(char* eredeti, char* toldalek) {
    int hossz = strlen(eredeti) + strlen(toldalek) + 1;
    char* tmp = malloc(hossz * sizeof(char));
    strcpy(tmp, eredeti);
    strcat(tmp, toldalek);
    free(eredeti);
    eredeti = tmp;
    return eredeti;
}

//reszstring kivagasa, ha az első index kisebb 0-nál, akkor a függvény 0-nak veszi; ha a második nagyobb a sztring hosszánál, 
//akkor annak veszi, visszaadja a kivagott stringre muatato pointert.
char* kivag(char* eredeti, int elso, int utolso) {
    int minindex = elso;
    int maxindex = utolso;
    if (elso < 0)
        minindex = 0;
    if (utolso > strlen(eredeti))
        maxindex = strlen(eredeti);
    char* kivagott = malloc((maxindex - minindex + 1) * sizeof(char));
    for (int i = 0;i < maxindex - minindex;i++) {
        kivagott[i] = eredeti[i + minindex];
    }
    kivagott[maxindex - minindex] = '\0';
    return kivagott;
}

//string elhagyasa, elhagyja az elso parametertol(mar nem) a stringbol a masodik parameterig(az mar benne lesz) terjedo szakaszt es visszater az uj stringgel
char* elhagy(char* eredeti, int elso, int utolso) {
    int aktualis_poz = 0;
    int hossz = strlen(eredeti) - (utolso - elso) + 1;

    char* kivagott = malloc(hossz * sizeof(char));
    for (int i = 0;eredeti[i] != '\0';i++) {
        if (i < elso || i >= utolso) {
            kivagott[aktualis_poz] = eredeti[i];
            aktualis_poz++;
        }
    }
    kivagott[hossz - 1] = '\0';
    return kivagott;
}
//beszuras
char* beszur(char* eredeti, int index, char* beszurt) {
    int aktualis_poz = 0;
    int hossz = strlen(eredeti) + strlen(beszurt) + 1;
    char* uj = malloc(hossz * sizeof(char));
    for (int i = 0;i < index;i++) {
        uj[i] = eredeti[i];
        aktualis_poz++;
    }
    for (int i = 0;beszurt[i] != '\0';i++) {
        uj[aktualis_poz] = beszurt[i];
        aktualis_poz++;
    }
    for (int i = index;i < strlen(eredeti);i++) {
        uj[aktualis_poz] = eredeti[i];
        aktualis_poz++;
    }
    uj[hossz - 1] = '\0';
    return uj;
}

int main(void) {
    //1.
    char* szoveg = masolat("alma");
    printf("%s\n", szoveg);
    //2.
    szoveg = hozzafuz(szoveg, "fa");
    printf("%s\n", szoveg);
    free(szoveg);
    //3.
    char* kivagott = kivag("hello, vilag", 5, 9);
    puts(kivagott);
    free(kivagott);
    //4.
    char* metszet = elhagy("hello, vilag", 5, 9);
    puts(metszet);
    free(metszet);
    //5.
    char* beszurt = beszur("hello!", 5, " vilag");
    puts(beszurt);
    free(beszurt);
    return 0;
}


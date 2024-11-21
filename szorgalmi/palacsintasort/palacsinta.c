#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
typedef struct LL {
    int adat;
    struct LL* next;
} LL;
void lista_felszabadit(LL* head) {
    if (head == NULL) return;
    while (head != NULL) {
        LL* next = head->next;
        free(head);
        head = next;
    }
    return;
}
LL* listat_epit(int* t, int meret) {
    if (meret <= 0) return NULL;
    LL* head = malloc(sizeof(LL));
    if (head == NULL) return NULL;
    head->adat = t[0];
    head->next = NULL;
    LL* current = head;
    for (int i = 1;i < meret;i++) {
        current->next = malloc(sizeof(LL));
        if (current->next == NULL) {
            lista_felszabadit(head);
            return NULL;
        }
        current = current->next;
        current->adat = t[i];
        current->next = NULL;
    }
    return head;
}
void listat_kiir(LL* head) {
    while (head != NULL) {
        printf("%d ", head->adat);
        head = head->next;
    }
    printf("\n");
}
/*megfordit egy lancolt listat a hosszban megadott eleme utan elvagva*/
LL* lista_fordit(LL* head, int hossz) {
    LL* eredeti = head;
    LL* megforditott = head;
    int elemszam = hossz;
    /*berakja az uj lista vegere az eredeti lista megadott eleme utani elemet*/
    while (elemszam != 0) {
        megforditott = megforditott->next;
        elemszam--;
    }
    /*gyakorlaton vett fordito algoritmus*/
    while (hossz != 0) {
        LL* atrakott = eredeti;
        LL* kovetkezo = eredeti->next;
        atrakott->next = megforditott;
        megforditott = atrakott;
        eredeti = kovetkezo;
        hossz--;
    }
    return megforditott;
}
/*kettos indirekciot hasznalok hogy ne kelljen a foprogramnak visszadni a listat*/
void palacsinta_sort(LL** head) {
    /*megszamoljuk a lista hosszat*/
    int lista_hossz = 0;
    LL* tmp = *head;
    while (tmp != NULL) {
        lista_hossz++;
        tmp = tmp->next;
    }
    for (int i = 0;i < lista_hossz - 1;i++) {
        /*megkeressuk hanyadik elem a legnagyobb*/
        int max = (*head)->adat;
        int max_hely = 1;
        LL* tmp = (*head)->next;
        for (int j = 1;j < lista_hossz - i;j++) {
            if (tmp->adat > max) {
                max = tmp->adat;
                max_hely = j + 1;
            }
            tmp = tmp->next;
        }
        /*megforditjuk a listat a legnagyobb elemnel*/
        printf("\nA(z) %d. par forditas soran:\n", i + 1);
        printf("A(z) %d a legnagyobb elem, azzal egyutt atforditva forditas utan:\n", max);
        *head = lista_fordit(*head, max_hely);
        listat_kiir(*head);
        /*megforditjuk az egeszet*/
        printf("Az egesz listat(%d. elemig) megforditva:\n", lista_hossz - i);
        *head = lista_fordit(*head, lista_hossz - i);
        listat_kiir(*head);
    }
    return;
}


int main(void) {
    int t[10] = { 5,4,11,7,9,11,19,20,3,10 };
    int meret = 10;
    LL* head = listat_epit(t, meret);
    printf("Az eredeti lista:\n");
    listat_kiir(head);
    palacsinta_sort(&head);
    lista_felszabadit(head);
    return 0;
}

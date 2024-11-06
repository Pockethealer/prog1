#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"

/*Hiba , mivel a fv csak masolatot kap az argumentumokról ezért segfault lesz.
int* f1(int i) {
    return &i;
}

int main(void) {
    int x = 10;
    int* p = f1(x);
    printf("%d\n", *p);
    printf("%d\n", *p);
    return 0;
}*/
/* megadott kód, létrehoz egy listát*/
typedef struct ListaElem {
    int adat;
    struct ListaElem* kov;
} ListaElem;


ListaElem* lista_letrehoz(void) {
    int szamok[] = { 8, 14, 13, 17, 1, 19, 16, 5, 3, 11, 2,
                     15, 9, 10, 6, 22, 4, 7, 18, 27, -1 };
    ListaElem* lis = NULL;

    for (int i = 0; szamok[i] != -1; ++i) {
        /*mindig a vegere rakja a headet*/
        ListaElem* u;
        u = (ListaElem*)malloc(sizeof(ListaElem));
        u->kov = lis;
        u->adat = szamok[i];
        lis = u;
    }
    return lis;
}

/*lista hossza*/
int lista_hossza(ListaElem* head) {
    int i = 0;
    ListaElem* c = head;
    while (c != NULL) {
        i++;
        c = c->kov;
    }
    return i;
}

void lista_felszabadit(ListaElem* head) {
    while (head != NULL)
    {
        ListaElem* tmp = head->kov;
        free(head);
        head = tmp;
    }
}

ListaElem* beszur_elore(ListaElem* head, int adat) {
    ListaElem* newhead = (ListaElem*)malloc(sizeof(ListaElem));
    newhead->kov = head;
    newhead->adat = adat;
    return newhead;
}
void beszur_hatra(ListaElem** head, int adat) {
    ListaElem* utolso = *head;
    if (utolso == NULL)
    {
        utolso = (ListaElem*)malloc(sizeof(ListaElem));
        utolso->adat = adat;
        utolso->kov = NULL;
        *head = utolso;
        return;
    }

    while (utolso->kov != NULL)
    {
        utolso = utolso->kov;
    }
    utolso->kov = (ListaElem*)malloc(sizeof(ListaElem));
    utolso->kov->adat = adat;
    utolso->kov->kov = NULL;

}
ListaElem* keres(ListaElem* head, int keresett) {
    if (head == NULL)
    {
        printf("az atadott lista ures!");
        return NULL;
    }
    ListaElem* keresett_elem = head;
    while (keresett_elem->adat != keresett)
    {
        keresett_elem = keresett_elem->kov;
    }
    return keresett_elem;
}
void lista_kiir(ListaElem* head)
{

    for (ListaElem* l = head;l != NULL; l = l->kov) {
        printf("%d ", l->adat);
    }
    printf("\n");
}

int main(void) {
    ListaElem* eleje;
    eleje = lista_letrehoz();
    /*kiírja a listát*/
    lista_kiir(eleje);
    /*megszamolja a listat*/
    printf("A lista hossza: %d\n", lista_hossza(eleje));
    /*beszúr előre*/
    eleje = beszur_elore(eleje, 22);
    lista_kiir(eleje);
    /*beszúr a végére*/
    ListaElem* newlist = NULL;
    beszur_hatra(&newlist, 99);
    beszur_hatra(&newlist, 55);
    lista_kiir(newlist);
    /*keres a listában*/
    ListaElem* k = keres(eleje, 2);
    if (k != NULL)
    {
        lista_kiir(k);
    }
    else
        printf("A keresett elem nem található!");
    /*felszabaditás*/
    lista_felszabadit(eleje);
    lista_felszabadit(newlist);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/*fibonacci O(2^n) futási idő
int fibonacci(int n) {
    if(n<2) {
        return n;
    }
   else {
       return fibonacci(n-1)+fibonacci(n-2);
   }
}
int main (void) {
    int sz=fibonacci(45);
    printf("%d",sz);
}*/

/*iterativ vs rekurziv függvény

void sztringet_kiir_1(char *szoveg) {
    if (szoveg[0] == '\0')
        return;
    putchar(szoveg[0]);
    printf("%s", szoveg + 1);
}


void sztringet_kiir_2(char *szoveg) {
    if (szoveg[0] == '\0')
        return;
    putchar(szoveg[0]);
    sztringet_kiir_2(szoveg + 1);
}


int main(void) {
    sztringet_kiir_1("alma");
    sztringet_kiir_2("\nalma");

    return 0;
}*/

/*tömb kiiratás

void elore_i(int *t, int db) {
    for(int i=0;i<db;i++) {
        printf("%d",t[i]);
    }
    printf("\n");
}

void hatra_i(int *t, int db) {
    for(int i=db-1;i>=0;i--) {
        printf("%d",t[i]);
    }
    printf("\n");
}
void elore_r(int *t, int db) {
    if (db==0) {
        return;}
    elore_r(t,db-1);
    printf("%d",t[db-1]);

}

void hatra_r(int *t, int db) {
    if (db==0) {
        printf("\n");
        return;}
    printf("%d",t[db-1]);
    hatra_r(t,db-1);
}


int main (void) {
    int elso[]={1,2,3,4,5};
    int masodik[]={1,2,3,4,5,6,7,8,9,0};
    //elore_i(elso,5);
    //elore_i(masodik,10);
    //hatra_i(elso,5);
    //hatra_i(masodik,10);
    elore_r(elso,5);
    printf("\n");
    elore_r(masodik,10);
    printf("\n");
    hatra_r(elso,5);
    hatra_r(masodik,10);
    }*/

    /*szamrendszer valto

    void szamrendszer_valto(int x, int a) {
        if(x==0)
            return;
        szamrendszer_valto(x/a,a);
        printf("%d",x%a);
    }

    int main(void) {
        szamrendszer_valto(255,2);
    }*/

    // szamjegy csoportosito

void csoport(int i)
{
    if (i == 0)
        return;
    csoport((i - (i % 1000)) / 1000);
    printf("%d ", i % 1000);
}
int main(void)
{
    csoport(999999999);
}

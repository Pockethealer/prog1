#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/* negatív számok keresése, és kiiratása
int main(void) {
    double szamok[10] = { 2.5, -69, 5.4, -8, -7.7, 6, 2.9, -10, -3, 9.8 };
    // Az eredeti tömb kiírása
    printf("Összesen %d szám van.\n", 10);
    for (int i = 0; i < 10; ++i)
        printf("[%d]=%g ", i, szamok[i]);
    printf("\n\n");
    // Negatívak indexeinek kigyűjtése
    int indexek[10];
    int counter =0;
    for (int i=0; i<10; i++) {
        if (szamok[i]< 0) {
            indexek[counter]=i;
            counter++;}}
    // Negatívak kiírása
    printf("Ebbol %d szam negativ.",counter);
    for (int i=0;i < counter;i++) {
        printf("[%d]=%g ",indexek[i],szamok[indexek[i]]);
    }
    return 0;
} */

/* fv-ek, szamok kiiratasa -1-től 1-ig tizedenként, köb, abszolút fv alkalmazása
double kob(double a);
double abszolut(double a);
int main(void) {
    for(double i=-1;i<=1;i+=0.1) {
        printf("%.4lf, %.4lf,%.4lf, %.4lf\n",i,kob(i),abszolut(i),sin(i));
    }}
double kob(double a) {
    return a*a*a;}
double abszolut(double a) {
    if (a <0) {
        return a*-1;}
    return a;}*/

/*virágnyelv nagybetűs integrálással
int maganhangzo(char c);
char kisbetu(char c);
int main(void) {
    char c;
    while (scanf("%c", &c) != EOF) {
        if (maganhangzo(kisbetu(c)))
            printf("%cv%c", c, kisbetu(c));
        else
            printf("%c", c);}
    return 0;}
int maganhangzo(char c) {
    return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u');}
char kisbetu(char c) {
    int kulonbseg='a'-'A';
    if (c=='A' || c=='E' || c=='I' || c=='O' || c=='U') {
        return c+kulonbseg;
    }
    return c;}*/

/*szakaszfelező pont koordinatai
typedef struct Pont{
    double x, y; } Pont;
int main(void){
    Pont p1={2.2,1.6};
    Pont p2;
    printf("Ird be a pont x, y kordinatait szokozzel elvalasztva:");
    scanf("%lf %lf",&p2.x,&p2.y);
    Pont p3={(p1.x+p2.x)/2, (p1.y+p2.y)/2};
    printf("Az ket pont kozotti szakaszfelezo pont koordinatai: %.2lf, %.2lf",p3.x,p3.y); }*/

/*program kiegeszites
typedef struct Datum {
    int ev, ho, nap;
} Datum;
typedef struct Versenyzo {
    char nev[31];
    Datum szuletes;
    int helyezes;
} Versenyzo;
void datum_kiir(Datum d);
void versenyzo_kiir(Versenyzo v);
int main() {
    Versenyzo versenyzok[5] = {
        { "Am Erika", {1984, 5, 6}, 1 },
        { "Break Elek", {1982, 9, 30}, 3 },
        { "Dil Emma", {1988, 8, 25}, 2 },
        { "Kasza Blanka", {1979, 6, 10}, 5 },
        { "Reset Elek", {1992, 4, 5}, 4 },
    };

    // 0-s versenyző neve - printf %s
    printf("%s",versenyzok[0].nev);
    // 2-es versenyző helyezése
    printf("\nmasodik versenyzo helyezese:%d\n",versenyzok[2].helyezes);
    // 4-es versenyző születési dátumát (írd meg a datum_kiir függvényt!)
    datum_kiir(versenyzok[4].szuletes);
    // 1-es versenyző nevének kezdőbetűjét (ne feledd, a sztring karaktertömb)
    printf("\n%c",versenyzok[1].nev[0]);
    // az 1-es versenyző dobogós-e? igen/nem, akár ?: operátorral, de egy printf-fel
    printf("\n%s",versenyzok[1].helyezes<4?"igen":"nem");
    // az 4-es versenyző gyorsabb-e, mint a 3-as versenyző?
    printf("\n%s",versenyzok[4].helyezes<versenyzok[3].helyezes?"igen":"nem");
    // az 1-es versenyző ugyanabban az évben született-e, mint a 2-es?
    printf("\n%s\n",versenyzok[1].szuletes.ev==versenyzok[2].szuletes.ev?"igen":"nem");
    // egészítsd ki a versenyzo_kiir() függvényt,aztán írd ki az 1-es versenyző összes adatát
    versenyzo_kiir(versenyzok[1]);
    // végül listázd ki az összes versenyzőt sorszámozva, összes adatukkal.
    for (int i=0;i<5;i++) {
        versenyzo_kiir(versenyzok[i]);}
    return 0;}
void datum_kiir(Datum d) {
    // dátum kiírása
    printf("%d.%d.%d",d.ev,d.ho,d.nap);}
void versenyzo_kiir(Versenyzo v) {
    // a versenyző összes adatának kiírása
    printf("%s ",v.nev);
    datum_kiir(v.szuletes);
    printf(" %d.helyezes\n",v.helyezes);}*/
/* Kezdetleges menü
int main(void) {
    int a=1;
    int b;
    do {
        b=-1;
        printf("0. Alapertek visszaallitasa (a = 1)\n"
            "1. Hozzaad 1-et\n"
            "2. Megforditja az elojelet\n"
            "3. Szorozza 2-vel\n"
            "9. Kilepes\n");
        scanf("%d",&b);
        switch (b) {
            case 0:
                a=1;
                break;
            case 1:
                a+=1;
                break;
            case 2:
                a*=-1;
                break;
            case 3:
                a*=2;
                break;
            default:
                printf("%s\n\n",b==9?"Kilepes":"Ervenytelen valasz!");
                break;}
        printf("Az a pillanatnyi erteke: %d\n\n",a);
    }while (b!=9);}*/
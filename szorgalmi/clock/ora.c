#include <stdio.h>
#include <math.h>

int main(void) {
    int hour, min, sec;
    double pi = 3.14159265358979;
    /* egy 2x*2x felbontású x,x középpontú, az egyszerűség kedvéért r=x sugarú kör,
      a sugár szabadon változtatható, az alkalmazás minden x >= r értékre működik
      (2520-100px tartományban tesztelve) */
    int x=640;
    int r=640;
    int sikeres=0;
    //feltételezzük hogy nem ad meg a felhasználó, csak egész számokat, akkor igaz a további:
    while(sikeres==0){
        printf("Kerem az idopontot 12 vagy 24 oras formatumban, szokozzel elvalasztva: ");
        scanf("%d %d %d",&hour,&min,&sec);
        //ha 24 órás formátumot használ
        if(hour>12&&hour<=24) {
            hour-=12;}
        if(hour>=0&&hour<=12&&min>=0&&min<=59&&sec>=0&&sec<=59) {
            sikeres=1;}
        else  {
            printf("Nem sikerult beolvasni.\n");}
    }
    //Ezeket lehetne printf argumentumban számolni, az átláthatóság kedvéért írtam ki külön
    //egy tört tömb deklarálása ami kifejezi hány fokot fordult a nagymutató
    double fok0=pi*2*(((double)hour*3600+min*60+sec)/43200);
    double fok1=pi*2*(((double)min*60+sec)/3600);
    double fok2=pi*2*(((double)sec)/60);

    //mutatók x kordinátájának a deklarálása
    double xmutato0=(x+(sin(fok0)*r)*0.6);
    double xmutato1=(x+(sin(fok1)*r)*0.75);
    double xmutato2=(x+(sin(fok2)*r)*0.75);

    //mutatók y kordinátájának deklarálása
    double ymutato0=(x-(cos(fok0)*r)*0.6);
    double ymutato1=(x-(cos(fok1)*r)*0.75);
    double ymutato2=(x-(cos(fok2)*r)*0.75);


    FILE* clock;
    clock = fopen("ora.svg", "w");
    //óra rajzolása
    fprintf(clock, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"black\" fill=\"white\" />\n",2*x,2*x,x,x,r);
    //mutatók rajzolása, az ora meretehez kalibralt mutato merettel
    fprintf(clock, "<line x1=\"%d\" y1=\"%d\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"%lf\" />\n",x,x,xmutato0,ymutato0,((double)r/640*7));
    fprintf(clock, "<line x1=\"%d\" y1=\"%d\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"%lf\" />\n",x,x,xmutato1,ymutato1,((double)r/640*3));
    fprintf(clock, "<line x1=\"%d\" y1=\"%d\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"%lf\" />\n",x,x,xmutato2,ymutato2,((double)r/640*1));
    //beosztások rajzolása
    for(int i=1;i<=60;i++) {
        //ez a változó szabályozza a beosztások hosszát
        double hossz=0.9;
        double szog=pi*2*(((double)i/(double)60));
        if(i%5==0) {
            hossz=0.8;
            //a +- r/20 csak esztétikai okokból van ott, jobban néznek ki a számok ha egy picit el vannak csúsztatva
            fprintf(clock,"<text x=\"%lf\" y=\"%lf\" stroke=\"black\" font-size=\"%lf\">%d</text>\n",(x+(sin(szog)*r)*0.75)-r/20,(x-(cos(szog)*r)*0.75)+r/20,(double)r*80/640,i/5);
        }

        //szintén csak az átláthatóság kedvéért van külön, és nem a printf argumentumában
        double beosztasasx1=(x+(sin(szog)*r)*hossz);
        double beosztasasx2=(x+(sin(szog)*r));
        double beosztasasy1=(x-(cos(szog)*r)*hossz);
        double beosztasasy2=(x-(cos(szog)*r));
        fprintf(clock,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"0.5\" />\n",beosztasasx1,beosztasasy1,beosztasasx2,beosztasasy2);
    }
    fprintf(clock,"</svg>");
    fclose(clock);
    return 0;
}


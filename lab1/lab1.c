#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 6. es 9. feladat

int vanegyok(int a, int b, int c);
double gyok(int a, int b, int c, int l);

int main(void)
{
    //inicializalom a valtozokat
    int a;
    int b;
    int c;
    //bekerem az egyutthatokat
    printf("Adja meg az egyutthatokat\n");
    scanf("%i", &a);
    scanf("%i", &b);
    scanf("%i", &c);
    //evalualom a gyokoket
    int l= vanegyok(a,b,c);
    //meghivom a megoldo fv-t
    gyok(a,b,c,l);
    return 0;
    }



//fuggveny a gyokokre
int vanegyok(int a,int b,int c)
{
    if (b*b>4*a*c){
        printf("\nVan ket valos gyoke.");
        return 2;
        }
    if (b*b==4*a*c){
        printf("\nVan egy valos gyoke.");
        return 1;
        }
    else{
        printf("\nNincs valos gyoke.");
        return 0;
        }
}

// fv. a masodfoku megoldokeplettel, l a gyokok szama
double gyok(int a, int b, int c, int l){
    if (l>1){
        double g[2];
        g[0]= (((-1)*b) + sqrt((b*b-4*a*c)))/(2*a);
        g[1]= (((-1)*b) - sqrt((b*b-4*a*c)))/(2*a);
        printf("egyik gyok: %lf, masik gyok %lf.",g[0],g[1]);
    }
    if (l==1){
        double g;
        g = ((-1)*b)/(2*a);
        printf("a gyok: %lf",g);
    }
    return 0;
}
*/

/* feladat8

int main(void){
    int n;
    printf("Adja meg a vonal hosszat\n");
    scanf("%i", &n);
    printf("+");
    for (int i = 0; i < n; i++){
        printf("-");
    }
    printf("+");


}


gyakorlo faladatok */

/* pelda1

int main(void){
    double a,b,c;
    printf("Adjon meg 3 valos szamot vesszovel elvalasztva:\n");
    scanf("%lf,%lf,%lf", &a,&b,&c);
    //printf("%lf,%lf,%lf",a,b,c);
    //kulonbseget szamol
    if (a<0)
        printf("Az elso szam negativ");
    else
        printf("Az elso szam nem negativ");
    while(a<c){
        printf("%lf ",a);
        a=a+b;
    }
}
*/
/* pelda2

int main(void){
    double a,b;
    printf("Adjon meg 2 valos szamot vesszovel elvalasztva:\n");
    scanf("%lf,%lf", &a,&b);
    int i=0;
    if((a-b)>1||(a-b)<-1){
    while(a>b-i){
        printf("%lf ",b);
        i++;
        b=b+i;

    }
    while(a<b){
        printf("%lf ",a);
        i++;
        a=a+i;
    }
    }
    else if(a>b)
        printf("%lf",a);
    else
        printf("%lf", b);

}
*/
/*
negyzet rajzolo
int main(void){
    //negyzet oldala a
    int a;
    printf("Adja meg a negyzet oldalat, pozitiv egesz szamkent:");
    scanf("%i",&a);


    //negyzet vertikalis loopja
    for (int i=0; i<a; i++){
        //negyzet teteje meg alja
        if (i==0||i==a-1){
            //negyzet bal sarkai
            printf("+");
            //teteje meg alja
            for (int i=0;i<a;i++){
                printf("-");
            }
            //jobb sarok
            printf("+\n");
        }
        //negyzet oldala-horizontalis loop
        else{
        printf("|");
        for(int i=0; i<a;i++){
            printf(" ");
        }
        printf("|\n");
        }

    }

}
*/

//sakktabla
/*
int main(void){
    int a;
    printf("Adja meg a negyzet oldalat, pozitiv egesz szamkent:");
    scanf("%i",&a);
    //sakk tabla vertikalis loop, fele akkora mert kettesevel mennek a sorok
    for(int i=0;i<a*2;i++){
        //horizontalis ketteagazik a foylamat
        if(i%2==0){
                //kettesevel csinalja a sorokat
                for(int x=0;x<2;x++){
                    printf("\n");
                    for(int i=0;i<a*2;i++){
                            //kiiratja a pontokat az adott 2 sorban
                        if (i%2==0){
                            printf("**");
                        }
                        else{
                            printf("..");
                        }}}
                    }
        if(i%2==1){
                for(int x=0;x<2;x++){
                    printf("\n");
                    for(int i=0;i<a*2;i++){
                        if (i%2==1){
                            printf("**");
                        }
                        else{
                            printf("..");
                            }
                    }
                    }
        }
    }
}
*/
//


















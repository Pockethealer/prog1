#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/*
void func1(int i2) {
    i2 *= 2;
    printf("func1()... i2 = %d\n", i2);     // 4 i1 =5, i2 lokalis valtozo, az erteke 10
}

void func2(int *p3) {
    *p3 *= 2;
    printf("func2()... *p3 = %d\n", *p3);
    p3 = NULL;                              // 5, az i1 erteke 10 lesz, 6, az i erteke 20 lesz
    printf("func2()... p3 = %p\n", (void*)p3);
}

int main(void) {
    int i1 = 2;
    int *p1 = NULL;
    int *p2 = NULL;
    printf("Hova mutat p1 es p2?\n");       // 1,  van egy i valtozo,aminek az erteke 2, és 2 null pointer

    p1 = &i1;
    printf("&i1 = %p, p1 = %p\n", (void*)&i1, (void*)p1);
    printf("i1 = %d, *p1 = %d\n", i1, *p1); // 2, p valtozo az i1-re mutat a p2 nullpointer

    i1 = 3;  printf("*p1 = %d\n", *p1);
    *p1 = 4; printf("i1 = %d\n", i1);

    p2 = p1;
    *p2 = 5;
    printf("i1 = %d, p2 = %p\n", i1, (void*)p2);   // 3 i1=5
    printf("-----\n");

    func1(i1);
    printf("main()... i1 = %d - de miert?\n", i1);
    printf("-----\n");

    func2(&i1);
    printf("main()... i1 = %d - miert?\n", i1);
    printf("-----\n");

    func2(p2);
    printf("main()... i1 = %d - miert?\n", i1);
    printf("main()... p2 = %p - miert?\n", (void*)p2);

    return 0;
}*/
/* felulet szamito
void kocka(double x,double *a,double *v) {
    *a=x*x*6;
    *v=x*x*x;}
int main (void) {
    double a,v;
    kocka(2.7,&a,&v);
    printf(" felulet:%f, terfogat:%f",a,v);
}*/
/*tömb fv
int *indexe(int *a,int m,int v) {
    //int i;
    //for(i=0;i<m;++i) {
        //if (a[i]==v)
            //return i;}
    for (int *p=a;p<a+m;++p) {
        if (*p==v)
            return p;
    }
    return NULL;}

int main(void) {
    int a[7]={2,54,3,4,5,6,11};
    for(int i=0;i<7;++i)
        printf("[%d]=%d",i,a[i]);
    int v=4;
    int *pi= indexe(a,7,v);
    if (pi!=NULL)
        printf("\na keresett elem:%d indexe:%lld, memoriacime:%p",v,pi-a,(void*)pi);
    else
        printf("\na keresett elem nem talalhato");
    return 0;
}*/
/*nev kiiras
int main(void) {
    char c[50];
    printf("irjon be egy nevet:");
    scanf("%s",c);
    for(int i=0;c[i]!='\0';++i)
        printf("\n%c",c[i]);
}*/
void trim(char *cel,char *forras) {
    int elso=-1, utolso=-1;
    //megkeressuk azelso es utolso space-t
    for(int i=0;forras[i]!='\0';++i) {
        if (forras[i]!=' ') {
            if(elso==-1){elso=i;}
            utolso=i;}}
    //lemasoljuk a stringet
    int counter=0;
    //printf("elso:%d, utolso: %d karakter\n",elso,utolso);
    for(int i=elso;i<=utolso;++i) {
        if (forras[i]!=' '||(i>elso&&i<utolso)){
            cel[counter]=forras[i];
            counter++;}}
    cel[counter]='\0';}
int main (void) {
    char a[]=" ez egy string  !      ";
    char b[50];
    trim(b,a);
    printf("az a szoveg:%s.",a);
    printf("\na b szoveg:%s.",b);
}
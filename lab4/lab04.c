#include <stdio.h>
#include <math.h>
#include <stdio.h>
/*lebegőpontos számok
int main(void) {
    printf("1. %f\n", 1.23456789123456789123456789e40);
    printf("2. %g\n", 1e40);
    printf("3. %s\n", 1e3+1 == 1e3 ? "igaz" : "hamis");
    printf("4. %s\n", 1e30+1 == 1e30 ? "igaz" : "hamis");
    printf("5. %g\n", pow(10, 40) / pow(10, -40));
    printf("6. %g\n", powf(10, 40) / powf(10, -40));

    return 0;
}*/
/*emeletes tört
int main(void) {
    printf("%.6lf",(4+2-(3-(6+4/5.0)))/(3*(2-7)));
    return 0;
}
*/
/*int overflow -2^31, -2^15, -2^8
int main(void) {
    int i = 1;
    while (i > 0) {
        ++i;
    }
    printf("%d\n", i);

    return 0;
}*/
/*léptetéses hatványok, bitszámolás
int main(void) {
    int szamlalo = 0;
    for (short int i = 1; i > 0; i<<=1) {
        printf("%d: %10d\n", szamlalo, i);
        szamlalo++;
    }
    printf(" az adott tipus %d bites", szamlalo);
    return 0;
}*/
/*egy szam bitjei
int main(void) {
    unsigned long int a;
    printf("Adjon meg egy szamot:");
    while (scanf("%li",&a)==1) {
        for(int i =31;i>=0;i--) {
            printf("%i",a & 1<<i?1:0);
        }
        printf("\n");
    }return 0;
}*/
/*bitek titkai
int main(void) {
    unsigned long szamok[8] = { 0U, 1931988508U, 581177634U, 581374240U,
                            581177632U, 581177634U, 1919159836U, 0U };
    for(int j=0; j<8; j++) {
        for(int i =31;i>=0;i--) {
            //szamok[j] = szamok[j] & 65535;
            //szamok[j] = szamok[j] & ~65535;
            //szamok[j] = szamok[j] | 65535;
            //szamok[j] = szamok[j] | ~65535;
            //szamok[j] = szamok[j] ^ 65535;
            //szamok[j] = szamok[j] ^ ~65535;
            printf("%s",szamok[j] & 1<<i?"#":" ");
        }
        printf("\n");
}return 0;}*/
//rajzolás
int rajzol(unsigned long szamok);
int xetrak(unsigned long szamok, int x);
int main(void) {
    int menu;
    unsigned long szamok[24];
    for(int i =0;i<24;i++){
        szamok[i]=0;
}
    printf("Mit tegyek?\n");
    do{
        printf("Mit csinaljak?\n"
               "1:rajzol egy #-t egy tetszoleges korinatara\n"
               "2:letorli a tablat\n"
               "3: kirajzolja a tablat\n"
               "4: kilepes\n"
               "5: poharat rajzol\n");
        scanf("%d",&menu);
        switch(menu){
            case 1:
                int x,y;
                printf("Milyen kordinatakra rakjam?(32x24)");
                scanf("%d %d",&x,&y);
                szamok[y]=xetrak(szamok[y], x);
                break;
            case 2:
                for(int i =0;i<24;i++){
                szamok[i]=0;
                }
                break;
            case 3:
                for(int j=0;j<24;j++) {
                    rajzol(szamok[j]);
                    printf("\n");}
                break;
            case 4:
                printf("kilepes");
                break;
            case 5:
                for (int i=4;i<= 10;i++) {
                    szamok[i]=xetrak(szamok[i],12);
                    szamok[i]=xetrak(szamok[i],20);
                    szamok[i+6]=xetrak(szamok[i+6],16);
                }
                for(int i=8; i<25;i++) {
                    szamok[16]=xetrak(szamok[16],i);
                }
                break;
            default:
                printf("Ervenytelen valasz");
                break;
        }
    }while(menu!=4);
}
int rajzol(unsigned long szamok) {
    for(int i =31;i>=0;i--) {
        printf("%s",szamok & 1<<i?"#":" ");
    }
    return 0;
}
int xetrak(unsigned long szamok, int x) {
    return szamok|= 1<<(32-x);
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/*szamok szorzata


int main()
{
    int n = 1;
    int szorzat = 1;
    while(n<=8){
        szorzat*=n;
        n++;
    }
    printf("Szorzat erteke %i\n", szorzat);
    return 0;
}
*/

/*nyomkovetes tesztelese: 6720 a szorzat erteke amikor az n 3-ra valt

int main() {
    int szorzat = 1;
    int n = 8;
    while (n > 1) {
        szorzat *= n;
        n -= 1;
    }
    printf("%d\n", szorzat);
    return 0;
}
*/

/*euklideszi algoritmus b=44 amikor a 374-re valt

int main() {
    int a = 11220;
    int b = 2002;
    while (b > 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    printf("lnko = %d\n", a);
    return 0;
}
*/
/*karakterkodok, kiirja a begepelt karaktereket es az ascii kodjukat, eof=scanf fv. 0-at fog visszaadni


int main(void) {
    char betu;
    while (scanf("%c", &betu) == 1)
        printf("betu='%c', betu=%d\n", betu, betu);

    return 0;
}
*/

/*tulindexeles, tulindexelt akrakterek helyett memoriaszemetet ad vissza a progi, while(true)-val kiprobalva

int main(void) {
    int tomb[10];

    for (int i = 0; i < 10; i += 1)
        tomb[i] = i * 10;

    int i = 0;
    while (true) {
        printf("%d. elem: %d\n", i, tomb[i]);
        i += 1;
    }

    return 0;
}
*/
/* min kereses
int main(void){

    int tomb[10]={11,2,3,4,2,6,7,8,9,1};
    int legkissebb=tomb[0];
    int minhely;
    printf("A tomb:");
    for(int i=0; i<10;i++){
        printf(" [%i]=%i",i,tomb[i]);
        if(tomb[i]<legkissebb){
            legkissebb=tomb[i];
            minhely=i;
        }
    }
    printf("\nA legkisebb szam: %i", legkissebb);
    printf("\nA legkisebb indexe: %i", minhely);
    return 0;
}
*/
/* legkisebb kereses, kiirva a minimum utan hogy min
int main(void){

    int tomb[10]={11,2,3,4,2,6,7,2,9,10};
    int legkissebb=tomb[0];
    int minhely;
    printf("A tomb:");
    for(int i=0; i<10;i++){
        if(tomb[i]<legkissebb){
            legkissebb=tomb[i];
            minhely=i;
        }
    }
    for(int i=0; i<10;i++){
        printf(" %i",tomb[i]);
        if(tomb[i]==legkissebb){
            printf("[MIN]");
        }
    }
    printf("\nA legkisebb szam: %i", legkissebb);
    printf("\nA legkisebb indexe: %i", minhely);
    return 0;
}
*/

/* pitagorasz nevenek kiirasa eltolva
int main(void){
    //alap tomb
    char p[10]={'P','i','t','a','g','o','r','a','s','z'};
    //soronkenti ciklus
    for(int i=0;i<10;i++){
        //kiiras a sorban
        for(int j=0;j<10;j++){
            //ideiglenes tomb a betuk megvaltozott helyzetenek tarolasara
            char x[10];
            //uj pozicio
            int temp =(j+i)%10;
            x[j]=p[temp];
            //kiiras
            printf("%c ",x[j]);
            }
            printf("\n");
        }
return 0;
}
*/






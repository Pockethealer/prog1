#include <stdio.h>
#include <stdbool.h>
/*nem hasznaltam kulon fuggvenyeket, mivel nem tanultuk meg hogyan kell
 *tomboket atadni fuggvenyargumentumba, ezert csak bonyolitotta volna a kodot.*/
int main(void)
{   /*szalag és szalag pozicio definialasa, majd feltoltese 0-val*/
    char szalag[32768];
    for (int i = 0; i < 32768; i++){szalag[i]=0;}
    int szalpoz=0;
    /*programkod es a programkodon beluli pozicio deklarálása
     *haromszog*/
    char programkod[] =
            "[ThisprogramkodprintsSierpinskitriangleon80-columndisplay.]>"
            "++++[<++++++++>-]>++++++++[>++++<-]>>++>>>+>>>+<<<<<<<<<<"
            "[-[->+<]>[-<+>>>.<<]>>>[[->++++++"
            "++[>++++<-]>.<<[->+<]+>[->++++++++++<<+>]>.[-]>]]+<<<"
            "[-[->+<]+>[-<+>>>-[->+<]++>[-<-"
            ">]<<<]<<<<]++++++++++.+++.[-]<]+++++*****Made*By:*NYYRIKKI*2002*****";
    /*program ami kitorli a space-eket a szovegbol
     *valamiert az eofnak uj sorban kell lennie hogy rendesen erzekelje es atatodjon a programnak*/
    /*char programkod[]= ",beker egy szamot torli az elso harom cellat+[->[-]>[-]<<"
                       "atmasolja a melette levo harom cellaba[>+>+<<-]"
                       "feltolti az elso cellat 32re ++++++++++++++++++++++++++++++++"
                       "kivon a masodikbol 32t[>-<-]>"
                       "ha a masodik nulla akkor nem irja ki ha nem nulla "
                       "akkor ugrik jobbra es kiirja majd nullaz[>.[-]<[-]]"
                       "ugrik vissza ker masik szamot<,+]";*/
    int progpoz=0;
    /*szintaktikai hibak elkerulesere*/
    bool helyes=1;
    /*a c nem enged switch case utan declaralni valtozot*/
    int ciklusszam2;
    int ciklusszam;
    while (programkod[progpoz]!='\0' && helyes){
        switch (programkod[progpoz])
        {
            case '<':
                if (szalpoz==0) {
                    printf("\nA programkod leter a szalagrol lefele");
                    helyes=0;
                    break;}
                szalpoz--;
                progpoz++;
                break;
            case '>':
                if (szalpoz==32767) {
                    printf("\nA programkod leter a szalagrol felfele");
                    helyes=0;
                    break;}
                szalpoz++;
                progpoz++;
                break;
            case '.':
                printf("%c",szalag[szalpoz]);
                progpoz++;
                break;
            case '+':
                szalag[szalpoz]++;
                progpoz++;
                break;
            case '-':
                szalag[szalpoz]--;
                progpoz++;
                break;
            case ',':
                    if (scanf("%c", &szalag[szalpoz]) != 1) {
                        szalag[szalpoz] = -1;
                    }
                progpoz++;
                break;
            /*a ciklusszam valtozot a beagyazott ciklusok kezelesere hoztam letre.*/
            case '[':;
                ciklusszam=1;
                if (szalag[szalpoz]==0) {
                    while (ciklusszam!=0) {
                        if(programkod[progpoz+1]=='['){ciklusszam++;}
                        if(programkod[progpoz+1]==']'){ciklusszam--;}
                        if(progpoz==32767) {
                            helyes=0;
                            printf("Szintaktikai hiba.Paratlan [.");
                            ciklusszam=0;}
                        progpoz++;}}
                progpoz++;
                break;
            case ']':;
                    ciklusszam2=1;
                    while (ciklusszam2!=0) {
                        if (programkod[progpoz-1]==']'){ciklusszam2++;}
                        if (programkod[progpoz-1]=='['){ciklusszam2--;}
                        if(progpoz==0) {
                            helyes=0;
                            printf("Szintaktikai hiba. Paratlan ].");
                            ciklusszam2=0;}
                        progpoz--;

                    }
                    break;
            default:
                progpoz++;
                break;}}
    return 0;}

#include <stdio.h>

int main(void) {

    typedef enum LyAllapot {
        alap, l_volt, ll_volt
    } LyAllapot;

    LyAllapot all;
    printf("Ird be az atalakitando szoveget:\n");
    int szaml, c;
    szaml = 0;
    all = alap;
    while ((c = getchar()) != EOF && c != '\n') {
        switch (all) {
        case alap:
            if (c == 'l') all = l_volt;
            else printf("%c", c);
            break;

        case l_volt:
            switch (c) {
            case 'l': all = ll_volt; break;
            case 'y':
                szaml += 1;
                all = alap;
                printf("j");
                break;
            default:
                all = alap;
                printf("l%c", c);
                break;
            }
            break;

        case ll_volt:
            switch (c) {
            case 'l':
                printf("l");
                break;
            case 'y':
                szaml += 2;
                all = alap;
                printf("jj");
                break;
            default:
                all = alap;
                printf("ll%c");
                break;
            }
            break;
        }
    }

    printf("\n%d darab volt.\n", szaml);

    return 0;
}
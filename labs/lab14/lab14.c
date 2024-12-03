#include <stdio.h>
#include <stdlib.h>
typedef struct Cord {
    int x, y;
}Cord;
typedef enum irany { jobb, bal, fel, le }irany;
typedef enum lehet { ures, fal, kijarat, kincs };

void rajzol(char s[10][11]) {
    for (int i = 0; i < 10;i++) {
        printf("%s\n", s[i]);
    }
    return;
}
Cord pcord(char s[10][11]) {
    for (int i = 0; i < 10;i++) {
        for (int j = 0; j < 10;j++) {
            if (s[i][j] == '@') {
                Cord c;
                c.y = i;
                c.x = j;
                return c;
            }
        }
    }
}
int kincseksz(char s[10][11]) {
    int k = 0;
    for (int i = 0; i < 10;i++) {
        for (int j = 0; j < 10;j++) {
            if (s[i][j] == '$') {
                k++;
            }
        }
    }
    return k;
}
int mehet_e(char s[10][11], irany i) {
    Cord c = pcord(s);
    switch (i)
    {
    case jobb:
        if (s[c.y][c.x + 1] == '#') return 0;
        else return 1;
    case bal:
        if (s[c.y][c.x - 1] == '#') return 0;
        else return 1;
    case fel:
        if (s[c.y + 1][c.x] == '#') return 0;
        else return 1;
    case le:
        if (s[c.y - 1][c.x] == '#') return 0;
        else return 1;
    }
}
int leptet(char s[10][11], irany i) {
    Cord c = pcord(s);
    char uj;
    switch (i)
    {
    case jobb:
        uj = s[c.y][c.x + 1];
        if (mehet_e(s, i)) {

            s[c.y][c.x + 1] = '@';
            s[c.y][c.x] = ' ';
            if (uj == '$') return kincs;
            c = pcord(s);
            if (c.x == 9 || c.x == 0 || c.y == 9 || c.y == 0) return kijarat;
            return ures;
        }
        else return fal;

    case bal:
        uj = s[c.y][c.x - 1];
        if (mehet_e(s, i)) {

            s[c.y][c.x - 1] = '@';
            s[c.y][c.x] = ' ';
            if (uj == '$') return kincs;
            c = pcord(s);
            if (c.x == 9 || c.x == 0 || c.y == 9 || c.y == 0) return kijarat;
            return ures;
        }
        else return fal;

    case fel:
        uj = s[c.y + 1][c.x];
        if (mehet_e(s, i)) {

            s[c.y + 1][c.x] = '@';
            s[c.y][c.x] = ' ';
            if (uj == '$') return kincs;
            c = pcord(s);
            if (c.x == 9 || c.x == 0 || c.y == 9 || c.y == 0) return kijarat;
            return ures;
        }
        else return fal;

    case le:
        uj = s[c.y - 1][c.x];
        if (mehet_e(s, i)) {

            s[c.y - 1][c.x] = '@';
            s[c.y][c.x] = ' ';
            if (uj == '$') return kincs;
            c = pcord(s);
            if (c.x == 9 || c.x == 0 || c.y == 9 || c.y == 0) return kijarat;
            return ures;
        }
        else return fal;
    }
}

int main(void) {
    int kincsek = 0;
    char s[10][11] = {
        "###### ###",
        "#$   #   #",
        "#### ### #",
        "#        #",
        "# #### ###",
        "# #    #$#",
        "# ##$# # #",
        "#@ ### # #",
        "#   $#   #",
        "##########" };
    int ossz_k = kincseksz(s);


    int i;
    int e = 0;
    do {
        printf("Merre menjen?\n");
        scanf("%i", &i);
        e = leptet(s, i);
        if (e == fal) printf("Arra nem lephetsz!\n");
        if (e == kincs) kincsek++;
        rajzol(s);
    } while (e != kijarat);
    if (kincsek < ossz_k)
    {
        printf("Vesztettel!\n");
    }
    else printf("NYertel!\n");

    return 0;
}
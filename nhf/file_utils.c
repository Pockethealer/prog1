/**
 * @file file_utils.c
 * @brief Ebben a modulban kaptak helyet a filokból beolvasó illetve azokba kiíró fv-k,
 * illetve az általánosan használt stdin/stdout olvasó író fv-ek.
 * @date 2024-11-08
 */
#include "debugmalloc.h"
#include "file_utils.h"
 /**
  * @brief Kap egy receptek structot és egy stringet és megnézi hogy a string egyezik e valamely r.etelek.nev stringgel
  * elvileg case független, de mivel utf karakterek ezért néha bugos, az esetek 99%ában működik.
  * @param r receptek struct
  * @param etel_neve keresett string
  * @return int Visszatér a keresett elem tömbbeli indexével plusz 1(i+1-el), vagy nullával ha nem található
 (azért kell az i+1 hogy a 0. elemet is helyesen kezelje).
  */
int recept_letezik(Receptkonyv* r, const char* etel_neve) {
    if (r == NULL)
    {
        printf("A receptkönyv üres!");
        return 0;
    }

    for (int i = 0; i < r->etelek_szama; i++)
    {
        if (strcasecmp(r->etelek[i].nev, etel_neve) == 0)
        {
            return i + 1;
        }
    }
    return 0;
}
/**
 * @brief Elmenti a kapott r struktúrát az előre megadott formátumban a kapott paraméter nevű fileba, ha nem létezik létrehozza a program gyökérkönyvtárába
 * @param r Receptkönyv amit menteni szeretnénk
 * @param f A file neve, amibe menti
 */
void receptet_fileba_ment(Receptkonyv* r, char* file)
{
    if (r == NULL)
    {
        printf("Nincs adat a receptkonyvben!\n");
        return;
    }

    FILE* f = fopen(file, "w");
    if (f == NULL)
    {
        printf("Nem lehet megnyitni a fájlt írásra.\n");
        return;
    }
    fprintf(f, "%d\n", r->etelek_szama);

    for (int i = 0; i < r->etelek_szama; i++)
    {
        Etel* etel = &r->etelek[i];

        fprintf(f, "%s,%d\n", etel->nev, etel->osszetevok_szama);

        for (int j = 0; j < etel->osszetevok_szama; j++)
        {
            Osszetevo* osszetevo = &etel->osszetevok[j];
            fprintf(f, "%s,%s,%.2lf\n", osszetevo->nev, osszetevo->tipus, osszetevo->mennyiseg);
        }
        fprintf(f, "%s\n", etel->elkeszites);
    }
    fclose(f);
}
/**
 * @brief beolvassa a recepteket az előre megadott receptek.txt fileból az r receptkönyv struktúrába
 * a működése egyszerű csak felbloatolja egy rakás hibakezelés.
 * @param f A kapott filenév ahonnan beolvas
 * @return Receptkonyv*
 */
Receptkonyv* receptek_beolvas(char* file)
{
    Receptkonyv* r = (Receptkonyv*)malloc(sizeof(Receptkonyv));
    if (r == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        return NULL;
    }
    FILE* f = fopen(file, "r");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni a %s file-t!\n", file);
        free(r);
        return NULL;
    }
    if (fscanf(f, "%d", &(r->etelek_szama)) != 1 || r->etelek_szama <= 0)
    {
        printf("Hibás a %s file tartalma, az első sorba az ételek száma kell hogy kerüljön.\n", file);
        free(r);
        fclose(f);
        return NULL;
    }
    r->etelek = (Etel*)malloc((r->etelek_szama) * sizeof(Etel));
    if (r->etelek == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        free(r);
        fclose(f);
        return NULL;
    }
    for (int i = 0; i < r->etelek_szama; i++)
    {
        if (fscanf(f, " %[^,],%d", r->etelek[i].nev, &(r->etelek[i].osszetevok_szama)) != 2)
        {
            printf("Hibás a receptek.txt file tartalma, nem sikerült az összes receptet beolvasni, csak %d db-ot!", i + 1);

            r->etelek_szama = i;
            r->etelek = (Etel*)realloc(r->etelek, r->etelek_szama * sizeof(Etel));

            fclose(f);
            return r;
        }
        r->etelek[i].osszetevok = (Osszetevo*)malloc(r->etelek[i].osszetevok_szama * sizeof(Osszetevo));
        if (r->etelek[i].osszetevok == NULL)
        {
            printf("Nem lehetett lefoglalni a memoriat!\n");
            for (int j = 0; j < i; j++)
            {
                free(r->etelek[j].osszetevok);
            }
            free(r->etelek);
            fclose(f);
            free(r);
            return NULL;
        }
        for (int j = 0; j < r->etelek[i].osszetevok_szama; j++)
        {
            if (fscanf(f, " %[^,], %[^,],%lf",
                r->etelek[i].osszetevok[j].nev,
                r->etelek[i].osszetevok[j].tipus,
                &r->etelek[i].osszetevok[j].mennyiseg) != 3)
            {
                r->etelek[i].osszetevok_szama = j;
                r->etelek[i].osszetevok = (Osszetevo*)realloc(r->etelek[i].osszetevok, r->etelek->osszetevok_szama * sizeof(Osszetevo));

            }
        }
        fscanf(f, " %[^\n]", r->etelek[i].elkeszites);
    }
    fclose(f);
    return r;
}
/**
 * @brief felszabadítja a kapott r struktúrát és minden alstruktúráját
 * @param r
 */
void receptkonyv_felszabadit(Receptkonyv* r)
{
    if (r == NULL)
    {
        return;
    }
    for (int i = 0; i < r->etelek_szama; i++)
    {
        free(r->etelek[i].osszetevok);
    }
    free(r->etelek);
    free(r);
}
/**
 * @brief Kiírja az adott étel struktura adatait(név összetevők elkészítés)
 * @param m Az étel struktúra amit ki akarunk írni.
 */
void recept_kiir(Etel* m) {
    if (m == NULL)
    {
        printf("Null pointert adott meg az étel kiíráshoz!\n");
        return;
    }
    printf("Az étel neve: "COLOR_RED COLOR_UNDERLINE BG_BLACK"%s"COLOR_RESET"\n", m->nev);
    printf("Az étel összetevőinek száma: %d\n", m->osszetevok_szama);
    for (int i = 0;i < m->osszetevok_szama;i++) {
        printf("Az %d. összetevő: "COLOR_GREEN"%s"COLOR_RESET", mennyisége: "COLOR_CYAN"%.1lf"COLOR_RESET"(%s).\n",
            i + 1, m->osszetevok[i].nev, m->osszetevok[i].mennyiseg, m->osszetevok[i].tipus);
    }
    printf("Az Étel elkészítése:\n"COLOR_BLUE COLOR_UNDERLINE"%s"COLOR_RESET, m->elkeszites);
    return;
}

/**
 * @brief Kap egy egyedi osszetevok structot és egy stringet és megnézi hogy a string egyezik-e valamely r.osszetevok.nev stringgel
 * elvileg case független, de mivel utf karakterek ezért néha bugos, az esetek 99%ában működik.
 * @param e Az összetevőket tartalmazó struktúra.
 * @param osszetevo_neve Keresett string.
 * @return int Visszatér a keresett elem tömbbeli poziciójával+1el, vagy nullával ha nem található.
 */
int osszetevo_letezik(Egyedi_osszetevok* e, const char* osszetevo_neve)
{
    if (e == NULL)
    {
        printf("Az összetevők listája üres!");
        return 0;
    }
    /*Megnézi hogy az adott összetevő létezik-e, és visszatér az elem sorszámával, vigyázat egyel nagyobb mint az index*/
    for (int i = 0; i < e->egyedi_osszetevok_szama; i++)
    {
        if (strcasecmp(e->egyedi_osszetevok[i].nev, osszetevo_neve) == 0)
        {
            return i + 1;
        }
    }
    return 0;
}
/**
 * @brief Felszabadítja a kapott e struktúrát és minden alstruktúráját.
 * @param e
 */
void egyedi_osszetevo_felszabadit(Egyedi_osszetevok* e)
{
    {
        if (e == NULL)
        {
            //printf("Üres az összetevők tartalma, nem lehet mit felszabadítani!\n");
            return;
        }
        free(e->egyedi_osszetevok);
        free(e);
    }
}
/**
 * @brief Beolvassa az összetevőket az előre megadott osszetevok.txt fileból az e egyedi összetevők tömbbe.
 * @return Egyedi_osszetevok*
 */
Egyedi_osszetevok* osszetevo_beolvas(void)
{
    Egyedi_osszetevok* e = (Egyedi_osszetevok*)malloc(sizeof(Egyedi_osszetevok));
    if (e == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        return NULL;
    }
    FILE* f;
    f = fopen("osszetevok.txt", "r");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni az összetevők file-t!\n");
        free(e);
        return NULL;
    }
    fscanf(f, " %d", &(e->egyedi_osszetevok_szama));
    e->egyedi_osszetevok = (Osszetevo*)malloc(e->egyedi_osszetevok_szama * sizeof(Osszetevo));
    if (e->egyedi_osszetevok == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        fclose(f);
        free(e);
        return NULL;
    }
    for (int i = 0; i < e->egyedi_osszetevok_szama; i++)
    {
        e->egyedi_osszetevok[i].nev[51] = 0;
        e->egyedi_osszetevok[i].tipus[51] = 0;
        if (fscanf(f, " %[^,], %[^\n]", e->egyedi_osszetevok[i].nev, e->egyedi_osszetevok[i].tipus) != 2)
        {
            e->egyedi_osszetevok_szama = i;
            e->egyedi_osszetevok = (Osszetevo*)realloc(e->egyedi_osszetevok, e->egyedi_osszetevok_szama * sizeof(Osszetevo));
        }
    }

    fclose(f);
    return e;
}
/**
 * @brief Összefésüli az e struktúrában található összetevőket a receptkönyv struktúra ételeinek az összetevőivel,
 * hogy az egyedi összetevő struktúra pontosan egyszer tartalmazzon minden összetevőt, majd elmenti azt
 * az előre megadott formátumban az osszetevok.txt fileba, ha nem létezik létrehozza a program gyökérkönyvtárába.
 * @param e
 * @param r
 */
void osszetevo_fileba_ment(Egyedi_osszetevok* e, Receptkonyv* r)
{
    if (e == NULL)
    {
        printf("Üres az összetevők listája!\n");
        return;
    }
    FILE* f = fopen("osszetevok.txt", "w");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni a file-t!\n");
        return;
    }
    if (r != NULL) {
        /*Végigmegy a receptkönyvben levő összetevőkön és ellenőrzi hogy tartalmazza-e már
        *őket az összetevők listája ha nem akkor hozzáadja, lassú a realloc ezért érdemes ezt kevésszer futtatni, mondjuk csak program zárásakor*/
        for (int i = 0; i < r->etelek_szama; i++)
        {
            Etel* etel = &(r->etelek[i]);
            for (int j = 0; j < etel->osszetevok_szama; j++)
            {
                Osszetevo* osszetevo = &(etel->osszetevok[j]);
                if (!osszetevo_letezik(e, osszetevo->nev))
                {
                    e->egyedi_osszetevok_szama++;
                    e->egyedi_osszetevok = realloc(e->egyedi_osszetevok, e->egyedi_osszetevok_szama * sizeof(Osszetevo));
                    if (e->egyedi_osszetevok == NULL)
                    {
                        printf("Nem sikerült a memória bővítése az összetevőknek!\n");
                        fclose(f);
                        return;
                    }
                    strcpy(e->egyedi_osszetevok[e->egyedi_osszetevok_szama - 1].nev, osszetevo->nev);
                    strcpy(e->egyedi_osszetevok[e->egyedi_osszetevok_szama - 1].tipus, osszetevo->tipus);
                }
            }
        }
    }
    /*kiírjuk a fileba az összetevők számát*/
    fprintf(f, "%d\n", e->egyedi_osszetevok_szama);
    /*fileba írjuk a már létező öszetevőket*/
    for (int i = 0; i < e->egyedi_osszetevok_szama; i++)
    {
        fprintf(f, "%s,%s\n", e->egyedi_osszetevok[i].nev, e->egyedi_osszetevok[i].tipus);
    }
    fclose(f);
}

/**
 * @brief windows-os bohóckodás utf-8-as beolvasáshoz, elvileg működik,
 * 3 különböző verziójú windowson néztem, mingw32 compilerrel. Nem teljesen megbízható, de az idő 99%ában működik
 * Azért struktúrát adnak vissza mert így egyszerűbb volt fix hosszúságú stringet visszaadni. Az első fv.-nél részletezem a működésüket.
 */
#ifdef _WIN32
 /**
  * @brief Beolvassa egy összetevőnek a nevét(max 50 karakter), és visszaadja osszetevok struktúra .nev stringjében
  * @return Osszetevo
  */
Osszetevo o_beolvas1(void) {
    Osszetevo o;
    /*Wchar-ba tud rendesen olvasni utf karaktert.*/
    wchar_t wstr1[51] = { 0 };
    /*Át kell állítani mindkét(!) std streamet utf-16 kódolásra(wide), setmóddal, mert a SetConsoleCP(CP_UTF8) valamiért nem csinál semmit az inputon,
    és azért utf-16-ra mert az utf-8(_O_U8TEXT) valamiért nem működik consolablakban*/
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    /*debug kód, néha nem megbízható a scanf, régebbi compilereknél ezt kell használni.
    wchar_t line[51];
    _getws_s(line, 51);
    swscanf(line, L" %51[^\n]", wstr1);*/

    /*a scanf wide karakterekkel működő verziója, a megfelelő szintaxissal*/
    wscanf(L" %50l[^\n]", wstr1);

    /*Vissza kell állítani a kódolást mert különben a többi könyvtári fv nem működik*/
    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stdin), _O_TEXT);

    char utf8_str1[51] = { 0 };
    /*A wide-ot utf-be konvertáló fv*/
    WideCharToMultiByte(CP_UTF8, 0, wstr1, -1, utf8_str1, sizeof(utf8_str1), NULL, NULL);
    /*Mivel hajlamos inkonzisztenciákra inkább bennhagytam a debug kódot*/
    //printf("A beolvasott utf karakter: %s\n", utf8_str1);
    strcpy(o.nev, utf8_str1);
    int c;
    /*Eltakarítja a bennmaradt bytokat az stdin-ről, mert a wide karaktereknél ez elég inkonzisztens,
    *néha emiatt plusz entereket kell nyomni, de inkább 2 plusz enter mint egy segfault*/
    while ((c = getchar()) != '\n' && c != EOF) {}
    return o;

}
/**
 * @brief Beolvassa egy összetevőnek a nevét(max 50 karakter) és típusát(max 50 karakter) és visszaadja egy osszetevők struktúrában
 * @return Osszetevo
 */
Osszetevo o_beolvas2(void) {
    Osszetevo o;
    wchar_t wstr1[51] = { 0 }, wstr2[51] = { 0 };


    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    /*wchar_t line[102];
    _getws_s(line, 102);
    swscanf(line, L" %50[^,], %50[^\n]", wstr1, wstr2);*/
    wscanf(L" %50l[^,], %50l[^\n]", wstr1, wstr2);


    //wprintf(L"A beolvasott karakter: %ls, %ls, %lf\n", wstr1, wstr2, d);

    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stdin), _O_TEXT);

    char utf8_str1[51] = { 0 }, utf8_str2[51] = { 0 };
    WideCharToMultiByte(CP_UTF8, 0, wstr1, -1, utf8_str1, sizeof(utf8_str1), NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, wstr2, -1, utf8_str2, sizeof(utf8_str2), NULL, NULL);

    //printf("az utf karakter: %s, %s\n", utf8_str1, utf8_str2);
    strcpy(o.nev, utf8_str1);
    strcpy(o.tipus, utf8_str2);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return o;

}
/**
 * @brief Beolvassa egy összetevőnek a nevét(max 50 karakter) típusát(max 50 karakter) és mennyiségét és visszaadja egy összetevők struktúrában.
 * @return Osszetevo
 */
Osszetevo o_beolvas3(void) {
    Osszetevo o;
    wchar_t wstr1[51] = { 0 }, wstr2[51] = { 0 };
    double d;

    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    wscanf(L" %50l[^,], %50l[^,], %lf", wstr1, wstr2, &d);

    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stdin), _O_TEXT);

    char utf8_str1[51] = { 0 }, utf8_str2[51] = { 0 };
    WideCharToMultiByte(CP_UTF8, 0, wstr1, -1, utf8_str1, sizeof(utf8_str1), NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, wstr2, -1, utf8_str2, sizeof(utf8_str2), NULL, NULL);

    //printf("az utf karakter: %s, %s, %lf\n", utf8_str1, utf8_str2, d);
    strcpy(o.nev, utf8_str1);
    strcpy(o.tipus, utf8_str2);
    o.mennyiseg = d;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return o;

}
/**
 * @brief Beolvassa egy receptnek az elkészítési módját(max 1000 karakter), és visszaadja egy étel struktúra .elkeszites stringjében.
 * @return Etel
 */
Etel i_beolvas(void) {
    Etel o;
    wchar_t wstr1[1001] = { 0 };

    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    /*wchar_t line[51];
    _getws_s(line, 51);
    swscanf(line, L" %51[^\n]", wstr1);*/

    wscanf(L" %1000l[^\n]", wstr1);

    //wprintf(L"A beolvasott karakter: %ls, %ls, %lf\n", wstr1, wstr2, d);

    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stdin), _O_TEXT);

    char utf8_str1[1001] = { 0 };
    WideCharToMultiByte(CP_UTF8, 0, wstr1, -1, utf8_str1, sizeof(utf8_str1), NULL, NULL);


    //printf("az utf karakter: %s\n", utf8_str1);
    strcpy(o.elkeszites, utf8_str1);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return o;

}
#endif
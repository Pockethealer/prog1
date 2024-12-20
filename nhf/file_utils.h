/**
 * @file file_utils.h
 * @brief A filekezelő fv-ek deklarációi, a program által használt structok deklarációi, és a konzol kiszínezéséhez használt ansi karakterkódok.
 * @date 2024-11-14
 */
#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <locale.h>
#include <wchar.h>
#include <windows.h>
#include <locale.h>
#include <fcntl.h>
#include <io.h>
#endif
#include "debugmalloc.h"
 /**
  * @brief A konzol kiszinezésére bevezetett konstansok
  */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

  // Text colors
#define COLOR_RESET     "\033[0m"
#define COLOR_BOLD      "\033[1m"
#define COLOR_UNDERLINE "\033[4m"

#define COLOR_BLACK     "\033[0;30m"
#define COLOR_RED       "\033[0;31m"
#define COLOR_GREEN     "\033[0;32m"
#define COLOR_YELLOW    "\033[0;33m"
#define COLOR_BLUE      "\033[0;34m"
#define COLOR_MAGENTA   "\033[0;35m"
#define COLOR_CYAN      "\033[0;36m"
#define COLOR_WHITE     "\033[0;37m"

// Bright (bold) text colors
#define COLOR_BRIGHT_BLACK   "\033[1;30m"
#define COLOR_BRIGHT_RED     "\033[1;31m"
#define COLOR_BRIGHT_GREEN   "\033[1;32m"
#define COLOR_BRIGHT_YELLOW  "\033[1;33m"
#define COLOR_BRIGHT_BLUE    "\033[1;34m"
#define COLOR_BRIGHT_MAGENTA "\033[1;35m"
#define COLOR_BRIGHT_CYAN    "\033[1;36m"
#define COLOR_BRIGHT_WHITE   "\033[1;37m"

// Background colors
#define BG_BLACK     "\033[40m"
#define BG_RED       "\033[41m"
#define BG_GREEN     "\033[42m"
#define BG_YELLOW    "\033[43m"
#define BG_BLUE      "\033[44m"
#define BG_MAGENTA   "\033[45m"
#define BG_CYAN      "\033[46m"
#define BG_WHITE     "\033[47m"

// Bright (bold) background colors
#define BG_BRIGHT_BLACK   "\033[100m"
#define BG_BRIGHT_RED     "\033[101m"
#define BG_BRIGHT_GREEN   "\033[102m"
#define BG_BRIGHT_YELLOW  "\033[103m"
#define BG_BRIGHT_BLUE    "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN    "\033[106m"
#define BG_BRIGHT_WHITE   "\033[107m"
  /*Az általános adatstruktúráim, a kettős indirekció ott van benne,
     *hogy egy ételnek bárhány összetevője lehet illetve bárhány étel lehet a receptkönyvben.*/

     /**
         * @struct Osszetevo
         * @brief  Összetevők struckt tartalmazza az összetevő nevét (max 50 karakter),
         *típusát(max 50 karakter), és mennyiségét(double)
     */
typedef struct Osszetevo
{
    char nev[51];
    char tipus[51];
    double mennyiseg;
} Osszetevo;
/**
 * @struct Etel
 * @brief Étel struktúra tartalmazza az étel nevét(max 50 karakter) az összetevőinek számát,
 * az összetevők tömbjének pointerét, és az elkészítési útmutatót(max 1000 karakter)
 */
typedef struct Etel
{
    char nev[51];
    int osszetevok_szama;
    Osszetevo* osszetevok;
    char elkeszites[1001];
} Etel;
/**
 * @struct Receptkonyv
 * @brief Receptkönyv struktúra tartalmazza a benne levő ételek számát és az ételek tömbjére egy mutatót.
 */
typedef struct Receptkonyv
{
    int etelek_szama;
    Etel* etelek;
} Receptkonyv;

/**
 * @struct Egyedi_osszetevok
 * @brief Egyedi összetevőket tartalmazó lista minden összetevő egyszer
 *kell hogy szerepeljen benne, tartalmazza az összetevők számát és az összetevők tömbjére mutató pointert.
 *A benne levő összetevők rendszerint nem tartalmaznak mennyiségeket csak a nevet és típust, de a lehetőség adott rá.
 */
typedef struct Egyedi_osszetevok
{
    Osszetevo* egyedi_osszetevok;
    int egyedi_osszetevok_szama;
} Egyedi_osszetevok;


Receptkonyv* receptek_beolvas(char* file);
void receptet_fileba_ment(Receptkonyv* r, char* file);
void receptkonyv_felszabadit(Receptkonyv* r);
int recept_letezik(Receptkonyv* r, const char* etel_neve);
void recept_kiir(Etel* m);

Egyedi_osszetevok* osszetevo_beolvas(void);
void osszetevo_fileba_ment(Egyedi_osszetevok* e, Receptkonyv* r);
void egyedi_osszetevo_felszabadit(Egyedi_osszetevok* e);
int osszetevo_letezik(Egyedi_osszetevok* e, const char* osszetevo_neve);

Osszetevo o_beolvas1(void);
Osszetevo o_beolvas2(void);
Osszetevo o_beolvas3(void);
Etel i_beolvas(void);

#endif

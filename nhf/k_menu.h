/**
 * @file k_menu.h
 * @brief A qol és kedvencek/bevlista almenük fv deklarációi és include headerei.
 * @date 2024-11-14
 */
#ifndef K_MENU_H
#define K_MENU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "file_utils.h"
#include "debugmalloc.h"
#include "o_menu.h"

void recept_random(Receptkonyv* r);
void qol_almenu(Receptkonyv* r);
void receptek_szures(Receptkonyv* r);
void bl_almenu(Receptkonyv* r);
void bl_hozzaad(Receptkonyv* r, Egyedi_osszetevok* e);
void bl_torol(Egyedi_osszetevok* e);
void bl_ment(Egyedi_osszetevok* e);
void kedvenc_hozzáad(Receptkonyv* r, Receptkonyv** k);

#endif
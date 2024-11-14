/**
 * @file o_menu.h
 * @brief Az összetevők és receptek almenü fv-einek a deklarációja, és az include headerek.
 * @date 2024-11-14
 *
 */
#ifndef O_MENU_H
#define O_MENU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "file_utils.h"
#include "debugmalloc.h"

void osszetevok_almenu(Egyedi_osszetevok** e);
void osszetevo_felvesz(Egyedi_osszetevok** e);
void osszetevo_kiir(Egyedi_osszetevok* e);
void osszetevok_keres(Egyedi_osszetevok* e);
void osszetevo_torol(Egyedi_osszetevok* e);

void receptek_almenu(Receptkonyv** r);
void recept_felvesz(Receptkonyv** r);
void recept_keres(Receptkonyv* r);
void recept_torol(Receptkonyv* r);
void recept_listaz(Receptkonyv* r);

#endif
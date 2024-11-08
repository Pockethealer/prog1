#ifndef MENU_H
#define MENU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <locale.h>
#endif
#include "file_utils.h"
#include "debugmalloc.h"

void osszetevok_almenu(Egyedi_osszetevok* e);
int main_menu(void);
int kilepes(Egyedi_osszetevok* e, Receptkonyv* r);
void menu_kiir(void);
void osszetevo_felvesz(Egyedi_osszetevok* e);
void osszetevo_kiir(Egyedi_osszetevok* e);

#endif

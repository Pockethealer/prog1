
#ifndef K_MENU_H
#define K_MENU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "file_utils.h"
#include "debugmalloc.h"

void recept_random(Receptkonyv* r);
void qol_almenu(Receptkonyv* r);


#endif
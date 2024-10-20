#include <stdio.h>
#include "../include/file_utils.h"

FILE* file_megnyit(char* mit, char* hogyan) {
    FILE* file = fopen(mit, hogyan);
    if (file == NULL) {
        printf("Nem sikerült megnyitni a %s file-t", mit);
        return NULL;
    }
    return file;
}
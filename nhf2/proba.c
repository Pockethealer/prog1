Receptkonyv* receptek_beolvas(void)
{
    Receptkonyv* r = (Receptkonyv*)malloc(sizeof(Receptkonyv));
    if (r == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        return NULL;  // Removed unnecessary free of NULL pointer
    }

    FILE* f = fopen("receptek.txt", "r");
    if (f == NULL)
    {
        printf("Nem lehetett megnyitni a file-t!\n");
        free(r);
        return NULL;
    }

    // Add buffer size limits to prevent buffer overflows
#define MAX_NEV_LENGTH 256
#define MAX_TIPUS_LENGTH 64
#define MAX_ELKESZITES_LENGTH 1024

// Initialize strings to zero
    memset(&r->etelek, 0, sizeof(r->etelek));

    // Read number of recipes with error checking
    if (fscanf(f, "%d", &(r->etelek_szama)) != 1 || r->etelek_szama <= 0) {
        printf("Hibas etelek szama a file-ban!\n");
        free(r);
        fclose(f);
        return NULL;
    }

    r->etelek = (Etel*)calloc(r->etelek_szama, sizeof(Etel));
    if (r->etelek == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!\n");
        free(r);
        fclose(f);
        return NULL;
    }

    // Read each recipe
    for (int i = 0; i < r->etelek_szama; i++)
    {
        // Clear any leftover whitespace/newline
        int c;
        while ((c = fgetc(f)) != EOF && (c == ' ' || c == '\n' || c == '\r'));
        ungetc(c, f);

        // Allocate with size limits
        r->etelek[i].nev = (char*)calloc(MAX_NEV_LENGTH, sizeof(char));
        if (r->etelek[i].nev == NULL) {
            goto cleanup;
        }

        // Read name and number of ingredients with better error checking
        if (fscanf(f, "%[^,],%d", r->etelek[i].nev, &(r->etelek[i].osszetevok_szama)) != 2 ||
            r->etelek[i].osszetevok_szama <= 0) {
            printf("Hibas formatum a receptek.txt file-ban!\n");
            goto cleanup;
        }

        r->etelek[i].osszetevok = (Osszetevo*)calloc(r->etelek[i].osszetevok_szama, sizeof(Osszetevo));
        if (r->etelek[i].osszetevok == NULL)
        {
            printf("Nem lehetett lefoglalni a memoriat!\n");
            goto cleanup;
        }

        // Read ingredients
        for (int j = 0; j < r->etelek[i].osszetevok_szama; j++)
        {
            // Clear any leftover whitespace/newline
            while ((c = fgetc(f)) != EOF && (c == ' ' || c == '\n' || c == '\r'));
            ungetc(c, f);

            // Allocate strings with size limits
            r->etelek[i].osszetevok[j].nev = (char*)calloc(MAX_NEV_LENGTH, sizeof(char));
            r->etelek[i].osszetevok[j].tipus = (char*)calloc(MAX_TIPUS_LENGTH, sizeof(char));
            if (r->etelek[i].osszetevok[j].nev == NULL || r->etelek[i].osszetevok[j].tipus == NULL) {
                goto cleanup;
            }

            if (fscanf(f, "%[^,], %[^,],%lf",
                r->etelek[i].osszetevok[j].nev,
                r->etelek[i].osszetevok[j].tipus,
                &r->etelek[i].osszetevok[j].mennyiseg) != 3) {
                printf("Hibas osszetevo formatum!\n");
                goto cleanup;
            }
        }

        // Allocate and read preparation instructions
        r->etelek[i].elkeszites = (char*)calloc(MAX_ELKESZITES_LENGTH, sizeof(char));
        if (r->etelek[i].elkeszites == NULL) {
            goto cleanup;
        }

        // Clear any leftover whitespace/newline
        while ((c = fgetc(f)) != EOF && (c == ' ' || c == '\n' || c == '\r'));
        ungetc(c, f);

        if (fscanf(f, "%[^\n]", r->etelek[i].elkeszites) != 1) {
            printf("Hibas elkeszites formatum!\n");
            goto cleanup;
        }
    }

    fclose(f);
    return r;

cleanup:
    // Proper cleanup of all allocated memory
    if (r != NULL) {
        if (r->etelek != NULL) {
            for (int i = 0; i < r->etelek_szama; i++) {
                if (r->etelek[i].osszetevok != NULL) {
                    for (int j = 0; j < r->etelek[i].osszetevok_szama; j++) {
                        free(r->etelek[i].osszetevok[j].nev);
                        free(r->etelek[i].osszetevok[j].tipus);
                    }
                    free(r->etelek[i].osszetevok);
                }
                free(r->etelek[i].nev);
                free(r->etelek[i].elkeszites);
            }
            free(r->etelek);
        }
        free(r);
    }
    if (f != NULL) {
        fclose(f);
    }
    return NULL;
}
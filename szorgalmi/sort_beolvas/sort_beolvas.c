#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Ez mar ha minden igaz tudja kezelni az EOF-ot helyesen*/
char *stringet_beolvas(int n)
{
    char *string;
    char c;
    int i = scanf("%c", &c);
    if (c == '\n' || i < 0)
    {
        string = malloc((n + 1) * sizeof(char));
        if (string == NULL)
        {
            printf("Nem lehetett lefoglalni a memoriat!");
            return NULL;
        }
        string[n] = '\0';
        return string;
    }
    string = stringet_beolvas(n + 1);
    /*Hibakezeles, hogy ne legyen tulindexeles, ha nem sikerult lefoglalni a memoriat.*/
    if (string == NULL)
    {
        printf("Nem lehetett lefoglalni a memoriat!");
        return NULL;
    }
    string[n] = c;
    return string;
}
char *sort_beolvas(void)
{
    char *string = stringet_beolvas(0);
    return string;
}
int main(void)
{
    printf("Irja be a beolvasando szoveget!\n");
    char *s = sort_beolvas();
    printf("\nA beolvasott szoveg:\n%s\n", s);
    free(s);
    return 0;
}
#ifdef _WIN32
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <locale.h>
#include <fcntl.h>
#include <io.h>
#include "file_utils.h"


Osszetevo o_beolvas1(void) {
    Osszetevo o;
    wchar_t wstr1[51] = { 0 };

    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    /*wchar_t line[51];
    _getws_s(line, 51);
    swscanf(line, L" %51[^\n]", wstr1);*/

    wscanf(L" %50l[^\n]", wstr1);

    //wprintf(L"A beolvasott karakter: %ls, %ls, %lf\n", wstr1, wstr2, d);

    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stdin), _O_TEXT);

    char utf8_str1[51] = { 0 };
    WideCharToMultiByte(CP_UTF8, 0, wstr1, -1, utf8_str1, sizeof(utf8_str1), NULL, NULL);


    printf("az utf karakter: %s\n", utf8_str1);
    strcpy(o.nev, utf8_str1);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return o;

}
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

    printf("az utf karakter: %s, %s\n", utf8_str1, utf8_str2);
    strcpy(o.nev, utf8_str1);
    strcpy(o.tipus, utf8_str2);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return o;

}
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

    printf("az utf karakter: %s, %s, %lf\n", utf8_str1, utf8_str2, d);
    strcpy(o.nev, utf8_str1);
    strcpy(o.tipus, utf8_str2);
    o.mennyiseg = d;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return o;

}
#endif
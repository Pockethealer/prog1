#include "file_utils.h"
#include "menu.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <fcntl.h>
#include <io.h>
#include <windows.h>

int main(void) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "hu_HU.UTF-8");


    printf("írd be a stringet!");

    wchar_t wstr1[51] = { 0 }, wstr2[51] = { 0 };
    double d;

    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    wscanf(L" %50[^,], %50[^,], %lf", wstr1, wstr2, &d);

    // Display results using wide strings
    wprintf(L"A beolvasott karakter: %ls, %ls, %lf\n", wstr1, wstr2, d);

    // Reset input/output modes to normal text
    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stdin), _O_TEXT);

    // Convert wide strings to UTF-8
    char utf8_str1[51] = { 0 }, utf8_str2[51] = { 0 };
    int result1 = WideCharToMultiByte(CP_UTF8, 0, wstr1, -1, utf8_str1, sizeof(utf8_str1), NULL, NULL);
    int result2 = WideCharToMultiByte(CP_UTF8, 0, wstr2, -1, utf8_str2, sizeof(utf8_str2), NULL, NULL);

    // Print the converted UTF-8 strings
    printf("az utf karakter: %s, %s, %lf\n", utf8_str1, utf8_str2, d);

    return 0;
}
#ifdef _WIN32
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <locale.h>
#include <fcntl.h>
#include <io.h>
#include "file_utils.h"


int read_comma_separated(wchar_t* str1, wchar_t* str2, int max_len) {
    wchar_t line[102] = { 0 };  // Initialize to zero

    // Flush any remaining input
    fflush(stdin);

    // Read the whole line
    if (_getws_s(line, 102) == NULL) {
        return 0;
    }

    // Find the comma
    wchar_t* comma = wcschr(line, L',');
    if (!comma) {
        return 0;  // No comma found
    }

    // Split at comma
    *comma = L'\0';

    // Copy first part (trim trailing spaces)
    wcsncpy(str1, line, max_len);
    str1[max_len - 1] = L'\0';  // Ensure null termination

    // Copy second part (skip leading spaces)
    wchar_t* start = comma + 1;
    while (*start == L' ') start++;
    wcsncpy(str2, start, max_len);
    str2[max_len - 1] = L'\0';  // Ensure null termination

    // Trim trailing newline from both strings
    for (int i = 0; i < max_len; i++) {
        if (str1[i] == L'\n' || str1[i] == L'\r') str1[i] = L'\0';
        if (str2[i] == L'\n' || str2[i] == L'\r') str2[i] = L'\0';
    }

    return 1;
}

Osszetevo osszetevo_beolvas_stdin(void) {
    Osszetevo o;
    // Set up UTF-8 console
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Set UTF-8 locale
    setlocale(LC_ALL, ".UTF8");

    // Set console mode to handle UTF-8
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    wchar_t wstr1[51] = { 0 }, wstr2[51] = { 0 };

    char utf8_str1[51] = { 0 }, utf8_str2[51] = { 0 };
    if (read_comma_separated(wstr1, wstr2, 50)) {
        // Convert to UTF-8


        int result1 = WideCharToMultiByte(CP_UTF8, 0, wstr1, -1, utf8_str1, sizeof(utf8_str1), NULL, NULL);
        int result2 = WideCharToMultiByte(CP_UTF8, 0, wstr2, -1, utf8_str2, sizeof(utf8_str2), NULL, NULL);

        if (result1 && result2) {
            // Switch back to normal mode for printf
            _setmode(_fileno(stdout), _O_TEXT);
            printf("UTF-8 strings: %s, %s\n", utf8_str1, utf8_str2);
        }
        else {
            wprintf(L"Error converting strings\n");
        }
    }
    else {
        wprintf(L"Error reading input\n");
    }
    _setmode(_fileno(stdout), _O_TEXT);
    _setmode(_fileno(stdin), _O_TEXT);
    strcpy(o.nev, utf8_str1);
    strcpy(o.tipus, utf8_str2);
    return o;
}
#endif
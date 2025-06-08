//
// Created by pnich on 07/06/2025.
//

#include "cli_utils.h"

#include <stdio.h>

#if _WIN32
#include <windows.h>
#endif

void ler_entrada(char *str) {
    char buffer[MAX_BUFF_SIZE];

    fgets(buffer, MAX_BUFF_SIZE, stdin);
    strcpy(str, buffer);
    tirar_brancos(str);

    //limpar_buffer();
}

void ler_entrada_int(int *num) {
    char buffer[MAX_BUFF_SIZE];
    ler_entrada(buffer);

    *num = strtol(buffer, NULL, 10);
}

int escolha_em_intervalo(const char *mensagem, char *opcoes[], int tamanho) {
    puts(mensagem);

    for (int i = 0; i < tamanho; i++) {
        printf("%d. %s\n", i + 1, opcoes[i]);
    }

    int escolha, ok;
    do {
        ler_entrada_int(&escolha);
        ok = 1 <= escolha && escolha <= tamanho;

        if (!ok) puts("Escolha inválida!");
    } while (!ok);

    return escolha;
}

void tirar_brancos(char *str) {
    // créditos: https://codeforwin.org/c-programming/c-program-to-trim-trailing-white-space-characters-in-string

    int index, i;

    /* Set default index */
    index = -1;

    /* Find last index of non-white space character */
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }

        i++;
    }

    /* Mark next character to last non-white space character as NULL */
    str[index + 1] = '\0';
}

void limpar_buffer() {
    // créditos: https://c-faq.com/stdio/stdinflush2.html

    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

void pausar_tela() {
    puts("Aperte qualquer tecla para continuar...");
    getchar();

    limpar_tela();
}

void limpar_tela() {
#if _WIN32
    // Credito: https://cplusplus.com/articles/4z18T05o/

    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
        )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
        )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );

#else

    printf(CONS_RESET); printf(CONS_CLEAR);
#endif
}
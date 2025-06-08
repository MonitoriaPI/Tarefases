//
// Created by pnich on 07/06/2025.
//

#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#define MAX_BUFF_SIZE 256

// Funciona apenas para terminais POSIX
// (veja mais sobre em https://cplusplus.com/articles/4z18T05o/)
#define CONS_UP         "\033[A"
#define CONS_DEL_LINE   "\033[2K"
#define CONS_CLEAR      "\033[2J"
#define CONS_RESET      "\033[f"

void ler_entrada();
void ler_entrada_int();
int escolha_em_intervalo(const char *mensagem, char *opcoes[], int tamanho);

void tirar_brancos();
void limpar_buffer();
void pausar_tela();
void limpar_tela();

#endif //CLI_UTILS_H

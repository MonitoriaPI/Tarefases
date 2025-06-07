//
// Created by pnich on 06/06/2025.
//

#ifndef CLI_H
#define CLI_H

#define MAX_BUFF_SIZE 256

#define CONS_UP         "\033[A"
#define CONS_DEL_LINE   "\033[2K"
#define CONS_CLEAR      "\033[2J"
#define CONS_RESET      "\033[f"

int tela_principal();
void listar_tarefas();

void tela_adicao_tarefas();
void tela_delecao_tarefas();
void tela_modificacao_tarefas();

int escolha_em_intervalo(char *mensagem, char *opcoes[], int tamanho);
void ler_entrada();
void ler_entrada_int();
void limpar_buffer();
void tirar_brancos();
void limpar_tela();
void pausar_tela();

#endif //CLI_H

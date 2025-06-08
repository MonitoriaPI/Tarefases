//
// Created by pnich on 06/06/2025.
//

#include "tarefas_funcs.h"

#include <stdio.h>
#include <string.h>

#include "cli_utils.h"


#define str_equals(x, y) (strcmp((x), (y)) == 0)

const char *nomeDoArquivo = ".tarefases";

Tarefa tarefas[QTD_MAX_TAREFAS];
int qtdTarefas = 0;

Tarefa construir_tarefa(const char *descricao, int estaConcluida) {
    Tarefa t = {
        .descricao = strdup(descricao),
        .estaConcluida = estaConcluida
    };
    return t;
}

void copiar_tarefa(Tarefa *tarefaDest, const Tarefa *tarefaSrc) {
    (*tarefaDest).descricao = strdup((*tarefaSrc).descricao);
    (*tarefaDest).estaConcluida = (*tarefaSrc).estaConcluida;
}

int adicionar_tarefa(Tarefa tarefa) {
    if (qtdTarefas == QTD_MAX_TAREFAS) return 0;

    copiar_tarefa(&tarefas[qtdTarefas++], &tarefa);

    return 1;
}

int remover_tarefa(Tarefa *tarefa) {
    if (qtdTarefas == 0) return 0;

    int idx = encontrar_tarefa(tarefa);
    if (idx == -1) return -1;

    for (; idx < qtdTarefas-1; idx++)
        tarefas[idx] = tarefas[idx+1];

    qtdTarefas--;

    return 1;
}

int atualizar_tarefa(Tarefa tarefa, Tarefa tarefaAtualizada) {
    int idx = encontrar_tarefa(&tarefa);
    if (idx == -1) return 0;

    copiar_tarefa(&tarefas[idx], &tarefaAtualizada);

    return 1;
}

int salvar_tarefas() {
    if (qtdTarefas == 0) return 0;

    FILE *listaDeTarefas = fopen(nomeDoArquivo, "w");
    if (listaDeTarefas == NULL) return -1;

    for (int idx = 0; idx < qtdTarefas; idx++) {
        fprintf(listaDeTarefas, "%s;; %d\n", tarefas[idx].descricao, tarefas[idx].estaConcluida);
    }

    fclose(listaDeTarefas);

    return 1;
}

int carregar_tarefas() {
    FILE *listaDeTarefas = fopen(nomeDoArquivo, "r");
    if (listaDeTarefas == NULL) return -1;

    char descricao[MAX_BUFF_SIZE];
    int estaConcluida = 0;

    while (fscanf(listaDeTarefas, "%[^;];; %d\n", descricao, &estaConcluida) == 2) {
        adicionar_tarefa(construir_tarefa(
            descricao,
            estaConcluida
        ));
    }

    fclose(listaDeTarefas);

    return 1;
}

int tarefas_sao_iguais(const Tarefa *tarefa1, const Tarefa *tarefa2) {
    return (
      str_equals((*tarefa1).descricao, (*tarefa2).descricao) &&
      (*tarefa1).estaConcluida == (*tarefa2).estaConcluida
    );
}

int encontrar_tarefa(Tarefa *tarefa) {
    for (int idx = 0; idx < qtdTarefas; idx++)
        if (tarefas_sao_iguais(tarefa, &tarefas[idx])) return idx;

    return -1; // não encontrou
}



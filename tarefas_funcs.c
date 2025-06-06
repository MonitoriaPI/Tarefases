//
// Created by pnich on 06/06/2025.
//

#include "tarefas_funcs.h"

#include <stdio.h>
#include <string.h>

#define str_equals(x, y) (strcmp((x), (y)) == 0)

int adicionar_tarefa(Tarefa *tarefa) {
    if (qtdTarefas == QTD_MAX_TAREFAS) return 0;

    tarefas[qtdTarefas] = *tarefa;
    qtdTarefas++;

    return 1;
}

int remover_tarefa(Tarefa *tarefa) {
    if (qtdTarefas == 0) return 0;

    for (int idx = encontrar_tarefa(tarefa); idx < qtdTarefas-1; idx++)
        tarefas[idx] = tarefas[idx+1];

    qtdTarefas--;

    return 1;
}

int atualizar_tarefa(Tarefa *tarefa, Tarefa *tarefaAtualizada) {
    int idx = encontrar_tarefa(tarefa);
    if (idx == -1) return 0;

    tarefas[idx] = *tarefaAtualizada;

    return 1;
}

int salvar_tarefas() {
    if (qtdTarefas == 0) return 0;

    FILE *listaDeTarefas = fopen("tarefas.TODO~", "w");
    if (listaDeTarefas == NULL) return -1;

    for (int idx = 0; idx < qtdTarefas; idx++) {
        fprintf(listaDeTarefas, "%s %d", tarefas[idx].descricao, tarefas[idx].estaConcluida);
    }
}

int carregar_tarefas() {
    FILE *listaDeTarefas = fopen("tarefas.TODO~", "r");
    if (listaDeTarefas == NULL) return -1;

    Tarefa *tarefa = malloc(sizeof(Tarefa));

    while (fscanf(listaDeTarefas, "%s %d", (*tarefa).descricao, (*tarefa).estaConcluida) == 2) {
        tarefas[qtdTarefas] = *tarefa;
        qtdTarefas++;
    }

    free(tarefa);
    fclose(listaDeTarefas);

    return 1;
}

int tarefas_sao_iguais(Tarefa *tarefa1, Tarefa *tarefa2) {
    return (
      str_equals((*tarefa1).descricao, (*tarefa2).descricao) &&
      (*tarefa1).estaConcluida == (*tarefa2).estaConcluida
    );
}

int encontrar_tarefa(Tarefa *tarefa) {
    for (int idx = 0; idx < qtdTarefas; idx++) {
        if (tarefas_sao_iguais(tarefa, &tarefas[idx]))
            return idx;
    }

    return -1; // não encontrou
}



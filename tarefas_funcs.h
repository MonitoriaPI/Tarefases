//
// Created by pnich on 06/06/2025.
//

#ifndef TAREFAS_FUNCS_H
#define TAREFAS_FUNCS_H

#include <stdbool.h>
#include <stdlib.h>

#define QTD_MAX_TAREFAS 10

typedef struct {
    char *descricao;
    bool estaConcluida = 0;
} Tarefa;

// Tarefa *tarefas = malloc(QTD_MAX_TAREFAS * sizeof(Tarefa));
Tarefa tarefas[QTD_MAX_TAREFAS];
int qtdTarefas = 0;

int adicionar_tarefa(Tarefa *tarefa);
int remover_tarefa(Tarefa *tarefa);
int atualizar_tarefa(Tarefa *tarefa, Tarefa *tarefaAtualizada);

int salvar_tarefas();
int carregar_tarefas();
int encontrar_tarefa(Tarefa *tarefa);
int tarefas_sao_iguais(Tarefa *tarefa1, Tarefa *tarefa2);

#endif //TAREFAS_FUNCS_H

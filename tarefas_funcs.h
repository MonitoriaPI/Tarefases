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
    int estaConcluida;
} Tarefa;

// Tarefa *tarefas = malloc(QTD_MAX_TAREFAS * sizeof(Tarefa));
extern Tarefa tarefas[];
extern int qtdTarefas;

Tarefa construir_tarefa(char *descricao, int estaConcluida);
void copiar_tarefa(Tarefa *tarefaDest, Tarefa *tarefaSrc);

int adicionar_tarefa(Tarefa tarefa);
int remover_tarefa(Tarefa *tarefa);
int atualizar_tarefa(Tarefa tarefa, Tarefa tarefaAtualizada);

// 0    : nenhuma tarefa registrada no momento
// -1   : erro ao criar o arquivo das tarefas
int salvar_tarefas();

// -1   : arquivo das tarefas não existe
int carregar_tarefas();

int encontrar_tarefa(Tarefa *tarefa);
int tarefas_sao_iguais(Tarefa *tarefa1, Tarefa *tarefa2);

#endif //TAREFAS_FUNCS_H

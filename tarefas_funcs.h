//
// Created by pnich on 06/06/2025.
//

#ifndef TAREFAS_FUNCS_H
#define TAREFAS_FUNCS_H

#define QTD_MAX_TAREFAS 10

typedef struct {
    char *descricao;
    int estaConcluida;
} Tarefa;

extern Tarefa tarefas[];
extern int qtdTarefas;
extern const char *nomeDoArquivo;

Tarefa construir_tarefa(const char *descricao, int estaConcluida);

void copiar_tarefa(Tarefa *tarefaDest, const Tarefa *tarefaSrc);

int adicionar_tarefa(Tarefa tarefa);

int remover_tarefa(Tarefa *tarefa);

int atualizar_tarefa(Tarefa *tarefa, Tarefa tarefaAtualizada);

int encontrar_tarefa(const Tarefa *tarefa);

int tarefas_sao_iguais(const Tarefa *tarefa1, const Tarefa *tarefa2);

void mudar_marcaco_tarefa(Tarefa *tarefa);

// 0    : nenhuma tarefa registrada no momento
// -1   : erro ao criar o arquivo das tarefas
int salvar_tarefas();

// -1   : arquivo das tarefas não existe
int carregar_tarefas();

#endif //TAREFAS_FUNCS_H

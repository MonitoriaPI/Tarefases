//
// Created by pnich on 06/06/2025.
//


#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "cli_utils.h"
#include "../tarefas_funcs.h"

int cli_tela_principal() {

    if (carregar_tarefas() == -1) {
        puts("Arquivo de tarefas não encontrado...");
        pausar_tela();
    }

    while (1) {
        limpar_tela();

        puts("\t\tTAREFASES\n");

        listar_tarefas();

        char *opcoes[] = {
            "Adicionar uma tarefa",
            "Remover uma tarefa",
            "Atualizar uma tarefa",
            "Salvar tarefas",
            "Fechar programa"
        };

        int escolha = escolha_em_intervalo("O que deseja fazer?", opcoes, 5);


        switch (escolha) {
        case 1:
            tela_adicao_tarefas();
            break;
        case 2:
            tela_delecao_tarefas();
            break;
        case 3:
            tela_modificacao_tarefas();
            break;
        case 4:
            int status = salvar_tarefas();

            puts("");

            if (status == 0)
                puts("Nenhuma tarefa pra salvar...");
            else if (status == -1)
                puts("Erro ao tentar criar tarefas.TODO~");
            else
                puts("Tarefas salvas com sucesso!");

            pausar_tela();

            break;
        case 5:
            limpar_tela();
            puts("Fechando programa...");
            pausar_tela();
            return 0;
        }
    }
}

void listar_tarefas() {

    if (qtdTarefas == 0) {
        puts("Nenhuma tarefa adicionada no momento\n");
        return;
    }

    for (int i = 0; i < qtdTarefas; i++)
        printf("[%c] %s\n", tarefas[i].estaConcluida? 'X' : ' ', tarefas[i].descricao);
    puts("");
}

void tela_adicao_tarefas() {
    limpar_tela();

    char *descricao = malloc(MAX_BUFF_SIZE);

    puts("Digite a tarefa");
    ler_entrada(descricao);

    adicionar_tarefa(construir_tarefa(
        descricao,
        0
    ));

    free(descricao);

}

void tela_delecao_tarefas() {
    limpar_tela();

    char *nomesTarefas[QTD_MAX_TAREFAS];
    for (int i = 0; i < qtdTarefas; i++)
        nomesTarefas[i] = tarefas[i].descricao;

    // array eh 0-indexado
    int escolha = escolha_em_intervalo("Qual tarefa deseja remover?", nomesTarefas, qtdTarefas) - 1;

    remover_tarefa(&tarefas[escolha]);
}

void tela_modificacao_tarefas() {
    limpar_tela();

    if (qtdTarefas == 0) {
        puts("Nenhuma tarefa para modificar");
        pausar_tela();
        return;
    }

    char *nomesTarefas[QTD_MAX_TAREFAS];
    for (int i = 0; i < qtdTarefas; i++)
        nomesTarefas[i] = tarefas[i].descricao;

    // array eh 0-indexado
    int escolhaTarefa = escolha_em_intervalo("Qual tarefa deseja modificar?", nomesTarefas, qtdTarefas) - 1;

    char *opcoes[] = {
        "Mudar o nome",
        (tarefas[escolhaTarefa].estaConcluida? "Desmarcar" : "Marcar")
    };
    int escolhaModificacao = escolha_em_intervalo("O que deseja fazer?", opcoes, 2);

    switch (escolhaModificacao) {
    case 1:
        puts("Digite o novo nome");
        ler_entrada(tarefas[escolhaTarefa].descricao);
        break;
    case 2:
        mudar_marcaco_tarefa(&tarefas[escolhaTarefa]);
        break;
    }
}

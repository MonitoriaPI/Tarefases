//
// Created by pnich on 06/06/2025.
//

#include "cli.h"

#include <stdio.h>

#include "dbg.h"
#include "tarefas_funcs.h"

#if _WIN32
#include <windows.h>
#endif

int tela_principal() {

    if (carregar_tarefas() == -1) {
        puts("Arquivo tarefas.TODO~ nao encontrado...");
        pausar_tela();
    }

    while (1) {
        //limpar_tela();

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

                if (status == 0)
                    puts("Nenhuma tarefa pra salvar...");
                else if (status == -1)
                    puts("Erro ao tentar criar tarefas.TODO~");
                else
                    puts("Tarefas salvas com sucesso!");

                break;
            case 5:
                limpar_tela();
                puts("Fechando programa...");
                return 0;

        }
    }
}

void listar_tarefas() {
    dbgi(qtdTarefas)

    if (qtdTarefas == 0) {
        puts("Nenhuma tarefa adicionada no momento\n");
        return;
    }

    for (int i = 0; i < qtdTarefas; i++)
        printf("[%c] %s\n", ((tarefas[i]).estaConcluida? 'X' : ' '), (tarefas[i]).descricao);
    puts("");
}

void tela_adicao_tarefas() {
    //limpar_tela();

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
    // limpar_tela();
    //
    // char *nomesTarefas[QTD_MAX_TAREFAS];
    // for (int i = 0; i < qtdTarefas; i++)
    //     nomesTarefas[i] = tarefas[i].descricao;
    // int escolha = escolha_em_intervalo("Qual tarefa deseja remover?", nomesTarefas, qtdTarefas);
    //
    // remover_tarefa(&tarefas[escolha]);
}

void tela_modificacao_tarefas() {
    // limpar_tela();

    if (qtdTarefas == 0) {
        puts("Nenhuma tarefa para modificar");
        pausar_tela();
        return;
    }

    char *nomesTarefas[QTD_MAX_TAREFAS];
    for (int i = 0; i < qtdTarefas; i++)
        nomesTarefas[i] = tarefas[i].descricao;
    int escolhaTarefa = escolha_em_intervalo("Qual tarefa deseja modificar?", nomesTarefas, qtdTarefas) - 1;

    Tarefa *tarefaAtualizada = malloc(sizeof(Tarefa));
    copiar_tarefa(tarefaAtualizada, &tarefas[escolhaTarefa]);

    char *opcoes[] = {
        "Mudar o nome",
        (tarefas[escolhaTarefa].estaConcluida? "Desmarcar" : "Marcar")
    };
    int escolhaModificacao = escolha_em_intervalo("O que deseja fazer?", opcoes, 2);

    switch (escolhaModificacao) {
    case 1:
        puts("Digite o novo nome");
        ler_entrada((*tarefaAtualizada).descricao);
        break;
    case 2:
        (*tarefaAtualizada).estaConcluida = !(*tarefaAtualizada).estaConcluida;
        break;
    }

    atualizar_tarefa(tarefas[escolhaTarefa], *tarefaAtualizada);

    free(tarefaAtualizada);
}

void ler_entrada(char *str) {
    char buffer[MAX_BUFF_SIZE];

    fgets(buffer, MAX_BUFF_SIZE, stdin);
    strcpy(str, buffer);
    tirar_brancos(str);

    dbgs(str);

    //limpar_buffer();
}

void ler_entrada_int(int *num) {
    char buffer[MAX_BUFF_SIZE];
    ler_entrada(buffer);

    *num = strtol(buffer, NULL, 10);
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

int escolha_em_intervalo(char *mensagem, char *opcoes[], int tamanho) {
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

void limpar_buffer() {
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

    // HANDLE                     hStdOut;
    // CONSOLE_SCREEN_BUFFER_INFO csbi;
    // DWORD                      count;
    // DWORD                      cellCount;
    // COORD                      homeCoords = { 0, 0 };
    //
    // hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    // if (hStdOut == INVALID_HANDLE_VALUE) return;
    //
    // /* Get the number of cells in the current buffer */
    // if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    // cellCount = csbi.dwSize.X *csbi.dwSize.Y;
    //
    // /* Fill the entire buffer with spaces */
    // if (!FillConsoleOutputCharacter(
    //     hStdOut,
    //     (TCHAR) ' ',
    //     cellCount,
    //     homeCoords,
    //     &count
    //     )) return;
    //
    // /* Fill the entire buffer with the current colors and attributes */
    // if (!FillConsoleOutputAttribute(
    //     hStdOut,
    //     csbi.wAttributes,
    //     cellCount,
    //     homeCoords,
    //     &count
    //     )) return;
    //
    // /* Move the cursor home */
    // SetConsoleCursorPosition( hStdOut, homeCoords );

#else

    printf(CONS_RESET); printf(CONS_CLEAR);
#endif
}
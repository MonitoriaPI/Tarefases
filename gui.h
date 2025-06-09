//
// Created by pnich on 09/06/2025.
//

#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>

#include "tarefas_funcs.h"

extern GtkWidget *janela;
extern GtkWidget *grid1;
extern GtkWidget *logo;
extern GtkWidget *lista_de_tarefas;
extern GtkWidget *botao_adicionar_tarefa;
extern GtkWidget *botao_remover_tarefa;
extern GtkWidget *botao_salvar_tarefas;

extern GtkWidget *janela_adicionar_tarefa;
extern GtkWidget *grid2;
extern GtkWidget *label1;
extern GtkWidget *campo_nome_da_tarefa;
extern GtkWidget *botao_sair_tela_adicionar_tarefa;
extern GtkWidget *botao_confirmar_tarefa;

extern GtkBuilder *builder;

void activate(GtkApplication *app);

void adicionar_tarefa_list_box(Tarefa tarefa);
int remover_tarefa_list_box(Tarefa tarefa);

#endif //GUI_H

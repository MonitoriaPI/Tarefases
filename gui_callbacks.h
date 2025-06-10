//
// Created by pnich on 09/06/2025.
//

#ifndef GUI_CALLBACKS_H
#define GUI_CALLBACKS_H
#include <gtk/gtk.h>

void on_botao_adicionar_tarefa_clicked(GtkButton *b);
void sair_tela_adicionar_tarefa(GtkButton *b);
void confirmar_tarefa(GtkButton *b);
void on_botao_remover_tarefa_clicked(GtkButton *b);
void on_botao_salvar_tarefas_clicked(GtkButton *b);
void on_tarefa_marcada(GtkWidget *w, gpointer data);
void on_janela_close_request(GtkWidget *w);

#endif //GUI_CALLBACKS_H

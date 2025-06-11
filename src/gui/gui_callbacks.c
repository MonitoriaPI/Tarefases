//
// Created by pnich on 09/06/2025.
//

#include <gtk/gtk.h>

#include "gui_callbacks.h"

#include "../../dbg.h"
#include "gui.h"

void on_botao_adicionar_tarefa_clicked(GtkButton *b) {
    if (qtdTarefas == QTD_MAX_TAREFAS) {
        gtk_popover_popup(GTK_POPOVER(popover_limite_tarefas));
        return;
    }

    gtk_widget_set_visible(janela_adicionar_tarefa, TRUE);
}

void sair_tela_adicionar_tarefa(GtkButton *b) {
    gtk_widget_set_visible(janela_adicionar_tarefa, FALSE);
}

void confirmar_tarefa(GtkButton *b) {
    GtkEntryBuffer *buff = gtk_entry_get_buffer(GTK_ENTRY(campo_nome_da_tarefa));

    if (gtk_entry_buffer_get_length(buff) == 0) {
        gtk_popover_popup(GTK_POPOVER(popover_confirmar_tarefa));
        return;
    }

    Tarefa novaTarefa = construir_tarefa(
        gtk_entry_buffer_get_text(buff),
        0
    );

    adicionar_tarefa_list_box(novaTarefa);
    adicionar_tarefa(novaTarefa);

    gtk_entry_set_buffer(GTK_ENTRY(campo_nome_da_tarefa), NULL);
    sair_tela_adicionar_tarefa(NULL);
}

void on_botao_remover_tarefa_clicked(GtkButton *b) {
    int i = 0;
    GtkListBoxRow *linhaSelecionada = gtk_list_box_get_selected_row(GTK_LIST_BOX(lista_de_tarefas));
    if (linhaSelecionada == NULL) {
        gtk_popover_popup(GTK_POPOVER(popover_remover_tarefa));
        return;
    }

    int idx = gtk_list_box_row_get_index(linhaSelecionada);
    remover_tarefa(&tarefas[idx]);

    gtk_list_box_remove(GTK_LIST_BOX(lista_de_tarefas), GTK_WIDGET(linhaSelecionada));
}

void on_botao_salvar_tarefas_clicked(GtkButton *b) {
    salvar_tarefas();

    gtk_popover_popup(GTK_POPOVER(popover_salvar_tarefas));
}

void on_tarefa_marcada(GtkWidget *w, gpointer data) {
    int idx = GPOINTER_TO_INT(data);

    mudar_marcaco_tarefa(&tarefas[idx]);
}

void on_janela_close_request(GtkWidget *w) {
    gtk_widget_unparent(popover_remover_tarefa);
    gtk_widget_unparent(popover_confirmar_tarefa);
    gtk_widget_unparent(popover_carregar_tarefas);
    gtk_widget_unparent(popover_limite_tarefas);
    gtk_widget_unparent(popover_salvar_tarefas);
}

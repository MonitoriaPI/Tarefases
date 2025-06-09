//
// Created by pnich on 09/06/2025.
//

#include <gtk/gtk.h>

#include "gui_callbacks.h"
#include "gui.h"

void on_botao_adicionar_tarefa_clicked(GtkButton *b) {
    gtk_widget_set_visible(janela_adicionar_tarefa, TRUE);
}

void sair_tela_adicionar_tarefa(GtkButton *b) {
    gtk_widget_set_visible(janela_adicionar_tarefa, FALSE);
}

void confirmar_tarefa(GtkButton *b) {
    GtkEntryBuffer *buff = gtk_entry_get_buffer(GTK_ENTRY(campo_nome_da_tarefa));

    if (gtk_entry_buffer_get_length(buff) == 0) {
        // TODO botar pop-up
        return;
    }

    Tarefa novaTarefa = construir_tarefa(
        gtk_entry_buffer_get_text(buff),
        0
    );

    adicionar_tarefa(novaTarefa);
    adicionar_tarefa_list_box(novaTarefa);

    gtk_entry_set_buffer(GTK_ENTRY(campo_nome_da_tarefa), NULL);
    sair_tela_adicionar_tarefa(NULL);
}

void on_botao_remover_tarefa_clicked(GtkButton *b) {
    GtkListBoxRow *linhaSelecionada = gtk_list_box_get_selected_row(GTK_LIST_BOX(lista_de_tarefas));
    if (linhaSelecionada == NULL) {
        // TODO pop up
        puts("linha não selecionada");
        return;
    }

    int idx = gtk_list_box_row_get_index(linhaSelecionada);
    remover_tarefa(&tarefas[idx]);

    gtk_list_box_remove(GTK_LIST_BOX(lista_de_tarefas), GTK_WIDGET(linhaSelecionada));
}

void on_botao_salvar_tarefas_clicked(GtkButton *b) {
    salvar_tarefas();

    // TODO pop up
}

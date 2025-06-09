//
// Created by pnich on 09/06/2025.
//
#include <gtk/gtk.h>

#include "gui.h"

#include "gui_callbacks.h"

GtkWidget *janela;
GtkWidget *grid1;
GtkWidget *logo;
GtkWidget *lista_de_tarefas;
GtkWidget *botao_adicionar_tarefa;
GtkWidget *botao_remover_tarefa;
GtkWidget *botao_salvar_tarefas;

GtkWidget *janela_adicionar_tarefa;
GtkWidget *grid2;
GtkWidget *label1;
GtkWidget *campo_nome_da_tarefa;
GtkWidget *botao_sair_tela_adicionar_tarefa;
GtkWidget *botao_confirmar_tarefa;

GtkBuilder *builder;

void activate (GtkApplication *app) {
    builder = gtk_builder_new_from_file("GUI-gtk4.glade");

    janela                  = GTK_WIDGET(gtk_builder_get_object(builder, "janela_principal"));
    grid1                   = GTK_WIDGET(gtk_builder_get_object(builder, "grid1"));
    logo                    = GTK_WIDGET(gtk_builder_get_object(builder, "logo"));
    lista_de_tarefas        = GTK_WIDGET(gtk_builder_get_object(builder, "lista_de_tarefas"));
    botao_adicionar_tarefa  = GTK_WIDGET(gtk_builder_get_object(builder, "botao_adicionar_tarefa"));
    botao_remover_tarefa    = GTK_WIDGET(gtk_builder_get_object(builder, "botao_remover_tarefa"));
    botao_salvar_tarefas    = GTK_WIDGET(gtk_builder_get_object(builder, "botao_salvar_tarefas"));

    janela_adicionar_tarefa             = GTK_WIDGET(gtk_builder_get_object(builder, "janela_adicionar_tarefa"));
    grid2                               = GTK_WIDGET(gtk_builder_get_object(builder, "grid2"));
    label1                              = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    campo_nome_da_tarefa                = GTK_WIDGET(gtk_builder_get_object(builder, "campo_nome_da_tarefa"));
    botao_sair_tela_adicionar_tarefa    = GTK_WIDGET(gtk_builder_get_object(builder, "botao_sair_tela_adicionar_tarefa"));
    botao_confirmar_tarefa              = GTK_WIDGET(gtk_builder_get_object(builder, "botao_confirmar_tarefa"));

    gtk_window_set_application(GTK_WINDOW(janela), app);

    gtk_image_set_from_file(GTK_IMAGE(logo), "logoTarefases.png");

    g_signal_connect(botao_adicionar_tarefa, "clicked", G_CALLBACK(on_botao_adicionar_tarefa_clicked), NULL);
    g_signal_connect(botao_sair_tela_adicionar_tarefa, "clicked", G_CALLBACK(sair_tela_adicionar_tarefa), NULL);
    g_signal_connect(botao_confirmar_tarefa, "clicked", G_CALLBACK(confirmar_tarefa), NULL);
    g_signal_connect(botao_remover_tarefa, "clicked", G_CALLBACK(on_botao_remover_tarefa_clicked), NULL);
    g_signal_connect(botao_salvar_tarefas, "clicked", G_CALLBACK(on_botao_salvar_tarefas_clicked), NULL);

    if (carregar_tarefas() == -1) {
        // TODO pop up
    } else {
        for (int i = 0; i < qtdTarefas; i++)
            adicionar_tarefa_list_box(tarefas[i]);
    }

    g_object_unref(builder);
}

void adicionar_tarefa_list_box(Tarefa tarefa) {
    GtkWidget *linha = gtk_list_box_row_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(linha), box);

    GtkWidget *checkButton = gtk_check_button_new();
    gtk_check_button_set_active(GTK_CHECK_BUTTON(checkButton), tarefa.estaConcluida);

    GtkWidget *label = gtk_label_new(tarefa.descricao);

    gtk_box_append(GTK_BOX(box), checkButton);
    gtk_box_append(GTK_BOX(box), label);

    gtk_list_box_append(GTK_LIST_BOX(lista_de_tarefas), linha);
}


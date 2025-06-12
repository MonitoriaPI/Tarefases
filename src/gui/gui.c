//
// Created by pnich on 09/06/2025.
//
#include <gtk/gtk.h>

#include "gui.h"

#include "../../dbg.h"
#include "gui_callbacks.h"

GtkWidget *janela;
GtkWidget *logo;
GtkWidget *lista_de_tarefas;
GtkWidget *botao_adicionar_tarefa;
GtkWidget *botao_remover_tarefa;
GtkWidget *botao_salvar_tarefas;

GtkWidget *janela_adicionar_tarefa;
GtkWidget *campo_nome_da_tarefa;
GtkWidget *botao_sair_tela_adicionar_tarefa;
GtkWidget *botao_confirmar_tarefa;

GtkWidget *popover_remover_tarefa;
GtkWidget *popover_salvar_tarefas;
GtkWidget *popover_carregar_tarefas;
GtkWidget *popover_confirmar_tarefa;
GtkWidget *popover_limite_tarefas;

GtkWidget *indicadores_das_tarefas[QTD_MAX_TAREFAS];

GtkBuilder *builder;

void activate (GtkApplication *app) {
    //// BOILERPLATE

    // associa o xml ao objeto builder
    builder = gtk_builder_new_from_file("GUI.ui");
    //

    // associa os widgets no xml a objetos no código
    janela                  = GTK_WIDGET(gtk_builder_get_object(builder, "janela_principal"));
    logo                    = GTK_WIDGET(gtk_builder_get_object(builder, "logo"));
    lista_de_tarefas        = GTK_WIDGET(gtk_builder_get_object(builder, "lista_de_tarefas"));
    botao_adicionar_tarefa  = GTK_WIDGET(gtk_builder_get_object(builder, "botao_adicionar_tarefa"));
    botao_remover_tarefa    = GTK_WIDGET(gtk_builder_get_object(builder, "botao_remover_tarefa"));
    botao_salvar_tarefas    = GTK_WIDGET(gtk_builder_get_object(builder, "botao_salvar_tarefas"));

    janela_adicionar_tarefa             = GTK_WIDGET(gtk_builder_get_object(builder, "janela_adicionar_tarefa"));
    campo_nome_da_tarefa                = GTK_WIDGET(gtk_builder_get_object(builder, "campo_nome_da_tarefa"));
    botao_sair_tela_adicionar_tarefa    = GTK_WIDGET(gtk_builder_get_object(builder, "botao_sair_tela_adicionar_tarefa"));
    botao_confirmar_tarefa              = GTK_WIDGET(gtk_builder_get_object(builder, "botao_confirmar_tarefa"));

    popover_remover_tarefa      = GTK_WIDGET(gtk_builder_get_object(builder, "popover_remover_tarefa"));
    popover_salvar_tarefas      = GTK_WIDGET(gtk_builder_get_object(builder, "popover_salvar_tarefas"));
    popover_carregar_tarefas    = GTK_WIDGET(gtk_builder_get_object(builder, "popover_carregar_tarefas"));
    popover_confirmar_tarefa    = GTK_WIDGET(gtk_builder_get_object(builder, "popover_confirmar_tarefa"));
    popover_limite_tarefas      = GTK_WIDGET(gtk_builder_get_object(builder, "popover_limite_tarefas"));
    //

    // conecta as funções callback aos seus respectivos widgets
    g_signal_connect(botao_adicionar_tarefa, "clicked", G_CALLBACK(on_botao_adicionar_tarefa_clicked), NULL);
    g_signal_connect(botao_sair_tela_adicionar_tarefa, "clicked", G_CALLBACK(sair_tela_adicionar_tarefa), NULL);
    g_signal_connect(botao_confirmar_tarefa, "clicked", G_CALLBACK(confirmar_tarefa), NULL);
    g_signal_connect(botao_remover_tarefa, "clicked", G_CALLBACK(on_botao_remover_tarefa_clicked), NULL);
    g_signal_connect(botao_salvar_tarefas, "clicked", G_CALLBACK(on_botao_salvar_tarefas_clicked), NULL);
    g_signal_connect(janela, "close_request", G_CALLBACK(on_janela_close_request), NULL);
    //

    // associa os popovers aos seus respectivos widgets
    gtk_widget_set_parent(popover_remover_tarefa, botao_remover_tarefa);
    gtk_widget_set_parent(popover_salvar_tarefas, botao_salvar_tarefas);
    gtk_widget_set_parent(popover_carregar_tarefas, janela);
    gtk_widget_set_parent(popover_confirmar_tarefa, botao_confirmar_tarefa);
    gtk_widget_set_parent(popover_limite_tarefas, botao_adicionar_tarefa);
    //

    // coloca a imagem no widget do tipo GtkImage
    gtk_image_set_from_file(GTK_IMAGE(logo), "logoTarefases.png");
    //

    // associa a janela principal à inicialização do app
    gtk_window_set_application(GTK_WINDOW(janela), app);
    //

    g_object_unref(builder);
    ////

    if (carregar_tarefas() == -1) {
        gtk_popover_popup(GTK_POPOVER(popover_carregar_tarefas));
    } else {
        for (int i = 0; i < qtdTarefas; i++)
            adicionar_tarefa_list_box(tarefas[i]);
    }
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

    int idx = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(linha));
    indicadores_das_tarefas[idx] = checkButton;

    g_signal_connect(indicadores_das_tarefas[idx], "toggled", G_CALLBACK(on_tarefa_marcada), GINT_TO_POINTER(gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(gtk_widget_get_parent(gtk_widget_get_parent(checkButton))))));

}


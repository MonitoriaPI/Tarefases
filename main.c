#include <stdlib.h>
#include <gtk/gtk.h>

#include "cli.h"

GtkWidget *janela;
GtkWidget *layout1;
GtkWidget *logo_tarefases;
GtkWidget *lista_de_tarefas;
GtkWidget *layout_2;
GtkWidget *botao_adicionar_tarefa;
GtkWidget *botao_remover_tarefa;
GtkWidget *botao_salvar_tarefas;
GtkBuilder *builder;

GtkApplication *app;

void on_window_close_request(GtkWidget *window) {
    g_application_quit(G_APPLICATION(window));
}

static void activate (GtkApplication *app) {
    builder = gtk_builder_new_from_file("GUI-gtk4.glade");

    janela = GTK_WIDGET(gtk_builder_get_object(builder, "janela_principal"));
    gtk_window_set_application(GTK_WINDOW(janela), app);

    GtkWidget *linha1 = gtk_list_box_row_new();
    GtkWidget *linha2 = gtk_list_box_row_new();
    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    gtk_box_append(GTK_BOX(box1), gtk_check_button_new());
    gtk_box_append(GTK_BOX(box1), gtk_label_new("Tarefa 1"));

    gtk_box_append(GTK_BOX(box2), gtk_check_button_new());
    gtk_box_append(GTK_BOX(box2), gtk_label_new("Tarefa 2"));

    gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(linha1), box1);
    gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(linha2), box2);

    lista_de_tarefas = GTK_WIDGET(gtk_builder_get_object(builder, "lista_de_tarefas"));
    gtk_list_box_append(GTK_LIST_BOX(lista_de_tarefas), linha1);
    gtk_list_box_append(GTK_LIST_BOX(lista_de_tarefas), linha2);

    gtk_list_box_row_set_selectable(gtk_list_box_get_row_at_index(GTK_LIST_BOX(lista_de_tarefas), 0), TRUE);
    gtk_list_box_row_set_selectable(gtk_list_box_get_row_at_index(GTK_LIST_BOX(lista_de_tarefas), 1), TRUE);

    GtkWidget *logo = GTK_WIDGET(gtk_builder_get_object(builder, "logo"));
    gtk_image_set_from_file(GTK_IMAGE(logo), "logoTeste.png");

    g_object_unref(builder);
}

int main(int argc, char** argv) {
    int cli = 0;

    if (argc > 1)
        cli = strtol(argv[1], NULL, 10);

    // CLI

    if (cli) {
        return cli_tela_principal();
    }

    // GUI

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    int status = g_application_run (G_APPLICATION (app), argc, argv);

    g_object_unref (app);
    return status;

}
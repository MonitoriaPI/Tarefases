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

static void activate (GtkApplication *app) {
    builder = gtk_builder_new_from_file("GUI-gtk4.glade");

    janela = GTK_WIDGET(gtk_builder_get_object(builder, "janela"));

    gtk_window_set_application(GTK_WINDOW(janela), app);

    //g_signal_connect(janela, "close-request", G_CALLBACK(on_window_close_request), NULL);

    gtk_window_set_title (GTK_WINDOW (janela), "TAREFASES");
    gtk_window_set_default_size (GTK_WINDOW (janela), 200, 200);

    gtk_widget_set_visible(GTK_WIDGET(janela), TRUE);

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

    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    int status = g_application_run (G_APPLICATION (app), argc, argv);

    g_object_unref (app);
    return status;

}
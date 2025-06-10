#include <stdlib.h>
#include <gtk/gtk.h>

#include "cli.h"
#include "gui.h"

int main(int argc, char** argv) {

    int cli = 0;

    if (argc > 1)
        cli = strtol(argv[1], NULL, 10);

    // CLI
    if (cli)
        return cli_tela_principal();
    //

    // GUI
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    int status = g_application_run (G_APPLICATION (app), argc, argv);

    g_object_unref (app);
    return status;
    //
}
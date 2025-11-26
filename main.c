#include <gtk/gtk.h>
#include "interfaz.h"

static void on_activate(GtkApplication *app)
{
    GtkWidget *window = crearInterfaz(app);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("com.jimena.sort", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

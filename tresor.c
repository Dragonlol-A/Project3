#include <stdlib.h>
#include <stdio.h>
#include "tresor_functions.h"



int main(int argc, char *argv[]) {

    chest_randomizer();
    
    //gtk part
    gtk_init(&argc, &argv);

    //window defininition and atributes
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Chasse aux trésor");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //UI generation
    generate_box_and_button(window);

    //button action!
    

    //gtk main (loop)
    gtk_main();

    return 0;
}



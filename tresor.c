#include <stdlib.h>
#include <stdio.h>

#include "tresor_functions.h"



int main(int argc, char *argv[]){

    chest_randomizer();
    
    //gtk part
    gtk_init(&argc, &argv);


    //window defininition and atributes
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Chasse aux trésor");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(program_exit), NULL);

    //UI generation
    if (generate_box_and_button(window) == -1){
        GTK_BUTTONS_CLOSE, GTK_DIALOG_DESTROY_WITH_PARENT;
        fprintf(stderr,"error while alocating memory, please retry");
        exit(EXIT_FAILURE);
    }

    //gtk main (loop)
    gtk_main();
    
    return 0;
}



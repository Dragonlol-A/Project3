#ifndef TRESOR_FUNCTIONS_H
#define TRESOR_FUNCTIONS_H

#include <gtk/gtk.h>

// Function declaration
GtkButton *charge_image_bouton();

int chest_randomizer();


typedef struct {
    GtkWidget *score_label;
    unsigned short chest1_oppened;
    unsigned short chest2_oppened;
    unsigned short chest3_oppened;
    unsigned short empty_chest;
    unsigned short round_end;
} Chest_var;

Chest_var *chest_initialisation();

#endif

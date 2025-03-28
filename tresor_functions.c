#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "tresor_functions.h"



// Global variables
unsigned a;
unsigned score_victory = 0;
unsigned score_lose = 0;
char score_string[45];
Chest_var *chest = NULL; 
GtkButton *restart;


/**********Functions**************/ 
GtkButton *charge_image_bouton() {
    GdkPixbuf *pb_temp = gdk_pixbuf_new_from_file("Images/img1.jpg", NULL);
    if (pb_temp == NULL) {
        printf("Erreur de chargement de l'image images/img1.jpg!\n");
        return NULL;
    }

    GdkPixbuf *pb = gdk_pixbuf_scale_simple(pb_temp, 100, 100, GDK_INTERP_NEAREST);
    g_object_unref(pb_temp);
    if (pb == NULL) {
        printf("Erreur lors de la redimension de l'image!\n");
        return NULL;
    }

    GtkWidget *pBouton = gtk_button_new();
    if (pBouton == NULL) {
        printf("Erreur lors de la création du bouton\n");
        g_object_unref(pb);
        return NULL;
    }

    GtkWidget *image = gtk_image_new_from_pixbuf(pb);
    g_object_unref(pb); // Free pixbuf after attaching to button
    gtk_button_set_image(GTK_BUTTON(pBouton), image);

    return GTK_BUTTON(pBouton);
}


Chest_var *chest_initialisation() {
    Chest_var *created_chest = (Chest_var *)malloc(sizeof(Chest_var));
    if (created_chest == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le coffre.\n");
        return NULL;
    }

    created_chest->chest1_oppened = 0;
    created_chest->chest2_oppened = 0;
    created_chest->chest3_oppened = 0;
    created_chest->empty_chest = 0;
    created_chest->round_end = 0;

    return created_chest;
}


// Function to reset chest values
void reset_chest_values(Chest_var *chest) {
    if (chest == NULL) return;

    chest->chest1_oppened = 0;
    chest->chest2_oppened = 0;
    chest->chest3_oppened = 0;
    chest->empty_chest = 0;
    chest->round_end = 0;
}

// Function to update the score label
void update_score_label_and_reset_state(GtkLabel *score_label, GtkWidget *restart) {
    if (chest->empty_chest == 2) {
        score_lose++;
        chest->empty_chest = 0;
        chest->round_end = 1;
    }

    sprintf(score_string, "Victoires: %u Défaites: %u", score_victory, score_lose);
    gtk_label_set_text(score_label, score_string);

    gtk_widget_set_sensitive(restart, chest->round_end);
}


// Button click functions
void button1_clicked(GtkWidget *widget, gpointer data) {
    GtkLabel *score_label = GTK_LABEL(data);
    if (a == 0 && chest->chest1_oppened == 0 && chest->round_end == 0) {
        chest->chest1_oppened = 1;
        score_victory++;
        chest->round_end = 1;
    } else if (chest->chest1_oppened == 0) {
        chest->chest1_oppened = 1;
        chest->empty_chest++;
    }

    update_score_label_and_reset_state(score_label, restart);
}

void button2_clicked(GtkWidget *widget, gpointer data) {
    GtkLabel *score_label = GTK_LABEL(data);
    if (a == 1 && chest->chest2_oppened == 0 && chest->round_end == 0) {
        chest->chest2_oppened = 1;
        score_victory++;
        chest->round_end = 1;
    } else if (chest->chest2_oppened == 0) {
        chest->chest2_oppened = 1;
        chest->empty_chest++;
    }

    update_score_label_and_reset_state(score_label, restart);
}

void button3_clicked(GtkWidget *widget, gpointer data) {
    GtkLabel *score_label = GTK_LABEL(data);
    if (a == 2 && chest->chest3_oppened == 0 && chest->round_end == 0) {
        chest->chest3_oppened = 1;
        score_victory++;
        chest->round_end = 1;
    } else if (chest->chest3_oppened == 0) {
        chest->chest3_oppened = 1;
        chest->empty_chest++;
    }

    update_score_label_and_reset_state(score_label, restart);
}

void reset_clicked(GtkWidget *widget, gpointer data) {
    reset_chest_values(chest);
    chest_randomizer();
    gtk_widget_set_sensitive(restart, FALSE);
}



void button_action(GtkWidget *button1, GtkWidget *button2, GtkWidget *button3, GtkWidget *restart, GtkWidget *score_label) {
    g_signal_connect(button1, "clicked", G_CALLBACK(button1_clicked), score_label);
    g_signal_connect(button2, "clicked", G_CALLBACK(button2_clicked), score_label);
    g_signal_connect(button3, "clicked", G_CALLBACK(button3_clicked), score_label);
    g_signal_connect(restart, "clicked", G_CALLBACK(reset_clicked), NULL);
}


int chest_randomizer() {
    unsigned short MAX_RAND_VAL = 3;
    srand(time(NULL));
    a = rand() % MAX_RAND_VAL;
    return a;
}


int generate_box_and_button(GtkWidget *window, unsigned a) {
    chest = chest_initialisation(); // Initialize global chest

    if (!chest) return -1;

    GtkWidget *main_box = gtk_vbox_new(FALSE, 10);
    GtkWidget *chest_box = gtk_hbox_new(FALSE, 10);
    GtkWidget *restart_box = gtk_vbox_new(FALSE, 0);
    GtkWidget *score_box = gtk_vbox_new(FALSE, 0);
    GtkWidget *text_box = gtk_vbox_new(FALSE, 0);

    GtkWidget *button1 = charge_image_bouton();
    GtkWidget *button2 = charge_image_bouton();
    GtkWidget *button3 = charge_image_bouton();
    GtkWidget *text_label = gtk_label_new("Choisisez un coffre!");
    restart = GTK_BUTTON(gtk_button_new_with_label("Restart"));

    sprintf(score_string, "Victoires: %u Défaites: %u", score_victory, score_lose);
    chest->score_label = gtk_label_new(score_string);

    button_action(button1, button2, button3, GTK_WIDGET(restart), chest->score_label);

    gtk_box_pack_start(GTK_BOX(chest_box), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chest_box), button2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chest_box), button3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(restart_box), GTK_WIDGET(restart), FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(score_box), chest->score_label, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(text_box), text_label, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(main_box), score_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), text_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), restart_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), chest_box, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_widget_show_all(window);

    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "tresor_functions.h"


//global
unsigned a;
unsigned score_victory;
unsigned score_lose ;
char score_string[45];
unsigned short chest1_oppened = 0;
unsigned short chest2_oppened = 0;
unsigned short chest3_oppened = 0;
unsigned short empty_chest = 0;
unsigned short round_end = 0;

GtkButton *restart;


/*************functions*************/
GtkButton *charge_image_bouton() {
    // 1a. Load the image
    GdkPixbuf *pb_temp = gdk_pixbuf_new_from_file("Images/img1.jpg", NULL);
    if (pb_temp == NULL) {
        printf("Erreur de chargement de l'image images/img1.jpg!\n");
        return NULL;
    }


          // 1b. Resize the image to 100x100 pixels
    GdkPixbuf *pb = gdk_pixbuf_scale_simple(pb_temp, 100, 100, GDK_INTERP_NEAREST);
    if (pb == NULL) {
        printf("Erreur lors de la redimension de l'image!\n");
        g_object_unref(pb_temp); // Free the temporary pixbuf
        return NULL;
          }
          g_object_unref(pb_temp); // Free the original pixbuf after resizing


          GtkWidget *pBouton = gtk_button_new();
    
          if (pBouton == NULL) {
              printf("Erreur lors de la création du bouton\n");
              g_object_unref(pb); // Free the pixbuf
              return NULL;
          }
        
          // 3. Place the image on the button
          GtkWidget *image = gtk_image_new_from_pixbuf(pb);
          if (image == NULL) {
              printf("Erreur lors de la création de l'image\n");
              g_object_unref(pb); // Free the pixbuf
              return NULL;
          }
          gtk_button_set_image(GTK_BUTTON(pBouton), image);
          g_object_unref(pb); // Free the pixbuf after attaching it to the button
      
          return GTK_BUTTON(pBouton);
      }

int generate_box_and_button(GtkWidget *window, unsigned a){
    

    GtkWidget *main_box = gtk_vbox_new(FALSE, 10);
    GtkWidget *chest_box = gtk_hbox_new(FALSE, 10);
    GtkWidget *restart_box = gtk_vbox_new(FALSE,0);
    GtkWidget *score_box = gtk_vbox_new(FALSE,0);
    GtkWidget *text_box = gtk_vbox_new(FALSE,0);

    GtkWidget *button1 = charge_image_bouton(); // Unlabeled button
    GtkWidget *button2 = charge_image_bouton();
    GtkWidget *button3 = charge_image_bouton();
    GtkWidget *text_label = gtk_label_new("Choisisez un coffre!");
    restart = GTK_BUTTON(gtk_button_new_with_label("restart"));


    sprintf(score_string, "Victoires: %u Défaites: %u ", score_victory, score_lose);
    GtkWidget *score_label = gtk_label_new(score_string);

    button_action(button1,button2,button3,restart,score_label);

    if ((button1 ||button2 || button3) == NULL) {
        printf("Erreur lors de la création des bouton \n");
        return -1;
    }


    GTK_LABEL(text_label);
    gtk_box_pack_start(GTK_BOX(chest_box), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chest_box), button2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chest_box), button3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(restart_box), restart, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(score_box), score_label, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(text_box), text_label, FALSE, TRUE, 0);
    

    gtk_box_pack_start(GTK_BOX(main_box), score_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), text_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), restart_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), chest_box, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), main_box);
    
    update_score_label_and_reset_state(score_label,restart);
    gtk_widget_show_all(window);
}


void update_score_label_and_reset_state(GtkLabel *score_label,GtkWidget *restart) {
    if(empty_chest == 2){
        ++score_lose;
        empty_chest = 0;
        round_end =1;
    }
    sprintf(score_string, "Victoires: %u Défaites: %u ", score_victory, score_lose);
    gtk_label_set_text(score_label, score_string);
    if(round_end){
        gtk_widget_set_sensitive ( restart , TRUE );
    }
    else gtk_widget_set_sensitive ( restart , FALSE );
}


void button1_clicked(GtkWidget *widget, gpointer data){
    unsigned oppened = 0;
    if (a==0 && !chest1_oppened && !round_end){
        chest1_oppened=1;
        ++score_victory;
        round_end=1;
        fprintf(stderr, "Button 1 clicked\n");
    }
    else if (!chest1_oppened && !round_end){
        chest1_oppened=1;
        ++empty_chest;
    }

    GtkLabel *score_label = GTK_LABEL(data); 
    update_score_label_and_reset_state(score_label,restart);
}


int button2_clicked(GtkWidget *widget, gpointer data){
    unsigned oppened = 0;
    if(a==1 && !chest2_oppened && !round_end){
        chest2_oppened=1;
        ++score_victory;
        round_end=1;
        fprintf(stderr, "Button 2 clicked\n");
    }
    else if (!chest2_oppened && !round_end) {
        ++empty_chest; 
        chest2_oppened=1; 
    }

    GtkLabel *score_label = GTK_LABEL(data); 
    update_score_label_and_reset_state(score_label,restart);
}

int button3_clicked(GtkWidget *widget, gpointer data){
    if(a==2 && !chest3_oppened && !round_end){
        chest3_oppened=1;
        ++score_victory;
        round_end =1;
        fprintf(stderr, "Button 3 clicked\n");
    }
    else if (!chest3_oppened && !round_end) {
        ++empty_chest;
        chest3_oppened=1;
    }

    GtkLabel *score_label = GTK_LABEL(data); 
    update_score_label_and_reset_state(score_label,restart);
}


int reset_clicked(GtkWidget *widget, gpointer data) {
    chest3_oppened = 0;
    chest2_oppened = 0;
    chest1_oppened = 0;
    empty_chest = 0;
    round_end = 0;
    chest_randomizer();
    gtk_widget_set_sensitive ( restart , FALSE );
    fprintf(stderr,"reset\n");
    return a;
    
}


int button_action(GtkWidget *button1, GtkWidget *button2, GtkWidget *button3, GtkWidget *restart, GtkWidget *score_label){
    g_signal_connect(button1, "clicked", G_CALLBACK(button1_clicked), (score_label));
    g_signal_connect(button2, "clicked", G_CALLBACK(button2_clicked),score_label );
    g_signal_connect(button3, "clicked", G_CALLBACK(button3_clicked), score_label);
    g_signal_connect(restart, "clicked", G_CALLBACK(reset_clicked),NULL);
}


int chest_randomizer(){
    unsigned short MAX_RAND_VAL = 3;

    srand(time(NULL));
    a = rand() % MAX_RAND_VAL;

    return a;
}


#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "tresor_functions.h"

#define IMAGE_WIDTH 100
#define IMAGE_HEIGHT 100
#define CLOSED_CHEST "Images/img1.jpg"
#define EMPTY_CHEST "Images/img2.jpg"
#define TRESURE_CHEST "Images/img3.jpg"




/**********Functions**************/ 
GtkButton *charge_image_bouton() {
    GdkPixbuf *pb_temp=NULL;

    pb_temp = gdk_pixbuf_new_from_file(CLOSED_CHEST, NULL);
    

    if (pb_temp == NULL) {
        fprintf(stderr, "Error loading image Images\n");
        return NULL;
    }

    GdkPixbuf *pb = gdk_pixbuf_scale_simple(pb_temp, IMAGE_WIDTH, IMAGE_HEIGHT, GDK_INTERP_NEAREST);
    g_object_unref(pb_temp);
    if (pb == NULL) {
        fprintf(stderr, "Error resizing the image!\n");
        return NULL;
    }

    GtkWidget *pBouton = gtk_button_new();
    if (pBouton == NULL) {
        fprintf(stderr, "Error creating button\n");
        g_object_unref(pb);
        return NULL;
    }
    

    GtkWidget *image = gtk_image_new_from_pixbuf(pb);
    g_object_unref(pb); 
    gtk_button_set_image(GTK_BUTTON(pBouton), image);

    return GTK_BUTTON(pBouton);
}


Chest_var *chest_initialisation() {
    Chest_var *created_chest = (Chest_var *)malloc(sizeof(Chest_var));
    if (created_chest == NULL) {
        free(created_chest);
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
    chest->chest1_oppened = 0;
    chest->chest2_oppened = 0;
    chest->chest3_oppened = 0;
    chest->empty_chest = 0;
    chest->round_end = 0;
}

// Function to update the score label and lock or unlock the restart button
void update_score_label_and_reset_state(GtkLabel *score_label, GtkWidget *restart, GameState *state) {
    if (state->chest->empty_chest == 2) {

        state->score_lose++;
        state->chest->empty_chest = 0;
        state->chest->round_end = 1;
        sprintf(state->state_string, "Perdu!");
    }
    
    sprintf(state->score_string, "Victoires: %u Défaites: %u", state->score_victory, state->score_lose);
    gtk_label_set_text(score_label, state->score_string);
    gtk_label_set_text(state->chest->state_label, state->state_string);


    if (state->chest->round_end)
        gtk_widget_set_sensitive(restart, TRUE);
    else
        gtk_widget_set_sensitive(restart, FALSE);
    
}

int update_button_image(GtkWidget *widget,unsigned short chest_state){
    GdkPixbuf *pixbuf;
    if(chest_state==1)
        pixbuf = gdk_pixbuf_new_from_file(TRESURE_CHEST, NULL);
    else if(chest_state==2)
        pixbuf = gdk_pixbuf_new_from_file(EMPTY_CHEST, NULL);
    else 
        pixbuf = gdk_pixbuf_new_from_file(CLOSED_CHEST, NULL);
    if (pixbuf) {
        GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, IMAGE_WIDTH, IMAGE_HEIGHT, GDK_INTERP_BILINEAR);
        g_object_unref(pixbuf);

        GtkWidget *new_image = gtk_image_new_from_pixbuf(scaled_pixbuf);
        gtk_button_set_image(GTK_BUTTON(widget), new_image);
        g_object_unref(scaled_pixbuf);
    } else {
        printf("Could not load the image, please check the that the directory is correct\n");
    }}

// Button click functions
void jack_chest_oppener(GtkWidget *widget, gpointer data){
    GameState *state = (GameState *)data;
    int player_choice = NULL;

    if (widget == state->chest_button->button1) player_choice = 0;
    else if (widget == state->chest_button->button2) player_choice = 1;
    else if (widget == state->chest_button->button3) player_choice = 2;


    int jack_chest = NULL;
    for (int i = 0; i < 3; ++i) {
        if (i == player_choice) continue;
        if (i != state->chest_index) {
            jack_chest = i;
            break;
        }
    }

    if (jack_chest == NULL) {
        for (int i = 0; i < 3; ++i) {
            if (i != player_choice) {
                jack_chest = i;
                break;
            }
        }
    }

    switch (jack_chest) {
        case 0:
            state->chest->chest1_oppened = 2;
            state->chest->empty_chest++;
            update_button_image(state->chest_button->button1, 2);
            break;
        case 1:
            state->chest->chest2_oppened = 2;
            state->chest->empty_chest++;
            update_button_image(state->chest_button->button2, 2);
            break;
        case 2:
            state->chest->chest3_oppened = 2;
            state->chest->empty_chest++;
            update_button_image(state->chest_button->button3, 2);
            break;
    }

    state->game_step = 1;

}

void button1_clicked(GtkWidget *widget, gpointer data) {
    GameState *state = (GameState *)data;
    GtkLabel *score_label = GTK_LABEL(state->chest->score_label);

    if (state->game_step==0) jack_chest_oppener(widget, data);
    else{

    if (state->chest_index == 0 && !state->chest->chest1_oppened && !state->chest->round_end) {
        state->chest->chest1_oppened = 1;
        state->score_victory++;
        state->chest->round_end = 1;
        sprintf(state->state_string, "Gagné!");
    } else if (!state->chest->chest1_oppened && !state->chest->round_end) {
        state->chest->chest1_oppened = 2;
        state->chest->empty_chest++;
    }

    if (!state->chest->round_end || state->chest->chest1_oppened == 1) {
        unsigned short chest_state = state->chest->chest1_oppened;
        update_button_image(widget, chest_state);
    }

    update_score_label_and_reset_state(score_label, GTK_WIDGET(state->restart), state);
    }
}

void button2_clicked(GtkWidget *widget, gpointer data) {
    GameState *state = (GameState *)data;
    GtkLabel *score_label = GTK_LABEL(state->chest->score_label);

    if (state->game_step==0) jack_chest_oppener(widget, data);
    else{
    if (state->chest_index == 1 && !state->chest->chest2_oppened && !state->chest->round_end ) {
        state->chest->chest2_oppened = 1;
        state->score_victory++;
        state->chest->round_end = 1;
        sprintf(state->state_string, "Gagné!");
    } else if (!state->chest->chest2_oppened && !state->chest->round_end) {
        state->chest->chest2_oppened = 2;
        state->chest->empty_chest++;
    }

    if(!state->chest->round_end || state->chest->chest2_oppened == 1){
        unsigned short chest_state = state->chest->chest2_oppened;
        update_button_image(widget, chest_state);
    }
    update_score_label_and_reset_state(score_label, GTK_WIDGET(state->restart), state);
    }
}

void button3_clicked(GtkWidget *widget, gpointer data) {
    GameState *state = (GameState *)data;
    GtkLabel *score_label = GTK_LABEL(state->chest->score_label);

    if (state->game_step==0) jack_chest_oppener(widget, data);
    else{

    if (state->chest_index == 2 && !state->chest->chest3_oppened && !state->chest->round_end) {
        state->chest->chest3_oppened = 1;
        state->score_victory++;
        state->chest->round_end = 1;
        sprintf(state->state_string, "Gagné!");
    } else if (!state->chest->chest3_oppened && !state->chest->round_end) {
        state->chest->chest3_oppened = 2;
        state->chest->empty_chest++;
    }
    if(!state->chest->round_end || state->chest->chest3_oppened == 1){
        unsigned short chest_state = state->chest->chest3_oppened;
        update_button_image(widget, chest_state);
    }
    update_score_label_and_reset_state(score_label, GTK_WIDGET(state->restart), state);
    }
}

void reset_clicked(GtkWidget *widget, gpointer data) {
    GameState *state = (GameState *)data;
    reset_chest_values(state->chest);
    sprintf(state->state_string, "choisissez un coffre!");
    gtk_label_set_text(state->chest->state_label, state->state_string);
    state->chest_index = chest_randomizer();
    state->game_step = 0;

    update_button_image(state->chest_button->button1, 0);
    update_button_image(state->chest_button->button2, 0);
    update_button_image(state->chest_button->button3, 0);

    gtk_widget_set_sensitive(GTK_WIDGET(state->restart), FALSE);
}



void button_action(Chest_button *chest_button, GtkWidget *restart, GtkWidget *score_label, GameState *state) {
    g_signal_connect(chest_button->button1, "clicked", G_CALLBACK(button1_clicked), state);
    g_signal_connect(chest_button->button2, "clicked", G_CALLBACK(button2_clicked), state);
    g_signal_connect(chest_button->button3, "clicked", G_CALLBACK(button3_clicked), state);
    g_signal_connect(restart, "clicked", G_CALLBACK(reset_clicked), state);
}


int chest_randomizer() {
    unsigned short MAX_RAND_VAL = 3;

    srand(time(NULL));
    return rand() % MAX_RAND_VAL;
}

void program_exit(GtkWidget *window, gpointer data) {
    GameState *state = (GameState *)data;
    if (state) {
        if (state->chest) free(state->chest);
        if (state->chest_button) free(state->chest_button);
        free(state);
    }
    gtk_widget_destroy(window);
    gtk_main_quit();
}

int generate_box_and_button(GtkWidget *window, GameState *state) {
    state->chest = chest_initialisation();
    
    if(state->chest==NULL) return -1;

    state->chest_button = malloc(sizeof(Chest_button));

    GtkWidget *main_box = gtk_vbox_new(FALSE, 10);
    GtkWidget *chest_box = gtk_hbox_new(FALSE, 10);
    GtkWidget *restart_box = gtk_vbox_new(FALSE, 0);
    GtkWidget *score_box = gtk_vbox_new(FALSE, 0);
    GtkWidget *text_box = gtk_vbox_new(FALSE, 0);

    state->chest_button->button1 = GTK_WIDGET(charge_image_bouton());
    state->chest_button->button2 = GTK_WIDGET(charge_image_bouton());
    state->chest_button->button3 = GTK_WIDGET(charge_image_bouton());

    if((!state->chest_button->button1||!state->chest_button->button2||!state->chest_button->button3)) return -2;
    
    sprintf(state->state_string, "Choisissez un coffre!");
    state->chest->state_label = gtk_label_new(state->state_string);
    
    state->restart = GTK_BUTTON(gtk_button_new_with_label("Restart"));

    sprintf(state->score_string, "Victoires: %u Défaites: %u", state->score_victory, state->score_lose);
    state->chest->score_label = gtk_label_new(state->score_string);

    button_action(state->chest_button, GTK_WIDGET(state->restart), state->chest->score_label, state);

    gtk_box_pack_start(GTK_BOX(chest_box), state->chest_button->button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chest_box), state->chest_button->button2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chest_box), state->chest_button->button3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(restart_box), GTK_WIDGET(state->restart), FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(score_box), state->chest->score_label, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(text_box), state->chest->state_label, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(main_box), score_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), text_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), restart_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), chest_box, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), main_box);

    gtk_widget_set_sensitive(GTK_WIDGET(state->restart), FALSE);

    gtk_widget_show_all(window);

    return 0;
}

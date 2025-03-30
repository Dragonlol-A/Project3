#ifndef TRESOR_FUNCTIONS_H
#define TRESOR_FUNCTIONS_H

#include <gtk/gtk.h>



typedef struct {
    GtkWidget *score_label;
    unsigned short chest1_oppened;
    unsigned short chest2_oppened;
    unsigned short chest3_oppened;
    unsigned short empty_chest;
    unsigned short round_end;
} Chest_var;

typedef struct {
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
} Chest_button;


// Functions declaration

/**
 * 
 * charge_image_bouton
 *
 * load a button with an image and resiz the image
 *
 * @return:a GtkButton with the loaded image, or NULL if an error occurred
 *  
 * @pre: the given image must exist
 *     
 * @post: the button is created with a resized image
 *     
 */
GtkButton *charge_image_bouton();


/**
 * chest_initialisation
 *
 * allocate and initialize the Chest_var structure to default state
 *
 * @return: 
 * -a pointer to the Chest_var structure
 * -null: if failed to allocate memory for the struct   
 *
 * 
 * @post: a Chest_var object is created and all fields are initialized to 0
 *     
 */
Chest_var *chest_initialisation();

/**
 * reset_chest_values
 *
 * reset the fields of Chest_var structure to 0 (default value)
 *
 * @param: chest pointer to the structure: Chest_var  to reset it's values
 *
 * @pre: chest != NULL.
 * @post:  all fields in the chest structure are reset to 0
 * 
 */
void reset_chest_values(Chest_var *chest);


/**
 * update_score_label_and_reset_state
 *
 * update the score label and manage the state of the restart button
 *
 * @param: score_label the GtkLabel to update with the current score
 * @param: restart the GtkButton to enable or disable it
 *
 * @pre: score_label != NULL, restart != NULL
 * @post: the score_label text is updated, the restart button is enabled or disabled
 */
void update_score_label_and_reset_state(GtkLabel *score_label, GtkWidget *restart);

/**
 * update_button_image
 *
 * updates the image displayed on a GtkButton based on the chest state
 *
 * @param: widget GtkButton whose image should be updated
 * @param: chest_state The state of the chest (0: default, 1: opened, 2: empty)
 *
 * @return:
 *    -0 if the image was updated successfully
 *    -1 if an error occurred (e.g., the image could not be loaded)
 *
 * @pre: widget != NULL
 * @post: the image of the button is updated
 *     
 */
int update_button_image(GtkWidget *widget, unsigned short chest_state);

/**
 * button1_clicked
 *
 * manage the click event for the a button, update the chest state and it's image.
 *
 * @param: widget the clicked GtkButton
 * @param: data (the score label)
 *
 * @pre: widget != NULL, data != NULL
 * @post: the chest state is updated, the image on the button is updated
 * 
 */
void button1_clicked(GtkWidget *widget, gpointer data);

/**
 * button2_clicked
 *
 
 * manage the click event for the a button, update the chest state and it's image.
 *
 * @param: widget the clicked GtkButton
 * @param: data (the score label)
 *
 * @pre: widget != NULL, data != NULL
 * @post: the chest state is updated, the image on the button is updated
 * 
 */
void button2_clicked(GtkWidget *widget, gpointer data);

/**
 * button3_clicked
 * manage the click event for the a button, update the chest state and it's image.
 *
 * @param: widget the clicked GtkButton
 * @param: data (the score label)
 *
 * @pre: widget != NULL, data != NULL
 * @post: the chest state is updated, the image on the button is updated
 * 
 */
void button3_clicked(GtkWidget *widget, gpointer data);

/**
 * chest_randomizer
 *
 * Randomly selects a chest to contain the treasure.
 *
 * @return: a random number between 0, 1 or 2
 *
 * @pre: srand should be called beforehand for randomness
 * @post: the chest index (a) is updated
 */
int chest_randomizer();

/**
 * program_exit
 *
 * cleans up resources and exits the program (and hopefully don't cause auny memory leaks)
 *
 * @param: window the main application window
 * @param: data Additional user data (if any)
 *
 * @pre: window != NULL
 * @post: the memory allocated is freed and the GTK main loop is terminated
 */
void program_exit(GtkWidget *window, gpointer data);

/**
 * reset_clicked
 *
 * resets the game state and updates all button images to their default image
 *
 * @param: widget the GtkButton representing the "Restart" button.
 * @param: data which is a pointer to Chest_button structure which contain all the game buttons.
 *
 * @pre: widget != NULL, data != NULL.
 * @post: the game state is reset and the images on all game buttons are updated to the default
 */
void reset_clicked(GtkWidget *widget, gpointer data);

/**
 * generate_box_and_button
 *
 * create and set up the UI for the game
 *
 * @param: window the main application window is to contain the UI
 * @param: a the index of the chest containing the treasure
 *
 * @return:
 *    -0 if the UI is successfully created.
 *    -1 if an error occurred (memory allocation error)
 *
 * @pre: window != NULL.
 * @post: the UI components are added to the window and initialized
 */
int generate_box_and_button(GtkWidget *window, unsigned a);


#endif

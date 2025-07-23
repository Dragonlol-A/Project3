#include <stdlib.h>
#include <stdio.h>

#include "tresor_functions.h"



int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GameState *state = malloc(sizeof(GameState));
    if (!state) exit(EXIT_FAILURE);

    state->chest_index = chest_randomizer();
    state->score_victory = 0;
    state->score_lose = 0;
    state->chest = NULL;
    state->chest_button = NULL;
    state->restart = NULL;
    state->game_step = 0;
    state->initial_player_choice = -1;
    state->chest_oppened_by_ghost = -1;

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Chasse aux trésor");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(program_exit), state);

    switch (generate_box_and_button(window, state)) {
        case -1:
            fprintf(stderr, "Error allocating memory for the chest.\n");
            free(state);
            exit(EXIT_FAILURE);
        case -2:
            fprintf(stderr, "Error loading image for the button.\n");
            free(state);
            exit(EXIT_FAILURE);
        default:
            break;
    }

    gtk_main();
    return 0;
}



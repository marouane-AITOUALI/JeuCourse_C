/**
 * \file main.c
 * \brief Boucle de jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date  20  decembre  2021
 */

#include "constants.h"
#include "data.h"
#include "graphics.h"
#include "events.h"

int main() {

    SDL_Event event;
    world_t world;
    resources_t textures;
    SDL_Renderer *renderer;
    SDL_Window *fenetre;

    time_t t;
    srand((unsigned) time(&t));
    world.time_debut_jeu = t;

    init_game(&fenetre, &renderer, &textures, &world);

    while (!is_game_over(&world)) {
        if (world.stop_menu == 0) {
            handle_events(&event, renderer, &world, &textures);
            update_menu(&world, &textures, renderer);
            refresh_menu(renderer, &world, &textures);
        } else {
            refresh_graphics(renderer, &world, &textures);
            update_data(&world, &textures, renderer);
            handle_events(&event, renderer, &world, &textures);
        }
        SDL_Delay(4);
    }


    clean(fenetre, renderer, &textures, &world);

    SDL_Quit();
    return 0;
}

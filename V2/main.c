/**
 * \file main.c
 * \brief Boucle de jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 26 septembre 2021
 */

 
#include <stdio.h>
#include <stdlib.h>

#include "sdl2.h"
#include "sdl2-ttf.h"
#include "const.h"
#include "graphics.h"
#include "logic.h"
#include "data.h"
#include "event.h"



/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param ressources les ressources
 * \param world le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *ressources, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_ttf();
    init_data(world);
    init_textures(*renderer,ressources);
}


/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param ressources les ressources
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *ressources, world_t * world){
    clean_data(world);
    clean_textures(ressources);
    clean_ttf();
    clean_sdl(renderer,window);
}


/**
* \brief fonction qui permet de relancer la boucle de jeu après une partie finie
* \param world le monde
*/
void re_init(world_t * world)
{
    clean_data(world);
    init_data(world);
    world->t0 = SDL_GetTicks();
}



/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main(int argc, char* args[])
{
    SDL_Event event;
    world_t world;
    ressources_t ressources;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&ressources,&world);

    //affichage du menu dans le début 
    print_menu_debut(renderer, &ressources, &world);
    while(1) {
        if(SDL_PollEvent(&event)) {
            //ENTRER est pressée
            if(event.key.keysym.sym == SDLK_RETURN
            || event.key.keysym.sym == SDLK_RETURN2
            || event.key.keysym.sym == SDLK_KP_ENTER) { break; }

            //ECHAP ou si on quitte
            if(event.type == SDL_QUIT
            || event.key.keysym.sym == SDLK_ESCAPE)
            {
                clean(window,renderer,&ressources,&world);
                return 0;
            }
        }
    }

    world.t0 = SDL_GetTicks();

    while(1){ //tant que le jeu n'est pas fini
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer, &world,&ressources);

        //pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);

        if(is_game_over(&world))
        {
            pause(1500);

            //afichage du menu dans la fin du jeu 
            print_menu_fin(renderer, &ressources, &world);
            while(1) {
                if(SDL_PollEvent(&event)) {
                    //ENTRER est pressée
                    if(event.key.keysym.sym == SDLK_RETURN
                    || event.key.keysym.sym == SDLK_RETURN2
                    || event.key.keysym.sym == SDLK_KP_ENTER) { re_init(&world); break;}
                    
                    //ECHAP ou si on quitte
                    if(event.type == SDL_QUIT
                    || event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        clean(window,renderer,&ressources,&world);
                        return 0;
                    }
                }
            }
        }
    }

    //Jamais atteint
    return 0;
}

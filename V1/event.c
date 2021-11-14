/**
 * \file event.c
 * \brief Gestion des entrées claviers du joueur
 * \author DJERMOUNI Yanis - YATIME Marouane
 * \date 26 mai 2021
 */
#include <stdio.h>
#include <stdlib.h>

#include "sdl2.h"
#include "const.h"
#include "event.h"
#include "data.h"

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event, world_t *world){
    while( SDL_PollEvent( event ) ) {
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = EXIT;
        }
       
         //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            if(event->key.keysym.sym == SDLK_ESCAPE) //Echap
                world->gameover = EXIT;
            if(event->key.keysym.sym == SDLK_LEFT) //Fleche de gauche
                world->spaceship.spaceship.x -= MOVING_STEP;
            if(event->key.keysym.sym == SDLK_RIGHT) //Fleche de droite
                world->spaceship.spaceship.x += MOVING_STEP;
            if(event->key.keysym.sym == SDLK_DOWN) //Fleche du bas
                world->vy -=5;
            if(event->key.keysym.sym == SDLK_UP) //Fleche du haut
                world->vy +=5;
            if(event->key.keysym.sym == SDLK_SPACE)
                init_bullet(&world->spaceship);
        }
    }
}

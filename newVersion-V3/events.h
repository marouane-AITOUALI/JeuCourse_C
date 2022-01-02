/**
 * \file event.h
 * \brief Gestion des entrées claviers du joueur
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 20  decembre  2021
 */

#ifndef V1_EVENTS_H
#define V1_EVENTS_H

#include <SDL2/SDL_mixer.h>
#include "constants.h"
#include "data.h"

//getion des evenements du jeu et les parametres
void handle_events(SDL_Event *event, SDL_Renderer *renderer, world_t *world, resources_t *textures);

#endif //V1_EVENTS_H

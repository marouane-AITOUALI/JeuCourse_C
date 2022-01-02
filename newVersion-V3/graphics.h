/**
 * \file graphics.h
 * \brief Gestion de l'affichage du jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 26 septembre 2021
 */

#ifndef V1_GRAPHICS_H
#define V1_GRAPHICS_H


#include "constants.h"
#include "data.h"
#include "liste.h"
#include "fonctions_SDL.h"



void init_textures(SDL_Renderer *renderer, resources_t *textures, world_t *world);

void refresh_menu(SDL_Renderer *renderer, world_t *world, resources_t *textures);

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *textures);

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

void clean(SDL_Window *window, SDL_Renderer *renderer, resources_t *textures, world_t *world);

void clean_textures(resources_t *textures);


#endif //V1_GRAPHICS_H

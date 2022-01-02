/**
 * \file graphics.h
 * \brief Gestion de l'affichage du jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 26 septembre 2021
 */
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <stdio.h>
#include <stdlib.h>

#include "sdl2.h"
#include "sdl2-ttf.h"
#include "const.h"



/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/
struct ressources_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* spaceship; /*!< Texture liée au vaisseau affiché sur l'écran. */
    SDL_Texture* finish_line; /*!< Texture liée à la ligne d'arrivée affiché sur l'écran. */
    SDL_Texture* meteorite; /*!< Texture liée au météorite sur l'écran. */
    SDL_Texture* bullet; /*!< Texture liée à la bullet sur l'écran. */
    TTF_Font* font; /*!< Police d'écriture utilisé */
};
/**
 * \brief Type qui correspond aux textures du jeu
*/
typedef struct ressources_s ressources_t;



#include "data.h"



void init_textures(SDL_Renderer *renderer, ressources_t *ressources);
void clean_textures(ressources_t *ressources);
void apply_background(SDL_Renderer *renderer, SDL_Texture *texture);
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t* sprite);
void apply_bullets(SDL_Renderer *renderer, SDL_Texture *texture, bullets_t *bullets);
void print_all_text(SDL_Renderer *renderer, ressources_t *ressources, world_t *world);
void print_menu_debut(SDL_Renderer *renderer, ressources_t *ressources, world_t *world);
void print_menu_fin(SDL_Renderer *renderer, ressources_t *ressources, world_t *world);
void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *ressources);



#endif
/**
 * \file data.h
 * \brief Gestion des données du jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 26 septembre 2021
 */
 
#ifndef __DATA_H__
#define __DATA_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sdl2.h"
#include "sdl2-ttf.h"
#include "const.h"




enum{
    SPACESHIP,
    BULLET,
    METEORE,
    FINISH_LINE,
    BACKGROUND,
};


enum{
    CONTINUE,
    EXIT,
    LOOSE,
    WIN,
};



/**
 * \brief Représentation du sprite
*/
struct sprite_s{
    double x; /*!<L'abscisse au centre*/
    double y; /*!<L'ordonnée au centre*/
    double w; /*!<largeur*/
    double h; /*!<hauteur*/
    char is_visible; /*!< Champ indiquant si le sprite est visible */
    int type; /*!< Champ indiquant le type de sprite (cf l'enum de ce fichier) */
};
/**
 * \brief Type qui correspond aux sprite
 */
typedef struct sprite_s sprite_t  ;




/**
 * \brief Représentation des bullets
*/
struct bullet_s{
    sprite_t bullet;
    double vy;
};
/**
 * \brief Type qui correspond aux bullet
 */
typedef struct bullet_s bullet_t;


/**
 * \brief Représentation des bullets
*/
struct bullets_s{
    bullet_t bullet[NB_BULLETS];
    int bullet_nb;
};
/**
 * \brief Type qui correspond aux bullets
 */
typedef struct bullets_s bullets_t;


/**
 * \brief Représentation d'un spaceship
*/
struct spaceship_s{
    sprite_t spaceship;
    bullets_t bullets;
};
/**
 * \brief Type qui correspond à un spaceship
 */
typedef struct spaceship_s spaceship_t;


/**
 * \brief Représentation du monde du jeu
*/
struct world_s{
    spaceship_t spaceship;
    sprite_t background;
    sprite_t finish_line;
    double vy; /*!< Champ indiquant la vitesse sur l'axe des y */
    
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */

    Uint32 t0; /*!<Ticks de la première frame (SDL_GetTicks()) */
};
/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;



#include "graphics.h"



int is_game_over(world_t *world);
void init_spaceship(spaceship_t *spaceship);
void init_sprite(sprite_t *sprite, double x, double y, double w, double h, int type);
void init_data(world_t *world);
void init_bullet(spaceship_t *spaceship);
void clean_data(world_t *world);

void update_background(world_t* world);
void update_data(world_t *world);

#endif
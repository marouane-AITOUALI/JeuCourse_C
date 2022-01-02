/**
 * \file collision.h
 * \brief Gestion des collisions du jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 20  decembre  2021
 */

#ifndef V1_COLISION_H
#define V1_COLISION_H

#include "data.h"
#include "logic.h"

/**
 * @brief gestion des collision entre car et les autre voitures 
 * 
 * @param world 
 * @param sp1 
 * @param sp2 
 */
void handle_Main_Enemy_collision(world_t *world, sprite_t *sp1, sprite_t *sp2);

/**
 * @brief gestion entre car et les boulles 
 * 
 * @param world 
 * @param sp1 
 * @param sp2 
 */
void handle_Bullet_Enemy_collision(world_t *world, sprite_t *sp1, sprite_t *sp2);


/**
 * @brief gestion de la colision avec les barrage 
 * 
 * @param sp1 
 * @param sp2 
 * @param world 
 * @param textures 
 * @param renderer 
 */
void handle_Main_Barrage_collision(sprite_t *sp1, sprite_t *sp2, world_t *world, resources_t *textures,
                                   SDL_Renderer *renderer);


#endif //V1_COLISION_H

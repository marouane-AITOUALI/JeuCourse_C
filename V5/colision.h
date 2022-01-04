/**
 * \file collision.h
 * \brief Gestion des collisions du jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 3  janvier  2022 */

#ifndef V1_COLISION_H
#define V1_COLISION_H

#include "data.h"
#include "logic.h"

void handle_Main_Enemy_collision(world_t *world, sprite_t *sp1, sprite_t *sp2);

void handle_Bullet_Enemy_collision(world_t *world, sprite_t *sp1, sprite_t *sp2);

void handle_Main_Barrage_collision(sprite_t *sp1, sprite_t *sp2, world_t *world, resources_t *textures,
                                   SDL_Renderer *renderer);


#endif //V1_COLISION_H

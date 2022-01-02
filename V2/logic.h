/**
 * \file logic.h
 * \brief Gestion de la logique du jeu (physique)
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 26 septembre 2021
 */
#ifndef __LOGIC_H__
#define __LOGIC_H__

#include <stdio.h>
#include <stdlib.h>

#include "sdl2.h"
#include "sdl2-ttf.h"
#include "const.h"
#include "data.h"



void screen_collide(sprite_t* s);
int sprites_collide(sprite_t *sp1, sprite_t *sp2);
void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t *world);



#endif
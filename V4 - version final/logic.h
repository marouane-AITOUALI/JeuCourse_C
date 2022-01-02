/**
 * \file logic.h
 * \brief Gestion de la logique du jeu (physique)
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 27 decembre  2021
 */

#ifndef V1_LOGIC_H
#define V1_LOGIC_H

#include "data.h"

double distance(sprite_t s1, sprite_t s2);

int sprites_collide(sprite_t* sp1, sprite_t* sp2);


#endif //V1_LOGIC_H

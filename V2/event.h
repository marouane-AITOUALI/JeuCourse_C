/**
 * \file event.h
 * \brief Gestion des entrées claviers du joueur
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 26 septembre 2021
 */
#ifndef __EVENT_H__
#define __EVENT_H__

#include <stdio.h>
#include <stdlib.h>

#include "sdl2.h"
#include "sdl2-ttf.h"
#include "const.h"
#include "data.h"



void handle_events(SDL_Event *event, world_t *world);



#endif
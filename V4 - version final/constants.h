/**
 * \file const.h
 * \brief Rassemblement des constantes utiles au jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 27 decembre  2021
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>


#include "fonctions_SDL.h"


#ifndef V1_CONSTANTS_H
#define V1_CONSTANTS_H


#define SCREEN_WIDTH 840

#define SCREEN_HEIGHT 650

#define RICK_STEP 50

#define SPEED_LIIMIT 10

#define NUMBER_ENEMY_CAR 5

#define NUMBER_LIFES 10

#define NUMBER_BARRAGE 50

#define NUMBER_ROADS 100


struct resources_s {

    SDL_Texture *main_car;

    SDL_Texture *enemy_car;

    SDL_Texture *barrage;

    SDL_Texture *road;

    SDL_Texture *bullet;

    SDL_Texture *menu;

    SDL_Texture *exit_button;

    SDL_Texture *new_game_button;

    SDL_Texture *settings_button;

    TTF_Font *font;
};
typedef struct resources_s resources_t;

#endif

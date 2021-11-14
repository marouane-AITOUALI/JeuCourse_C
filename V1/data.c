/**
 * \file data.c
 * \brief Gestion des données du jeu
 * \author DJERMOUNI Yanis - YATIME Marouane
 * \date 26 mai 2021
 */
#include <stdio.h>
#include <stdlib.h>

#include "sdl2.h"
#include "const.h"
#include "graphics.h"
#include "logic.h"
#include "data.h"



/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world){
    if(world->gameover != CONTINUE)
        return 1;
    return 0;
}



void init_bullet(spaceship_t *spaceship)
{
    if(spaceship->bullets.bullet_nb+1 < NB_BULLETS)
    {
        init_sprite(&spaceship->bullets.bullet[spaceship->bullets.bullet_nb].bullet, spaceship->spaceship.x + SHIP_SIZE/2 - BULLET_SIZE/2, spaceship->spaceship.y, BULLET_SIZE, BULLET_SIZE, BULLET);
        spaceship->bullets.bullet[spaceship->bullets.bullet_nb].vy = 0.02*INITIAL_SPEED;
        spaceship->bullets.bullet_nb++;
    }
}


/**
 * \brief La fonction initialise le spaceship
 * \param spaceship le spaceship
 */
void init_spaceship(spaceship_t *spaceship)
{
    init_sprite(&spaceship->spaceship, SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, SPACESHIP);
    spaceship->bullets.bullet_nb = 0; // pas utilisé au départ
}


/**
 * \brief La fonction initialise un sprite
 * \param sprite le sprite
 * \param x abscisse
 * \param y ordonnée
 * \param w largeur
 * \param h hauteur
 */
void init_sprite(sprite_t *sprite, double x, double y, double w, double h, int type){
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
    sprite->is_visible = 1;
    sprite->type = type;
}


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t *world){
    init_sprite(&world->finish_line, 0, -60000, SCREEN_WIDTH, FINISH_LINE_HEIGHT, FINISH_LINE);
    init_spaceship(&world->spaceship);
    init_sprite(&world->background, 0, -SCREEN_HEIGHT*100, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND);
    world->vy = INITIAL_SPEED;

    //on n'est pas à la fin du jeu
    world->gameover = CONTINUE;
}


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    
}



void update_bullets(world_t *world)
{
   
        for(int j = 0; j < world->spaceship.bullets.bullet_nb; j++)
        {
            if(!world->spaceship.bullets.bullet[j].bullet.is_visible)
                world->spaceship.bullets.bullet[j].vy = -world->vy;
            world->spaceship.bullets.bullet[j].bullet.y -= world->spaceship.bullets.bullet[j].vy;
           
        }
    
}

void update_background(world_t* world){
    world->background.y += world->vy;
}

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param renderer
 * \param world les données du monde
 */
void update_data(world_t *world){
    //world->finish_line.y += world->vy;
    screen_collide(&world->spaceship.spaceship);
    handle_sprites_collision(&world->spaceship.spaceship, &world->finish_line, world);
    update_bullets(world);
    update_background(world);
}


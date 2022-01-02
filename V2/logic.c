/**
 * \file logic.c
 * \brief Gestion de la logique du jeu (physique)
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 26 septembre 2021
 */
#include <stdio.h>
#include <stdlib.h>

#include "sdl2.h"
#include "const.h"

#include "logic.h"
#include "data.h"



/**
 * \brief gere les collisions entre le sprite et l'écran (gauche et droite)
 * \param s le sprite
 */
void screen_collide(sprite_t* sprite)
{
    //left
    if(sprite->x < 145)  // Trouvé a l aide des pixels du background
        sprite->x = 145;
    //right
    if(sprite->x + sprite->w > 700)  // 700 taille de la piste de route 
        sprite->x = 700 - sprite->w;
}


/**
 * \brief gere les collisions entre deux sprites
 * \param sp1 un sprite
 * \param sp2 un sprite
 * \return 1 si collision, 0 sinon
 */
int sprites_collide(sprite_t *sp1, sprite_t *sp2){
    if(abs(sp1->x + sp1->w/2 - sp2->x - sp2->w/2) <= (sp1->w + sp2->w)/2 && abs(sp1->y + sp1->h/2 - sp2->y - sp2->h/2) <= (sp1->h + sp2->h)/2)
        return 1;
    return 0;
}


/**
 * \brief rend la vitesse(world.vy) nulle lors de la collision
 * \param sp1 un sprite
 * \param sp2 un sprite
 * \param world les données du monde
 * \param make_disappear vaut 1 si on doit faire disparaître le sprite, 0 si on ne veut pas, autre cas particulier
 * \return 1 si une meteore doit être détruite, 0 sinon
 */
void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t *world)
{
    if(sprites_collide(sp1, sp2) == 1)
    {
        if((sp1->type == SPACESHIP && sp2->type == FINISH_LINE) || (sp2->type == SPACESHIP && sp1->type == FINISH_LINE))
        {
            world->spaceship.spaceship.is_visible = 0;
            world->gameover = WIN;
        }
        else if(((sp1->type == SPACESHIP && sp2->type != FINISH_LINE) || (sp2->type == SPACESHIP && sp1->type != FINISH_LINE)) && (sp1->is_visible && sp2->is_visible))
        {
            world->spaceship.spaceship.is_visible = 0;
            world->gameover = LOOSE;
        }
        else if((sp1->type == BULLET && sp2->type == METEORE && sp2->is_visible) || (sp2->type == BULLET && sp1->type == METEORE && sp1->is_visible))
        {
            sp2->is_visible = 0;
            sp1->is_visible = 0;
        }

    }
    if(world->gameover == CONTINUE)
        world->gameover = CONTINUE;
}

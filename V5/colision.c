/**
 * \file collision.c
 * \brief Gestion des collisions du jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 3  janvier  2022 */

#include "colision.h"
#include "liste.h"
#include <stdio.h>

void handle_Main_Barrage_collision(sprite_t *sp1, sprite_t *sp2, world_t *world, resources_t *textures,
                                   SDL_Renderer *renderer) {
    if (sprites_collide(sp1, sp2)) {
        sp1->direction = 2;
        tout_deplacer(world, renderer, textures);
        sp1->direction = 0;
        sp1->speed = 0;
    }
}

void handle_Main_Enemy_collision(world_t *world, sprite_t *sp1, sprite_t *sp2) {

    if (sprites_collide(sp1, sp2)) {

        int push = 200 + (rand() % (100 * world->Main_car.speed));

        if (world->Main_car.life > 0) {
            world->Main_car.life--;
            if (world->Main_car.life <= 0 && world->dead == 0) {
                world->dead = 1;
                world->time_mort = time(NULL);
            }

            if (sp1->position.x <= sp2->position.x) {
                if (sp1->position.y <= sp2->position.y) {
                    sp2->position.x += push;
                    sp2->position.y += push;
                } else {
                    sp2->position.x += push;
                    sp2->position.y -= push;
                }
            } else {
                if (sp1->position.y <= sp2->position.y) {
                    sp2->position.x -= push;
                    sp2->position.y += push;
                } else {
                    sp2->position.x += push;
                    sp2->position.y -= push;
                }
            }
        }

    }
}


void handle_Bullet_Enemy_collision(world_t *world, sprite_t *sp1, sprite_t *sp2) {

    if (sprites_collide(sp1, sp2)) {

        int recul = 100 + (rand() % 100);

        if (sp1->position.x <= sp2->position.x) {
            if (sp1->position.y <= sp2->position.y) {
                sp2->position.x += recul;
            } else {
                sp2->position.x += recul;
            }
        } else {
            if (sp1->position.y <= sp2->position.y) {
                sp2->position.x -= recul;
            } else {
                sp2->position.x += recul;
            }
        }


        if (sp2->life > 0) {
            sp2->life--;
            int temp = 0;
            temp = sp2->h;
            sp2->h = sp2->w;
            sp2->w = temp;
            sp2->direction = sp1->direction;
            if (sp1->direction != 1) {
                sp2->position.x -= sp2->w;
            }
        }

        sp2->count = 0;


        sp1->position.x = 100000;
        sp1->position.y = 100000;
    }
}



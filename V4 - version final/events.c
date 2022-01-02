/**
 * \file events.c
 * \brief Gestion des entrées claviers du joueur
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 27 decembre  2021
 */

#include "events.h"
#include "constants.h"
#include "data.h"
#include "colision.h"
#include "liste.h"


void handle_events(SDL_Event *event, SDL_Renderer *renderer, world_t *world, resources_t *textures) {

    while (SDL_PollEvent(event)) {

        if (world->stop_menu == 0) {
            if (event->type == SDL_MOUSEMOTION) {
                world->mouse.position.x = event->button.x;
                world->mouse.position.y = event->button.y;
            }
            if (event->type == SDL_MOUSEBUTTONDOWN) {
                if (sprites_collide(&world->mouse, &world->new_game_menu)) {
                    world->stop_menu = 1;
                }
            }
            if (event->type == SDL_MOUSEBUTTONDOWN) {
                if (sprites_collide(&world->mouse, &world->exit_menu)) {
                    world->gameover = 1;
                }
            }
        } else if (world->Main_car.life > 0 && world->dead != 1) {
            if (event->type == SDL_MOUSEBUTTONDOWN) {
                if (event->button.button == SDL_BUTTON_LEFT) {
                    sprite_t temp_sprite;
                    int x, y;
                    int direction;
                    if (world->Main_car.dir_texture == 3) {
                        x = world->Main_car.position.x - world->Main_car.w;
                        y = world->Main_car.position.y + 0.07 * world->Main_car.h;
                        direction = 3;
                    } else if (world->Main_car.dir_texture == 1) {
                        x = world->Main_car.position.x + world->Main_car.w;
                        y = world->Main_car.position.y + 0.07 * world->Main_car.h;
                        direction = 1;
                    } else if (world->Main_car.dir_texture == 2) {
                        x = world->Main_car.position.x + 20;
                        y = world->Main_car.position.y + 30;
                        direction = 2;
                    } else if (world->Main_car.dir_texture == 0) {
                        x = world->Main_car.position.x;
                        y = world->Main_car.position.y - 100;
                        direction = 0;
                    }

                    temp_sprite = init_sprite(temp_sprite, x, y, 16, 16, 50, 1, Bullet);
                    temp_sprite.direction = direction;
                    world->nb_bullets++;
                    world->bullet = ajouter(world->bullet, temp_sprite);
                }

            }

            if (event->type == SDL_KEYDOWN) {
                if (event->key.keysym.sym == SDLK_UP) {
                    world->Main_car.direction = 0;
                    world->Main_car.dir_texture = 0;
                    world->Main_car.direction = 0;
                    if (world->Main_car.speed < SPEED_LIIMIT) {
                        world->Main_car.speed++;
                    }
                } else if (event->key.keysym.sym == SDLK_RIGHT) {
                    world->Main_car.direction = 0;
                    if (world->Main_car.position.x < SCREEN_WIDTH - world->Main_car.w) {
                        world->Main_car.position.x += 15;
                    }
                } else if (event->key.keysym.sym == SDLK_DOWN) {

                    if (world->Main_car.speed > 0) {
                        world->Main_car.speed--;
                    }
                } else if (event->key.keysym.sym == SDLK_LEFT) {
                    world->Main_car.direction = 0;
                    if (world->Main_car.position.x > world->Main_car.w) {
                        world->Main_car.position.x -= 15;
                    }
                } else if (event->key.keysym.sym == SDLK_ESCAPE) {
                    world->stop_menu = 0;
                }
            }
        }
    }
}
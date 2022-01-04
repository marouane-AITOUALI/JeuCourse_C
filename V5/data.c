/**
 * \file data.c
 * \brief Gestion des données du jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 3  janvier  2022 */

#include "data.h"
#include "graphics.h"
#include "liste.h"
#include "logic.h"
#include "colision.h"
#include <stdio.h>


void init_sprite_ptr(sprite_t *sprite, int x, int y, int w, int h, int v, int life, nature_t nat) {
    sprite->direction = 0;
    sprite->dir_texture = 3;
    sprite->count = 0;
    sprite->position.y = y;
    sprite->h = h;
    sprite->w = w;
    sprite->disappear = 0;
    sprite->speed = v;
    sprite->life = life;
    sprite->nature = nat;
    sprite->position.x = x;
}


sprite_t init_sprite(sprite_t sprite, int x, int y, int w, int h, int v, int life, nature_t nat) {
    sprite.dir_texture = 3;
    sprite.count = 0;
    sprite.h = h;
    sprite.w = w;
    sprite.disappear = 0;
    sprite.speed = v;
    sprite.life = life;
    sprite.nature = nat;
    sprite.position.x = x;
    sprite.position.y = y;
    sprite.direction = 0;
    return sprite;
}


void init_data(world_t *world) {

    srand(time(NULL));
    world->mouse = init_sprite(world->mouse, (SCREEN_WIDTH) / 2, (SCREEN_HEIGHT) / 2, 1, 1, 1, 1, Menu);

    world->Enemy_car = l_vide();
    world->Barrage = l_vide();
    world->Road = l_vide();
    world->bullet = l_vide();
    world->gameover = 0;
    world->nb_bullets = 0;
    world->stop_menu = 0;
    world->dead = 0;




    world->Menu = init_sprite(world->Menu, (SCREEN_WIDTH) / 2,
                              (SCREEN_HEIGHT) / 2,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              1, 1, Menu);


    world->new_game_menu = init_sprite(world->new_game_menu, 150, 100,
                                       200,
                                       100,
                                       1, 1, Menu);

    world->settings_menu = init_sprite(world->settings_menu, 400,
                                       100,
                                       200,
                                       100,
                                       1, 1, Menu);

    world->exit_menu = init_sprite(world->exit_menu, 650,
                                   100,
                                   200,
                                   100,
                                   1, 1, Menu);


    init_sprite_ptr(&world->Main_car, SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 4, 45, 100, 6, 10, Main_car);

    world->ligne_arivee = init_sprite(world->ligne_arivee, 0, -50*650, SCREEN_WIDTH, 247, 1,1,Finish_line);


    for (int i = 0; i < NUMBER_ROADS; i++) {

        int x = SCREEN_WIDTH / 2;
        int y = ((i + 2) * 650) - (650 * NUMBER_ROADS);

        sprite_t temp_sprite;
        temp_sprite = init_sprite(temp_sprite, x, y, 840, 650, 1, 1, Road);
        world->Road = ajouter(world->Road, temp_sprite);
    }


    for (int i = 0; i < NUMBER_ENEMY_CAR; i++) {

        int x = i * 20;

        int y = 1500 + i*500;

        sprite_t temp_sprite;
        temp_sprite = init_sprite(temp_sprite, x, y, 45, 100, 7, 4, Enemy_car);
        world->Enemy_car = ajouter(world->Enemy_car, temp_sprite);
    }


    for (int i = 0; i < NUMBER_BARRAGE; i++) {

        int x = rand() % (SCREEN_WIDTH - 110);
        int y = -500 - (rand() % NUMBER_ROADS * 650);

        sprite_t temp_sprite;
        temp_sprite = init_sprite(temp_sprite, x, y, 210, 109, 1, 1, Barrage);
        world->Barrage = ajouter(world->Barrage, temp_sprite);
    }


}


void init_game(SDL_Window **window, SDL_Renderer **renderer, resources_t *textures, world_t *world) {
    init_ttf();
    init_sdl(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer, textures, world);

}


void update_menu(world_t *world, resources_t *textures, SDL_Renderer *renderer) {

}


void update_data(world_t *world, resources_t *textures, SDL_Renderer *renderer) {
    move_enemy_car(world, textures, renderer);
    move_bullets(world, textures, renderer);
    tout_deplacer(world, renderer, textures);

    if(world->Main_car.position.y <= world->ligne_arivee.position.y){
        world->gameover=1;
    }

    list_t temp_Barrage = world->Barrage;
    while (temp_Barrage != NULL) {
        handle_Main_Barrage_collision(&world->Main_car, &temp_Barrage->val, world, textures, renderer);
        temp_Barrage = temp_Barrage->nxt;
    }

    if (SDL_GetTicks() % 10000 > 9990) {

    }
    if (world->dead == 1 && (time(NULL) - world->time_mort > 5)) {
        world->gameover = 1;
    }
}


int is_game_over(world_t *world) {
    return world->gameover;
}


void tout_deplacer(world_t *world, SDL_Renderer *renderer, resources_t *textures) {
    if (world->Main_car.life > 0) {
        list_t temp_enemy_car = world->Enemy_car;
        list_t temp_barrage = world->Barrage;
        list_t temp_road = world->Road;
        list_t temp_bullet = world->bullet;
        sprite_t temp_main_car = world->Main_car;
        int d = world->Main_car.direction;


        if (d == 0) {
            temp_main_car.position.y -= world->Main_car.speed;
        } else if (d == 1) {
            temp_main_car.position.x += world->Main_car.speed;
        } else if (d == 2) {
            temp_main_car.position.y += world->Main_car.speed;
        } else if (d == 3) {
            temp_main_car.position.x -= world->Main_car.speed;
        }


        switch (d) {
            case 0:
                temp_enemy_car = world->Enemy_car;
                while (temp_enemy_car != NULL) {
                    temp_enemy_car->val.position.y += world->Main_car.speed;
                    if (temp_enemy_car->val.life != 0 && (distance(temp_enemy_car->val, world->Main_car) < 400)) {
                        handle_Main_Enemy_collision(world, &world->Main_car, &temp_enemy_car->val);
                    }
                    temp_enemy_car = temp_enemy_car->nxt;
                }
                temp_barrage = world->Barrage;
                while (temp_barrage != NULL) {
                    temp_barrage->val.position.y += world->Main_car.speed;
                    temp_barrage = temp_barrage->nxt;
                }
                temp_road = world->Road;
                while (temp_road != NULL) {
                    temp_road->val.position.y += world->Main_car.speed;
                    temp_road = temp_road->nxt;
                }
                temp_bullet = world->bullet;
                while (temp_bullet != NULL) {
                    temp_bullet->val.position.y += world->Main_car.speed;
                    temp_bullet = temp_bullet->nxt;
                }
                world->ligne_arivee.position.y += world->Main_car.speed;
                break;
            case 1:
                temp_enemy_car = world->Enemy_car;
                while (temp_enemy_car != NULL) {
                    temp_enemy_car->val.position.x -= world->Main_car.speed;
                    if (temp_enemy_car->val.life != 0 && (distance(temp_enemy_car->val, world->Main_car) < 400)) {
                        handle_Main_Enemy_collision(world, &world->Main_car, &temp_enemy_car->val);
                    }
                    temp_enemy_car = temp_enemy_car->nxt;
                }
                temp_barrage = world->Barrage;
                while (temp_barrage != NULL) {
                    temp_barrage->val.position.x -= world->Main_car.speed;
                    temp_barrage = temp_barrage->nxt;
                }
                temp_road = world->Road;
                while (temp_road != NULL) {
                    temp_road->val.position.x -= world->Main_car.speed;
                    temp_road = temp_road->nxt;
                }
                temp_bullet = world->bullet;
                while (temp_bullet != NULL) {
                    temp_bullet->val.position.x -= world->Main_car.speed;
                    temp_bullet = temp_bullet->nxt;
                }
                break;
            case 2:
                temp_enemy_car = world->Enemy_car;
                while (temp_enemy_car != NULL) {
                    temp_enemy_car->val.position.y -= world->Main_car.speed;
                    if (temp_enemy_car->val.life != 0 && (distance(temp_enemy_car->val, world->Main_car) < 400)) {
                        handle_Main_Enemy_collision(world, &world->Main_car, &temp_enemy_car->val);
                    }
                    temp_enemy_car = temp_enemy_car->nxt;
                }
                temp_barrage = world->Barrage;
                while (temp_barrage != NULL) {
                    temp_barrage->val.position.y -= world->Main_car.speed;
                    temp_barrage = temp_barrage->nxt;
                }
                temp_road = world->Road;
                while (temp_road != NULL) {
                    temp_road->val.position.y -= world->Main_car.speed;
                    temp_road = temp_road->nxt;
                }
                temp_bullet = world->bullet;
                while (temp_bullet != NULL) {
                    temp_bullet->val.position.y -= world->Main_car.speed;
                    temp_bullet = temp_bullet->nxt;
                }
                world->ligne_arivee.position.y -= world->Main_car.speed;

                break;
            case 3:
                temp_enemy_car = world->Enemy_car;
                while (temp_enemy_car != NULL) {
                    temp_enemy_car->val.position.x += world->Main_car.speed;
                    if (temp_enemy_car->val.life != 0 && (distance(temp_enemy_car->val, world->Main_car) < 400)) {
                        handle_Main_Enemy_collision(world, &world->Main_car, &temp_enemy_car->val);
                    }
                    temp_enemy_car = temp_enemy_car->nxt;
                }
                temp_barrage = world->Barrage;
                while (temp_barrage != NULL) {
                    temp_barrage->val.position.x += world->Main_car.speed;
                    temp_barrage = temp_barrage->nxt;
                }
                temp_road = world->Road;
                while (temp_road != NULL) {
                    temp_road->val.position.x += world->Main_car.speed;
                    temp_road = temp_road->nxt;
                }
                temp_bullet = world->bullet;
                while (temp_bullet != NULL) {
                    temp_bullet->val.position.x += world->Main_car.speed;
                    temp_bullet = temp_bullet->nxt;
                }
                break;
        }

    }
}


void move_enemy_car(world_t *world, resources_t *textures, SDL_Renderer *renderer) {
    list_t temp_enemy_car = world->Enemy_car;
    while (temp_enemy_car != NULL) {
        if (temp_enemy_car->val.life != 0 && world->Main_car.life > 0) {
            move_enemy_to_main(temp_enemy_car, world, textures, renderer);
            handle_Main_Enemy_collision(world, &world->Main_car, &temp_enemy_car->val);
        }
        temp_enemy_car = temp_enemy_car->nxt;
    }
}


void move_enemy_to_main(list_t enemy_car, world_t *world, resources_t *textures, SDL_Renderer *renderer) {
    if (enemy_car->val.position.x < world->Main_car.position.x) {
        if (enemy_car->val.position.y < world->Main_car.position.y) {
            if (enemy_car->val.direction != 1) {
                enemy_car->val.direction = 1;
            } else {
                enemy_car->val.position.x += enemy_car->val.speed;
                enemy_car->val.position.y += enemy_car->val.speed;
            }
        } else if (enemy_car->val.position.y > world->Main_car.position.y) {
            if (enemy_car->val.direction != 1) {
                enemy_car->val.direction = 1;
            } else {
                enemy_car->val.position.x += enemy_car->val.speed;
                enemy_car->val.position.y -= enemy_car->val.speed;
            }
        } else if (enemy_car->val.position.y == world->Main_car.position.y) {
            if (enemy_car->val.direction != 1) {
                enemy_car->val.direction = 1;
            } else {
                enemy_car->val.position.x += enemy_car->val.speed;
            }
        }
    } else if (enemy_car->val.position.x > world->Main_car.position.x) {
        if (enemy_car->val.position.y < world->Main_car.position.y) {
            if (enemy_car->val.direction != 3) {
                enemy_car->val.direction = 3;
            } else {
                enemy_car->val.position.x -= enemy_car->val.speed;
                enemy_car->val.position.y += enemy_car->val.speed;
            }
        } else if (enemy_car->val.position.y > world->Main_car.position.y) {
            if (enemy_car->val.direction != 3) {
                enemy_car->val.direction = 3;
            } else {
                enemy_car->val.position.x -= enemy_car->val.speed;
                enemy_car->val.position.y -= enemy_car->val.speed;
            }

        } else if (enemy_car->val.position.y == world->Main_car.position.y) {
            if (enemy_car->val.direction != 3) {
                enemy_car->val.direction = 3;
            } else {
                enemy_car->val.position.x -= enemy_car->val.speed;
            }
        }
    } else if (enemy_car->val.position.x == world->Main_car.position.x) {
        if (enemy_car->val.position.y < world->Main_car.position.y) {
            enemy_car->val.position.y += enemy_car->val.speed;
        } else if (enemy_car->val.position.y > world->Main_car.position.y) {
            enemy_car->val.position.y -= enemy_car->val.speed;
        }
    }
}


void move_sprite_randomly(list_t sprite, resources_t *textures, SDL_Renderer *renderer) {
    int count_max = (rand() % 50) + 50;
    if (sprite->val.count < count_max) {
        switch (sprite->val.direction) {
            case 0:
                sprite->val.position.y -= sprite->val.speed;
                sprite->val.count++;
                break;
            case 1:
                sprite->val.position.x += sprite->val.speed;
                sprite->val.count++;
                break;
            case 2:
                sprite->val.position.y += sprite->val.speed;
                sprite->val.count++;
                break;
            case 3:
                sprite->val.position.x -= sprite->val.speed;
                sprite->val.count++;
                break;

        }
    } else {
        sprite->val.count = 0;
        sprite->val.direction = (rand() % (4));
        switch (sprite->val.direction) {
            case 0:
                sprite->val.position.y -= sprite->val.speed;
                sprite->val.count++;
                break;
            case 1:
                sprite->val.position.x += sprite->val.speed;
                sprite->val.count++;
                break;
            case 2:
                sprite->val.position.y += sprite->val.speed;
                sprite->val.count++;
                break;
            case 3:
                sprite->val.position.x -= sprite->val.speed;
                sprite->val.count++;
                break;

        }
    }
}


void clean_data(world_t *world) {
    for (int i = 0; i < NUMBER_ENEMY_CAR - 1; i++) {
        supprimerElementEnFin(world->Enemy_car);
    }
    for (int i = 0; i < NUMBER_BARRAGE - 1; i++) {
        supprimerElementEnFin(world->Barrage);
    }
    for (int i = 0; i < NUMBER_ROADS - 1; i++) {
        supprimerElementEnFin(world->Road);
    }
}


void move_bullets(world_t *world, resources_t *textures, SDL_Renderer *renderer) {
    list_t temp_bullet = world->bullet;
    while (temp_bullet != NULL) {
        if (distance(temp_bullet->val, world->Main_car) < 3 * SCREEN_HEIGHT) {
            if (temp_bullet->val.direction == 3) {
                temp_bullet->val.position.x -= temp_bullet->val.speed;
                list_t temp_enemy_car = world->Enemy_car;
                while (temp_enemy_car != NULL) {
                    if (temp_enemy_car->val.life != 0) {
                        handle_Bullet_Enemy_collision(world, &temp_bullet->val, &temp_enemy_car->val);
                    }
                    temp_enemy_car = temp_enemy_car->nxt;
                }
            } else if (temp_bullet->val.direction == 1) {
                temp_bullet->val.position.x += temp_bullet->val.speed;
                list_t temp = world->Enemy_car;
                while (temp != NULL) {
                    if (temp->val.life != 0) {
                        handle_Bullet_Enemy_collision(world, &temp_bullet->val, &temp->val);
                    }
                    temp = temp->nxt;
                }
            } else if (temp_bullet->val.direction == 2) {
                temp_bullet->val.position.y += temp_bullet->val.speed;
                list_t temp_enemy_car = world->Enemy_car;
                while (temp_enemy_car != NULL) {
                    if (temp_enemy_car->val.life != 0) {
                        handle_Bullet_Enemy_collision(world, &temp_bullet->val, &temp_enemy_car->val);
                    }
                    temp_enemy_car = temp_enemy_car->nxt;
                }
            } else if (temp_bullet->val.direction == 0) {
                temp_bullet->val.position.y -= temp_bullet->val.speed;
                list_t temp_enemy_car = world->Enemy_car;
                while (temp_enemy_car != NULL) {
                    if (temp_enemy_car->val.life != 0) {
                        handle_Bullet_Enemy_collision(world, &temp_bullet->val, &temp_enemy_car->val);
                    }
                    temp_enemy_car = temp_enemy_car->nxt;
                }
            }
        }

        temp_bullet = temp_bullet->nxt;

    }
}

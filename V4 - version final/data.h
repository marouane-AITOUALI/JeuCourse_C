/**
 * \file data.h
 * \brief Gestion des données du jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 27 decembre  2021
 */

#ifndef V1_DATA_H
#define V1_DATA_H

#include "constants.h"



struct position_s {
    int x;
    int y;
};
typedef struct position_s position_t;

typedef enum {
    Main_car, Enemy_car, Road, Bullet, Car, Barrage, Barre, Menu
} nature_t;

struct sprite_s {
    position_t position;
    int h;
    int w;
    int disappear;
    int direction;
    int dir_texture;
    int count;
    int speed;
    int life;
    nature_t nature;
};
typedef struct sprite_s sprite_t;


typedef struct element element;
struct element {
    sprite_t val;
    struct element *nxt;
};

typedef element *list_t;


struct world_s {
    sprite_t Menu;
    sprite_t new_game_menu;
    sprite_t settings_menu;
    sprite_t exit_menu;
    sprite_t Main_car;
    list_t Barrage;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu  */
    list_t Enemy_car;
    list_t Road;
    list_t bullet;
    int nb_bullets;
    bool stop_menu;
    sprite_t mouse;
    int time_debut_jeu;
    int time_mort;
    int dead;
};
typedef struct world_s world_t;


void init_game(SDL_Window **window, SDL_Renderer **renderer, resources_t *textures, world_t *world);

void init_sprite_ptr(sprite_t *sprite, int x, int y, int w, int h, int v, int life, nature_t nature);

sprite_t init_sprite(sprite_t sprite, int x, int y, int w, int h, int v, int life, nature_t nature);

void init_data(world_t *world);

void update_menu(world_t *world, resources_t *textures, SDL_Renderer *renderer);

void update_data(world_t *world, resources_t *textures, SDL_Renderer *renderer);

int is_game_over(world_t *world);

int sprites_collide(sprite_t *sp1, sprite_t *sp2);

void move_all_except_rick(world_t *world, SDL_Renderer *renderer, resources_t *textures);

void move_enemy_car(world_t *world, resources_t *textures, SDL_Renderer *renderer);

void move_sprite_randomly(list_t enemy_car, resources_t *textures, SDL_Renderer *renderer);

void move_enemy_to_main(list_t enemy_car, world_t *world, resources_t *textures, SDL_Renderer *renderer);

double distance(sprite_t s1, sprite_t s2);

void clean_data(world_t *world);

void move_bullets(world_t *world, resources_t *textures, SDL_Renderer *renderer);

void handle_Bullet_Zombie_collision(world_t *world, sprite_t *sp1, sprite_t *sp2);


#endif //V1_DATA_H

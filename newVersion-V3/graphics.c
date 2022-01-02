/**
 * \file graphics.c
 * \brief Gestion de l'affichage du jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 20  decembre  2021
 */

#include "graphics.h"


void init_textures(SDL_Renderer *renderer, resources_t *textures, world_t *world) {

    textures->font = load_font("font/arial.ttf", 200);

    textures->main_car = charger_image_transparente("IMG/main_car.bmp", renderer);

    textures->enemy_car = charger_image_transparente("IMG/enemy_car.bmp", renderer);

    textures->barrage = charger_image_transparente("IMG/barrage.bmp", renderer);

    textures->road = charger_image_transparente("IMG/road.bmp", renderer);

    textures->bullet = charger_image_transparente("IMG/bullet.bmp", renderer);

    textures->menu = charger_image_transparente("IMG/menu.bmp", renderer);

    textures->new_game_button = charger_image_transparente("IMG/boutton.bmp", renderer);

    textures->settings_button = charger_image_transparente("IMG/boutton.bmp", renderer);

    textures->exit_button = charger_image_transparente("IMG/boutton.bmp", renderer);

}


void refresh_menu(SDL_Renderer *renderer, world_t *world, resources_t *textures) {
    clear_renderer(renderer);
    apply_sprite(renderer, textures->menu, &world->Menu);
    apply_sprite(renderer, textures->new_game_button, &world->new_game_menu);
    apply_sprite(renderer, textures->settings_button, &world->settings_menu);
    apply_sprite(renderer, textures->exit_button, &world->exit_menu);
    apply_text(renderer, (60), 50, 180, 90, "New Game", textures->font,(SDL_Color){243, 89, 0});
    apply_text(renderer, (310), 50, 180, 90, "Settings", textures->font,(SDL_Color){243, 89, 0});
    apply_text(renderer, (560), 50, 180, 90, "Exit", textures->font,(SDL_Color){243, 89, 0});

    apply_text(renderer, (SCREEN_WIDTH-610), 200, 400, 14*4, "Bienvenue", textures->font,(SDL_Color){243, 89, 0});
    apply_text(renderer, (SCREEN_WIDTH-620), 340, 400, 14*4, "Appuyer sur ", textures->font,(SDL_Color){243, 89, 0});
    apply_text(renderer, (SCREEN_WIDTH-620), 410, 400, 14*4, "'NEW GAME'", textures->font,(SDL_Color){240, 248, 255, 0.993});
    apply_text(renderer, (SCREEN_WIDTH-620), 460, 400, 14*4, "pour commencer", textures->font,(SDL_Color){243, 89, 0});
    apply_text(renderer, (SCREEN_WIDTH-800), 600, 200, 14*3, "YATIME MAROUANE", textures->font,(SDL_Color){253, 217, 13});
    apply_text(renderer, (SCREEN_WIDTH-250), 600, 200, 14*3, "AIT OUALI MAROUANE", textures->font,(SDL_Color){253, 217, 13});
    update_screen(renderer);
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *textures) {

    clear_renderer(renderer);

    list_t temp_road = world->Road;
    while (temp_road != NULL) {
        if (distance(temp_road->val, world->Main_car) < 2 * SCREEN_HEIGHT) {
            apply_sprite(renderer, textures->road, &temp_road->val);
        }
        temp_road = temp_road->nxt;
    }

    list_t temp_barrage = world->Barrage;
    while (temp_barrage != NULL) {
        if (temp_barrage->val.disappear == 0) {
            if (distance(temp_barrage->val, world->Main_car) < 2 * SCREEN_HEIGHT) {
                apply_sprite(renderer, textures->barrage, &temp_barrage->val);
            }
        }
        temp_barrage = temp_barrage->nxt;
    }


    list_t temp_enemy = world->Enemy_car;

    while (temp_enemy != NULL) {
        if (distance(temp_enemy->val, world->Main_car) < 2 * SCREEN_HEIGHT) {
            if (temp_enemy->val.life >= 0) {
                apply_sprite(renderer, textures->enemy_car, &temp_enemy->val);
            }
        }

        temp_enemy = temp_enemy->nxt;
    }

    apply_sprite(renderer, textures->main_car, &world->Main_car);


    if (world->nb_bullets != 0) {
        list_t temp_bullet = world->bullet;
        for (int i = 0; i < world->nb_bullets; i++) {
            apply_sprite(renderer, textures->bullet, &temp_bullet->val);
            temp_bullet = temp_bullet->nxt;
        }
    }


    if (world->Main_car.life == 0) {
        SDL_Color color = {255, 50, 50};
        char fin_jeu[20] = "GAME OVER";
        int W = 800;
        int H = 200;
        int X = SCREEN_WIDTH / 2 - W / 2;
        int Y = SCREEN_HEIGHT / 4;
        apply_text(renderer, X, Y, W, H, fin_jeu, textures->font, color);
    }


    update_screen(renderer);
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite) {
    if (texture != NULL) {
        apply_texture(texture, renderer,
                      (sprite->position.x) - ((sprite->w) / 2),
                      (sprite->position.y) - ((sprite->h) / 2)
        );
    }
}


void clean(SDL_Window *window, SDL_Renderer *renderer, resources_t *textures, world_t *world) {
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer, window);
    TTF_Quit();
}

void clean_textures(resources_t *textures) {

    clean_texture(textures->main_car);

    clean_texture(textures->enemy_car);

    clean_texture(textures->barrage);

    clean_texture(textures->road);

    clean_texture(textures->bullet);

    clean_texture(textures->menu);

    clean_texture(textures->new_game_button);

    clean_texture(textures->settings_button);

    clean_texture(textures->exit_button);

    clean_font(textures->font);

}
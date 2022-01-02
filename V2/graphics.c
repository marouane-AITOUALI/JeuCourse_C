/**
 * \file graphics.c
 * \brief Gestion de l'affichage du jeu
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 26 septembre 2021
 */
#include <stdio.h>
#include <stdlib.h>

#include "sdl2.h"
#include "const.h"
#include "graphics.h"
#include "data.h"

/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param screen la surface correspondant à l'écran de jeu
 * \param ressources les ressources du jeu
*/
void init_textures(SDL_Renderer *renderer, ressources_t *ressources)
{
    ressources->background = load_image( "IMG/road.bmp", renderer);
    ressources->spaceship = load_image( "IMG/voiture.bmp", renderer);
    ressources->finish_line = load_image( "IMG/finish_line.bmp", renderer);
    ressources->meteorite = load_image( "IMG/meteorite.bmp", renderer);
    ressources->bullet = load_image( "IMG/bullet.bmp", renderer);
    ressources->font = load_font("IMG/BNKGOTHM.TTF", 15);
}


/**
 * \brief La fonction nettoie les textures
 * \param ressources les ressources du jeu
*/
void clean_textures(ressources_t *ressources)
{
    clean_texture(ressources->background);
    clean_texture(ressources->spaceship);
    clean_texture(ressources->finish_line);
    clean_texture(ressources->meteorite);
    clean_texture(ressources->bullet);
    clean_font(ressources->font);
}


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture liée au fond
*/
void apply_background(SDL_Renderer *renderer, SDL_Texture *texture)
{
    if(texture != NULL)
      apply_texture(texture, renderer, 0, 0);
}


/**
 * \brief La fonction applique un sprite sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture
 * \param sprite la texture liée au sprite
*/
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t* sprite)
{
    if(texture != NULL && sprite->is_visible)
      apply_texture(texture, renderer, sprite->x, sprite->y);
}



/**
 * \brief La fonction applique les meteores sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture
 * \param world les données du monde
*/
void apply_bullets(SDL_Renderer *renderer, SDL_Texture *texture, bullets_t *bullets){
    for(int i = 0; i < bullets->bullet_nb; i++)
        apply_sprite(renderer, texture, &bullets->bullet[i].bullet);
}


/**
 * \brief La fonction applique tout les textes du jeu (au moment voulu) sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture
 * \param world les données du monde
*/
void print_all_text(SDL_Renderer *renderer, ressources_t *ressources, world_t *world)
{
    //Timer
    char timer[20];
    sprintf(timer, "Temps : %.3lf", (double)(SDL_GetTicks() - world->t0)/(double)1000);
    apply_text(renderer, 0, 0, 200, 14*2, timer, ressources->font,(SDL_Color){250, 0, 137});

    //Message de fin
    if(world->gameover == WIN)
        apply_text(renderer, (SCREEN_WIDTH-250)/2, (SCREEN_HEIGHT-14*4)/2, 250, 14*4, "Victoire!", ressources->font,(SDL_Color){250, 0, 137});
    else if(world->gameover == LOOSE)
        apply_text(renderer, (SCREEN_WIDTH-250)/2, (SCREEN_HEIGHT-14*4)/2, 250, 14*4, "Gameover", ressources->font,(SDL_Color){250, 0, 137});
}


/**
 * \brief La fonction qui affiche un menu pour commencer le jeu 
 * \param renderer le renderer
 * \param texture la texture
 * \param world les données du monde
*/
void print_menu_debut(SDL_Renderer *renderer, ressources_t *ressources, world_t *world){
    apply_background(renderer, ressources->background);
    //message de menu
    apply_text(renderer, (SCREEN_WIDTH-610), 20, 400, 14*4, "Bienvenue", ressources->font,(SDL_Color){243, 89, 0});
    apply_text(renderer, (SCREEN_WIDTH-620), 160, 400, 14*4, "Appuyer sur ", ressources->font,(SDL_Color){243, 89, 0});
    apply_text(renderer, (SCREEN_WIDTH-620), 210, 400, 14*4, "'ENTRER'", ressources->font,(SDL_Color){240, 248, 255, 0.993});
    apply_text(renderer, (SCREEN_WIDTH-620), 250, 400, 14*4, "pour commencer", ressources->font,(SDL_Color){243, 89, 0});
    apply_text(renderer, (SCREEN_WIDTH-800), 600, 200, 14*3, "YATIME MAROUANE", ressources->font,(SDL_Color){253, 217, 13});
    apply_text(renderer, (SCREEN_WIDTH-250), 600, 200, 14*3, "AIT OUALI MAROUANE", ressources->font,(SDL_Color){253, 217, 13});
    update_screen(renderer);

}


/**
 * \brief La fonction qui affiche un menu dans la fin du jeu  
 * \param renderer le renderer
 * \param texture la texture
 * \param world les données du monde
*/
void print_menu_fin(SDL_Renderer *renderer, ressources_t *ressources, world_t *world){
    apply_background(renderer, ressources->background);
    //message de menu
    apply_text(renderer, (SCREEN_WIDTH-610), 20, 400, 14*4, "MERCI DE VOTRE PARTICIPATION", ressources->font,(SDL_Color){243, 89, 0});
    apply_text(renderer, (SCREEN_WIDTH-620), 160, 400, 14*4, "Appuyer sur ", ressources->font,(SDL_Color){243, 89, 0});
    apply_text(renderer, (SCREEN_WIDTH-620), 210, 400, 14*4, "'ENTRER'", ressources->font,(SDL_Color){240, 248, 255, 0.993});
    apply_text(renderer, (SCREEN_WIDTH-620), 250, 400, 14*4, "pour rejouer", ressources->font,(SDL_Color){243, 89, 0});
    apply_text(renderer, (SCREEN_WIDTH-800), 600, 200, 14*3, "YATIME MAROUANE", ressources->font,(SDL_Color){253, 217, 13});
    apply_text(renderer, (SCREEN_WIDTH-250), 600, 200, 14*3, "AIT OUALI MAROUANE", ressources->font,(SDL_Color){253, 217, 13});

    update_screen(renderer);

}


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources){

    //application des ressources dans le renderer
    sprite_t tmp = world->background;
    for(int i = 0; i < NB_BACKGROUND; i++){
        apply_sprite(renderer, ressources->background, &tmp); 
        tmp.y += SCREEN_HEIGHT;
    }
    
    apply_sprite(renderer, ressources->spaceship, &world->spaceship.spaceship);
    apply_sprite(renderer, ressources->finish_line, &world->finish_line);
    apply_bullets(renderer, ressources->bullet, &world->spaceship.bullets);
    print_all_text(renderer, ressources, world);
    // on met à jour l'écran
    update_screen(renderer);
}

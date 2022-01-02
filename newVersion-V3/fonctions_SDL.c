/**
 * \file fonctions_SDL.c
 * \brief sur-couche de SDL2 pour simplifier son utilisation pour le projet
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 20  decembre  2021
 */

#include "fonctions_SDL.h"

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Erreur initialisation de la SDL : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer))
    {
        fprintf(stderr, "Erreur lors de la creation de l'image et du renderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

SDL_Texture* charger_image(const char* nomfichier, SDL_Renderer* renderer)
{

	SDL_Surface* surface = SDL_LoadBMP(nomfichier);

	return SDL_CreateTextureFromSurface(renderer, surface);
}

SDL_Texture* charger_image_transparente(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *temp = NULL;
    SDL_Texture *texture = NULL;
    temp = SDL_LoadBMP(path);

    if(NULL == temp)
    {
        fprintf(stderr, "Erreur pendant chargement image BMP: %s", SDL_GetError());
        return NULL;
    }
    SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 255, 0, 255));
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur pendant creation de la texture liee a l'image chargee: %s", SDL_GetError());
        return NULL;
    }
    return texture;
}


void clear_renderer(SDL_Renderer *renderer){
    SDL_RenderClear(renderer);
}

void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y){
    SDL_Rect dst = {0, 0, 0, 0};

    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    dst.x = x; dst.y = y;

    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void update_screen(SDL_Renderer *renderer){
    SDL_RenderPresent(renderer);
}

void clean_texture(SDL_Texture *texture){
    if(NULL != texture){
        SDL_DestroyTexture(texture);
    }
}

void clean_sdl(SDL_Renderer *renderer,SDL_Window *window){
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void init_audio(){
    SDL_Init(SDL_INIT_AUDIO);
}


void init_ttf(){
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
    }
}

TTF_Font * load_font(const char *path, int font_size){
    TTF_Font *font = TTF_OpenFont(path, font_size);
    if(font == NULL){
        fprintf(stderr, "Erreur pendant chargement font: %s\n", SDL_GetError());
    }
    return font;
}

void apply_text(SDL_Renderer *renderer,int x, int y, int w, int h, const char *text, TTF_Font *font, SDL_Color color){

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect2 = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect2);
    SDL_FreeSurface(surface);
    clean_texture(texture);

}

void clean_font(TTF_Font * font){
    TTF_CloseFont(font);
}





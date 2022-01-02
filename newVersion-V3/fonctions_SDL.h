/**
 * \file fonctions_SDL.h
 * \brief en-tête du module correspondant à une sur-couche de SDL2 pour simplifier son utilisation pour le projet
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 20  decembre  2021
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdio.h>

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

SDL_Texture* charger_image(const char* nomfichier, SDL_Renderer* renderer);

SDL_Texture* charger_image_transparente(const char path[], SDL_Renderer *renderer);

void clear_renderer(SDL_Renderer *renderer);

void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y);

void update_screen(SDL_Renderer *renderer);

void clean_texture(SDL_Texture *texture);

void clean_sdl(SDL_Renderer *renderer,SDL_Window *window);

void init_ttf();

TTF_Font * load_font(const char *path, int font_size);

void apply_text(SDL_Renderer *renderer,int x, int y, int w, int h, const char *text, TTF_Font *font, SDL_Color color);

void clean_font(TTF_Font * font);

void init_audio();



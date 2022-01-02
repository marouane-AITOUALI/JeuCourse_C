#include <stdio.h>
#include <stdlib.h>

#include "sdl2.h"
#include "const.h"

#include "data.h"

/**
 * \brief tester les fonctions
 */

void print_sprite(sprite_t *sprite){
    printf("sprite->x : %d\n", sprite->x);
    printf("sprite->y : %d\n", sprite->y);
    printf("sprite->w : %d\n", sprite->w);
    printf("sprite->h : %d\n", sprite->h);
}

void test_init_sprite_param(int x, int y, int w, int h){
    sprite_t sprite;
    init_sprite(&sprite, x, y, w, h);
    print_sprite(&sprite);
}

void test_init_sprite(){
     test_init_sprite_param(10, 20, 30, 40);
     test_init_sprite_param(15, 25, 35, 45);
     test_init_sprite_param(50, 60, 70, 80);
     test_init_sprite_param(55, 65, 75, 85);
}


 int main(){
     test_init_sprite();
     return 0;
 }
 

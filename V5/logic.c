/**
 * \file logic.c
 * \brief Gestion de la logique du jeu (physique)
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 3  janvier  2022 */

#include "logic.h"


double distance(sprite_t s1, sprite_t s2) {
    double s1x = s1.position.x;
    double s1y = s1.position.y;
    double s2x = s2.position.x;
    double s2y = s2.position.y;
    return (sqrt(pow(s1x - s2x, 2) + pow(s1y - s2y, 2)));
}

int sprites_collide(sprite_t *sp1, sprite_t *sp2) {

    int gauche1, gauche2, droite1, droite2, haut1, haut2, bas1, bas2;


    haut1 = sp1->position.y - (sp1->h) / 2;
    bas1 = sp1->position.y + (sp1->h) / 2;
    haut2 = sp2->position.y - (sp2->h) / 2;
    bas2 = sp2->position.y + (sp2->h) / 2;
    gauche1 = sp1->position.x - (sp1->w) / 2;
    droite1 = sp1->position.x + (sp1->w) / 2;
    gauche2 = sp2->position.x - (sp2->w) / 2;
    droite2 = sp2->position.x + (sp2->w) / 2;


    if (bas1 <= haut2 || haut1 >= bas2 || droite1 <= gauche2 || gauche1 >= droite2) {
        return false;
    } else {
        return true;
    }
}


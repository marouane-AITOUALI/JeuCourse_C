/**
 * \file liste.h
 * \brief Gestion des listes
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 3  janvier  2022 */

#ifndef V1_LISTE_H
#define V1_LISTE_H


#include "constants.h"
#include "data.h"

list_t ajouter(list_t liste, sprite_t valeur);

bool estVide(list_t liste);

list_t supprimerElementEnTete(list_t liste);

list_t supprimerElementEnFin(list_t liste);

list_t l_vide();

int tailleListe(list_t liste);

#endif //V1_LISTE_H

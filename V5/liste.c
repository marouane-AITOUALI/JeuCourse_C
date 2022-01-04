/**
 * \file liste.c
 * \brief Gestion des listes
 * \author YATIME Marouane - AIT OUALI Marouane
 * \date 3  janvier  2022 */

#include "liste.h"



list_t ajouter(list_t liste, sprite_t valeur) {
    element *nouvelElement = malloc(sizeof(element));
    nouvelElement->val = valeur;
    nouvelElement->nxt = NULL;
    if (liste == NULL) {
        return nouvelElement;
    } else {
        element *temp = liste;
        while (temp->nxt != NULL) {
            temp = temp->nxt;
        }
        temp->nxt = nouvelElement;
        return liste;
    }
}

bool estVide(list_t liste) {
    return (liste == NULL) ? 1 : 0;
}

list_t supprimerElementEnTete(list_t liste) {
    if (liste != NULL) {
        element *aRenvoyer = liste->nxt;
        free(liste);
        return aRenvoyer;
    } else {
        return NULL;
    }
}

list_t supprimerElementEnFin(list_t liste) {
    if (liste == NULL)
        return NULL;

    if (liste->nxt == NULL) {
        free(liste);
        return NULL;
    }

    element *tmp = liste;
    element *ptmp = liste;
    while (tmp->nxt != NULL) {
        ptmp = tmp;
        tmp = tmp->nxt;
    }

    ptmp->nxt = NULL;
    free(tmp);
    return liste;
}


list_t l_vide() {
    return NULL;
}

int tailleListe(list_t liste) {
    list_t liste_temp = liste;
    int i = 0;
    while (liste_temp != NULL) {
        i++;
        liste_temp = liste_temp->nxt;
    }
    return i;
}
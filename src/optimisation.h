/**
 * \file optimisation.h
 * \brief En-tête d'optimisation
 * \author david
 * \date 28 avr. 2012
 */

#ifndef __OPTIMISATION_H__
#define __OPTIMISATION_H__

#include "dijkstra.h"
#include "chaine.h"
#include "erreur.h"
#include "fichier.h"
#include "heap.h"
#include "reseau.h"
#include "stringTools.h"

/**
 * @brief Fonction de récréation de la ListeChaine à partir du réseau en utilisant Dijkstra sans contraintes
 * @param L Pointeur vers la ListeChaine
 * @param R Pointeur vers le réseau
 */
void recree_liste_chaine(ListeChaine *L, Reseau *R);

/**
 * @brief Fonction de récréation de la ListeChaine à partir du réseau en utilisant Dijkstra avec contraintes
 * @param L Pointeur vers la ListeChaine
 * @param R Pointeur vers le réseau
 */
void recree_liste_chaine_csp(ListeChaine *L, Reseau *R);


#endif

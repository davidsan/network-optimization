/**
 * \file timer.h
 * \brief En-tête des timers
 * \author David San
 */
#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abr.h"
#include "build.h"
#include "chaine.h"
#include "hachage.h"
#include "reseau.h"

/**
 * @brief Fonction qui affiche le temps de chaque conversion de ListeChaine vers Reseau par les trois structures de données
 * @param filename Chaîne de caractères représentant le nom du fichier à lire
 */
void timeAll(char *filename);
/**
 * @brief Fonction qui affiche le temps de chaque conversion de ListeChaine vers Reseau par l'utilisation d'une liste chaînée triée
 * @param filename
 */
void timeLC(char *filename);
/**
 * @brief Fonction qui affiche le temps de chaque conversion de ListeChaine vers Reseau par l'utilisation d'une table de hachage
 * @param filename
 */
void timeHash(char *filename);
/**
 * @brief Fonction qui affiche le temps de chaque conversion de ListeChaine vers Reseau par l'utilisation d'un arbre binaire de recherche équilibré
 * @param filename
 */
void timeAVL(char *filename);


#endif

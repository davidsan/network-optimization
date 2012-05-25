/**
 * \file menu.h
 * \brief En-tête de menu
 * \author David San
 */
#ifndef MENU_H
#define MENU_H
#include <ctype.h>
#include "abr.h"
#include "build.h"
#include "chaine.h"
#include "erreur.h"
#include "fichier.h"
#include "hachage.h"
#include "reseau.h"
#include "xfigTools.h"

/**
 * @brief Fonction d'affichage du menu
 */
void showMenu();

/**
 * @brief Fonction de lecture d'un nombre
 * @return Le nombre lu
 */
int readNombre();
/**
 * @brief Fonction de lecture d'une chaîne de caractères
 * @param s Pointeur vers la chaîne de caractères de stockage
 */
void readString(char **s);
/**
 * @brief Fonction d'appel du choix de l'utilisation
 * @param f Flux vers le fichier ouvert
 * @param choix Entier représentant le choix dans le menu
 * @param R Pointeur vers l'adresse du réseau
 * @param L Pointeur vers l'adresse de la structure ListeChaine
 */
void callChoix(FILE ** f, int choix, Reseau ** R, ListeChaine ** L);

#endif

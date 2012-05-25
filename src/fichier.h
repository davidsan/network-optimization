/**
 * \file fichier.h
 * \brief En-tête de fichier
 * \author David San
 */
#ifndef __FICHIER_H__
#define __FICHIER_H__

#include <stdio.h>
#include "erreur.h"

#define BUFFER_SIZE 8192
/**
 * @brief Fonction d'ouverture de fichier en lecture seule
 * @param filename Chaîne de caractères représentant le nom du fichier à ouvrir
 * @return Flux vers le fichier ouvert
 */
FILE *ouvrirFichier(char *filename);
/**
 * @brief Fonction de fermeture d'un fichier
 * @param f Flux à fermer
 */
void fermerFichier(FILE * f);
/**
 * @brief Fonction de lecture d'une ligne d'un flux
 * @param f Flux à lire
 * @param buffer Pointeur vers une chaîne de caractères où sera stocké la ligne lue
 * @return 1 si la lecture a réussi, 0 sinon.
 */
int readLine(FILE * f, char *buffer);

#endif

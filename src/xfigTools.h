/**
 * \file xfigTools.h
 * \brief En-tête des outils xfig
 * \author David San
 */
#ifndef __XFIGTOOLS_H__
#define __XFIGTOOLS_H__

#include <stdio.h>
#include "chaine.h"
#include "erreur.h"
#include "reseau.h"

/**
 * @brief Fonction d'écriture de l'en-tête d'un fichier xfig
 * @param f Pointeur vers le flux d'écriture
 */
void ecrit_entete_xfig(FILE * f);
/**
 * @brief Fonction d'écriture d'une structure de type ListeChaine dans un fichier xfig
 * @param L Pointeur vers la structure de type ListeChaine
 * @param f Pointeur vers le flux d'écriture
 * @param zoom Entier représentant le zoom de la représentation
 * @param epaisseur Entier représentant l'épaisseur des tracés xfig
 */
void ecrit_chaine_xfig(ListeChaine * L, FILE * f, int zoom, int epaisseur);
/**
 * @brief Fonction d'écriture d'un réseau dans un fichier xfig
 * @param R Pointeur vers le réseau
 * @param f Pointeur vers le flux d'écriture
 * @param zoom Entier représentant le zoom de la représentation
 * @param epaisseur Entier représentant l'épaisseur des tracés xfig
 */
void ecrit_reseau_xfig(Reseau * R, FILE * f, int zoom, int epaisseur);

#endif

/**
 * \file stringTools.h
 * \brief En-tête des outils de manipulation des chaînes de caractères
 * \author David San
 */
#ifndef __STRINGTOOLS_H__
#define __STRINGTOOLS_H__
#include "erreur.h"

/**
 * @brief Fonction qui extrait le nombre de chaînes
 * @param string Chaîne de caractères à traiter
 * @return Le nomnbre de chaînes.
 */
int scanNbChain(char *string);
/**
 * @brief Fonction qui extrait gamma
 * @param string Chaîne de caractères à traiter
 * @return Gamma.
 */
int scanGamma(char *string);
/**
 * @brief Fonction qui extrait le numéro
 * @param string Chaîne de caractères à traiter
 * @return Le numéro.
 */
int scanNumero(char *string);
/**
 * @brief Fonction qui extrait le nombre de noeuds
 * @param string Chaîne de caractères à traiter
 * @return Le nombre de noeuds.
 */
int scanNbNodes(char *string);
/**
 * @brief Fonction qui extrait le nombre de câbles
 * @param string Chaîne de caractères à traiter
 * @return Le nombre de câbles.
 */
int scanNbCables(char *string);
/**
 * @brief Fonction qui teste si la chaîne de caractères est un commentaire
 * @param string
 * @return 1 si la chaîne de caractères est un commentaire, 0 sinon.
 */
int isComment(char *string);


#endif

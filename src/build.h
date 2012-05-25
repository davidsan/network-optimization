/**
 * \file build.h
 * \brief En-tête de build
 * \author David San
 */
#ifndef __BUILD_H__
#define __BUILD_H__

#include "chaine.h"
#include "reseau.h"

#define EPS 0.0001
/**
 * @brief Fonction de recherche d'un noeud dans un réseau
 * @param R Pointeur vers le réseau
 * @param x Ordonnée du noeud à chercher
 * @param y Abscisse du noeud à chercher
 * @return Pointeur vers le noeud correspondant ou NULL.
 */
Noeud *recherche_noeud(Reseau * R, double x, double y);
/**
 * @brief Fonction d'ajout d'un noeud dans un réseau s'il n'est pas déjà présent
 * @param R Pointeur vers le réseau
 * @param x Ordonnée du noeud à ajouter
 * @param y Abscisse du noeud à ajouter
 * @return Pointeur vers le noeud présent s'il existe, ou NULL.
 */
Noeud *recherche_cree_noeud(Reseau * R, double x, double y);

/**
 * @brief Fonction de comparaison entre deux noeuds
 * @param x1 Ordonnée du premier noeud
 * @param y1 Abscisse du premier noeud
 * @param x2 Ordonnée du deuxième noeud
 * @param y2 Abscisse du deuxième noeud
 * @return 1 si le premier noeud est inférieur au deuxième noeud, 0 sinon
 */
int compare(double x1, double y1, double x2, double y2);
/**
 * @brief Fonction de recherche d'une cellule de noeud dans un réseau
 * @param R Pointeur vers le réseau
 * @param node Pointeur vers le noeud à chercher
 * @return Pointeur vers la cellule de noeud correspondante ou NULL.
 */
CelluleLNoeud *rechercheCelluleLNoeud(Reseau * R, Noeud * node);
/**
 * @deprecated Fonction non utilisée
 * @brief Fonction de purge sur les doublons
 * @param L Pointeur vers la liste chaînée de noeuds à purger
 * @return Pointeur vers la nouvelle liste chaînée de noeuds
 */
CelluleLNoeud *purgeDuplicate(CelluleLNoeud * L);

/**
 * @brief Fonction qui recrée le réseau à partir d'une structure de type ListeChaine en utilisant une liste chaînée
 * @param L Pointeur vers la structure de type ListeChaine
 * @param R Pointeur vers le réseau
 */
void recree_reseau(ListeChaine * L, Reseau * R);

/**
 * @brief Fonction d'insertion d'une cellule de noeud dans une liste chaînée triée de noeuds
 * @param debutListeNoeuds Pointeur vers le début de la liste de noeuds
 * @param node Pointeur vers la cellule de noeud à insérer
 * @return Pointeur vers la liste chaînée triée de noeuds mise à jour.
 */
CelluleLNoeud *insererCelluleLNoeudTrie(CelluleLNoeud * debutListeNoeuds,
		CelluleLNoeud * node);

#endif

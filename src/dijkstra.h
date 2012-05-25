/**
 * \file dijkstra.h
 * \brief En-tête Dijkstra
 * \author david
 * \date 28 avr. 2012
 */

#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include "chaine.h"
#include "float.h"
#include "heap.h"
#include "reseau.h"
/**
 * @brief Fonction Dijkstra qui renvoie un vecteur de successeurs
 * @param R Pointeur vers le réseau
 * @param src Entier du numéro du noeud de départ
 * @param target Entier du numéro du noeud d'arrivée
 * @return Vecteur de successeurs (plus court chemin entre le noeud de départ et le noeud d'arrivée)
 */
Noeud ** dijkstra(Reseau *R, int src, int target);

/**
 * @brief Fonction qui renvoie la liste chaînée de Chaine à partir du vecteur de successeurs
 * @param R Pointeur vers le réseau
 * @param previous Vecteur de successeurs
 * @param target Entier du numéro du noeud d'arrivée
 * @return Liste chaînée de Chaine obtenue à partir du vecteur de successeurs
 */
Chaine * convertPrevious(Reseau *R, Noeud ** previous, int target);

/**
 * @brief Fonction Dijkstra qui renvoie un vecteur de successeurs (csp)
 * @param R Pointeur vers le réseau
 * @param src Entier du numéro du noeud de départ
 * @param target Entier du numéro du noeud d'arrivée
 * @return Vecteur de successeurs (plus court chemin entre le noeud de départ et le noeud d'arrivée)
 */
Noeud ** dijkstra_csp(Reseau *R, int src, int target);

/**
 * @brief Fonction qui renvoie la liste chaînée de Chaine à partir du vecteur de successeurs (csp)
 * @param R Pointeur vers le réseau
 * @param previous Vecteur de successeurs
 * @param target Entier du numéro du noeud d'arrivée
 * @return Liste chaînée de Chaine obtenue à partir du vecteur de successeurs
 */
Chaine * convertPrevious_csp(Reseau *R, Noeud ** previous, int target);


/**
 * @brief Fonction qui mets à jour le gamma de deux noeuds
 * @param u Pointeur vers le premier noeud
 * @param v Pointeur vers le second noeud
 */
void updateGamma(Noeud *u, Noeud *v);

/**
 * @brief Fonction qui cherche un voisin parmi les voisins d'un noeud
 * @param node Pointeur vers le noeud
 * @param int Numéro du voisin à chercher
 * @return Pointeur vers le voisin cherché
 */
Voisin *chercheVoisin(Noeud *node, int vs);

/**
 * @brief Fonction qui renvoie le plus grand gamma contenu dans le réseau
 * @param R Pointeur vers le réseau
 * @return Entier du plus grand gamma
 */
int getMaxGamma(Reseau *R);

#endif

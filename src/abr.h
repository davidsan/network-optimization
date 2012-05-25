/**
 * \file abr.h
 * \brief En-tête de abr
 * \author David San
 */
#ifndef __ABR_H__
#define __ABR_H__

#include "build.h"
#include "reseau.h"

/**
 * @struct avl
 * Arbre binaire de recherche équilibrée (AVL)
 */
typedef struct avl {
    Noeud *content; /*!< Pointeur vers le contenu du noeud */
    int height; /*!< Hauteur du noeud */
    struct avl *right; /*!< Pointeur vers le fils gauche */
    struct avl *left; /*!< Pointeur vers le fils droit */
} AVL;

/**
 * @brief Fonction de création d'un arbre binaire de recherche équilibré
 * @param content Pointeur vers le contenu du noeud
 * @param left Pointeur vers le fils gauche
 * @param right Pointeur vers le fils droit
 * @return Pointeur vers la nouvelle instance allouée de type AVL
 */
AVL *creerAVL(Noeud * content, AVL * left, AVL * right);
/**
 * @brief Fonction de destruction d'un arbre binaire de recherche équilibré
 * @param root Pointeur vers la racine de l'arbre binaire de recherche équilibré à détruire
 */
void freeAVL(AVL * root);

/**
 * @brief Fonction qui calcule la hauteur du noeud
 * @param node Pointeur vers le noeud
 * @return Hauteur du noeud
 */
int getHeight(AVL * node);

/**
 * @brief Fonction qui teste si le noeud est équilibré
 * @param node Pointeur vers le noeud à tester
 * @return 1 si le noeud est équilibré, 0 sinon.
 */
int isBalanced(AVL * node);
/**
 * @brief Fonction qui teste si l'arbre binaire de recherche est équilibré
 * @param root Pointeur vers la racine de l'arbre binaire de recherche
 * @return 1 si l'arbre binaire de recherche est équilibré.
 */
int checkBalance(AVL * root);
/**
 * @brief Fonction qui calcule la hauteur de l'arbre en parcourant l'arbre
 * @param root Racine de l'arbre
 * @return Hauteur de l'arbre
 */
int height(AVL * root);

/**
 * @brief Fonction qui renvoie le plus grand entier de deux entiers
 * @param a Premier entier
 * @param b Deuxième entier
 * @return Le plus grand entier de deux entiers
 */
int max(int a, int b);
/**
 * @brief Fonction qui compare deux noeuds
 * @param a Premier noeud
 * @param b Deuxième noeud
 * @return 1 si le noeud a est inférieur au noeud b, 0 sinon
 */
int compareNode(Noeud * a, Noeud * b);

/**
 * @brief Fonction qui effectue une rotation gauche simple sur l'arbre binaire de recherche
 * @param root Pointeur vers la racine de l'arbre binaire de recherche
 * @return Pointeur vers la racine de l'arbre binaire de recherche résultant de la rotation.
 */
AVL *rotateLeft(AVL * root);
/**
 * @brief Fonction qui effectue une rotation droite simple sur l'arbre binaire de recherche
 * @param root Pointeur vers la racine de l'arbre binaire de recherche
 * @return Pointeur vers la racine de l'arbre binaire de recherche résultant de la rotation.
 */
AVL *rotateRight(AVL * root);

/**
 * @brief Fonction qui effectue une rotation gauche double sur l'arbre binaire de recherche
 * @param root Pointeur vers la racine de l'arbre binaire de recherche
 * @return Pointeur vers la racine de l'arbre binaire de recherche résultant de la rotation.
 */
AVL *doubleRotateLeft(AVL * root);
/**
 * @brief Fonction qui effectue une rotation droite double sur l'arbre binaire de recherche
 * @param root Pointeur vers la racine de l'arbre binaire de recherche
 * @return Pointeur vers la racine de l'arbre binaire de recherche résultant de la rotation.
 */
AVL *doubleRotateRight(AVL * root);

/**
 * @brief Fonction qui recherche si un noeud est présent dans l'arbre binaire de recherche
 * @param root Pointeur vers la racine de l'arbre binaire de recherche
 * @param x Ordonnée du noeud
 * @param y Abscisse du noeud
 * @return Pointeur vers le noeud trouvé, ou NULL.
 */
Noeud *rechercheNoeudAVL(AVL * root, double x, double y);

/**
 * @brief Fonction d'insertion d'un noeud dans l'arbre binaire de recherche équilibré
 * @param root Pointeur vers la racine de l'arbre binaire de recherche
 * @param node Pointeur vers le noeud à insérer
 * @return Pointeur vers la racine de l'arbre binaire de recherche résultant de l'insertion
 */
AVL *insererAVL(AVL * root, Noeud * node);

/**
 * @brief Fonction qui affiche le noeud d'un arbre binaire de recherche équilibré
 * @param node Pointeur vers le noeud à afficher
 */
void displayNodeAVL(AVL * node);
/**
 * @brief Fonction qui affiche un arbre binaire de recherche équilibré
 * @param root Pointeur vers la racine de l'arbre binaire de recherche à afficher
 */
void displayAVL(AVL * root);

/**
 * @brief Fonction d'insertion d'un noeud dans l'arbre binaire de recherche équilibré
 * @deprecated N'apporte pas de réel avantage (performances équivalentes) par rapport à insererAVL, moins lisible.
 * @param root Pointeur vers la racine de l'arbre binaire de recherche
 * @param x Ordonnée du point à insérer
 * @param y Abscisse du point à insérer
 * @param insertion Boolean indiquant si une insertion a eu lieu
 * @param compteur Compteur du point
 * @param node Pointeur vers l'adresse du noeud à créer s'il n'est pas déjà présent ou à modifier s'il est présent
 * @return Pointeur vers la racine de l'arbre binaire de recherche résultant de l'insertion
 */
AVL *insererAVL_NoCheck(AVL * root, double x, double y, int * insertion, int * compteur, Noeud **node);

/**
 * @brief Fonction qui recrée un réseau à partir d'une structure de type ListeChaine en utilisant un arbre binaire de recherche équilibré
 * @deprecated N'apporte pas de réel avantage (performances équivalentes) par rapport à recree_reseau_AVL, moins lisible.
 * @param L Pointeur vers la structure de type ListeChaine
 * @param R Pointeur vers le réseau
 */
void recree_reseau_AVL_NoCheck(ListeChaine * L, Reseau * R);

/**
 * @brief Fonction qui recrée un réseau à partir d'une structure de type ListeChaine en utilisant un arbre binaire de recherche équilibré
 * @param L Pointeur vers la structure de type ListeChaine
 * @param R Pointeur vers le réseau
 */
void recree_reseau_AVL(ListeChaine * L, Reseau * R);




#endif

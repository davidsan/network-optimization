/**
 * \file hachage.h
 * \brief En-tête d'hachage
 * \author David San
 */
#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "build.h"
#include "chaine.h"
#include "reseau.h"

/**
 * @struct hachage
 * Structure représentant une table de hachâge
 */
typedef struct hachage {
    int m; /*!< Taille de la table de hachage */
    int nbElement; /*!< Nombre d'éléments dans la table de hachage */
    CelluleLNoeud **tab; /*!< Pointeur vers la table de hachage */
} Hachage;

/**
 * @brief Fonction de création d'une table de hachage
 * @param m Taille de la table de hachage
 * @return Pointeur vers la nouvelle instance allouée de type Hachage
 */
Hachage *creerHachage(int m);
/**
 * @brief Fonction d'inserertion d'une cellule de noeud dans une table de hachage
 * @param h Pointeur vers la table de hachage
 * @param node Pointeur vers la cellule de noeud à insérer
 */
void insererHachage(Hachage * h, CelluleLNoeud * node);
/**
 * @brief Fonction de destruction du tableau de la table de hachage
 * @param h Pointeur vers la table de hachage
 */
void freeHachageTable(Hachage * h);
/**
 * @brief Fonction de destruction de lable de hachage (structure Hachage)
 * @param h Pointeur vers la table de hachage
 */
void freeHachage(Hachage * h);

/**
 * @brief Fonction de génération de clé à partir d'ordonnée et d'abscisse
 * @param x Ordonnée
 * @param y Abscisse
 * @return Clé généré
 */
double generateKey(double x, double y);
/**
 * @brief Fonction de hachage
 * @param k Clé
 * @param h Pointeur vers la table de hachage
 * @return Empreinte résultant du hachage
 */
int hash(double k, Hachage * h);
/**
 * @brief Fonction d'affichage de la table de hachage
 * @param h Pointeur vers la table de hachage
 */
void displayHachage(Hachage * h);
/**
 * @brief Fonction de recherche d'un noeud de coordonnées (x, y) dans la table de hachage
 * @param h Pointeur vers la table de hachage
 * @param x Ordonnée du noeud à chercher
 * @param y Abscisse du noeud à chercher
 * @return Pointeur vers le noeud trouvé ou NULL.
 */
Noeud *rechercheNoeudHachage(Hachage * h, double x, double y);
/**
 * @brief Fonction d'insertion d'un noeud dans la table de hachage et dans le réseau
 * @param R Pointeur vers le réseau
 * @param H Pointeur vers la table de hachage
 * @param x Ordonnée du noeud à insérer
 * @param y Abscisse du noeud à insérer
 * @return Pointeur vers le noeud s'il est déjà présent, ou NULL.
 */
Noeud *recherche_cree_noeud_hachage(Reseau * R, Hachage * H, double x,
				    double y);
/**
 * @brief Fonction qui recrée le réseau à partir de la structure de type ListeChaine en utilisant une table de hachage
 * @param L Pointeur vers la structure de type ListeChaine
 * @param R Pointeur vers le réseau
 * @param H Pointeur vers la table de hachage
 */
void recree_reseau_hachage(ListeChaine * L, Reseau * R, Hachage * H);

#endif

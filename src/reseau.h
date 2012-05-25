/**
 * \file reseau.h
 * \brief En-tête de réseau
 * \author David San
 */
#ifndef __RESEAU_H__
#define __RESEAU_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "erreur.h"
#include "fichier.h"
#include "stringTools.h"

/**
 * \struct voisin
 * Elément de la liste des noeuds voisins d’un noeud du réseau
 */
typedef struct voisin {
	int v; /*!< Numero du voisin dans le Reseau */
	int gamma; /*!< Nombre de cables entre le noeud et le voisin */
	struct voisin *voisSuiv; /*!< Pointeur sur le voisin suivant */
} Voisin;

/**
 * \struct noeud
 * Noeud du réseau
 */
typedef struct noeud {
	int u; /*!< Numéro du noeud dans le réseau */
	double x; /*!< Abscisse du noeud */
	double y; /*!< Ordonnée du noeud */
	Voisin *LVoisins; /*!< Liste des noeuds voisins de u */
} Noeud;

/**
 * \struct celluleLNoeud
 * Element de la liste chainee des noeuds du reseau
 */
typedef struct celluleLNoeud {
	Noeud *ptrnoeud; /*!< Pointeur sur un noeud du réseau */
	struct celluleLNoeud *noeudSuiv; /*!< Noeud suivant dans la liste des noeuds */
} CelluleLNoeud;

/**
 * \struct celluleLCommodite
 * Element de la liste chainee des commodites du reseau
 */
typedef struct celluleLCommodite {
	int extr1; /*!< Première extrémité */
	int extr2; /*!< Deuxième extrémité */
	struct celluleLCommodite *commSuiv; /*!< Commodité suivante dans la liste des commodités */
} CelluleLCommodite;

/**
 * \struct reseau
 * Un réseau
 */
typedef struct reseau {
	int nbNoeuds; /*!< Nombre total de noeuds dans le réseau */
	int gamma; /*!< Nombre maximal de fibres dans un câble */
	CelluleLCommodite *LCommodites; /*!< Liste des commodités à relier */
	CelluleLNoeud *LNoeuds; /*!< Liste des noeuds du réseau */
} Reseau;


/**
 * @brief Fonction de création d'une nouvelle instance d'un objet Voisin
 *
 * @param v Numéro d'identification du voisin
 * @return Pointeur vers la nouvelle instance allouée d'un objet de type Voisin ou NULL.
 */
Voisin *creerVoisin(int v);
/**
 * @brief Fonction d'insertion d'un voisin à la fin d'une liste chaînée de voisin
 *
 * @param debutListeVoisin Début de la liste chaînée des voisins
 * @param vois Voisin à insérer dans la liste
 * @return Pointeur vers le premier élément de la liste chaînée mise à jour.
 */
Voisin *insererVoisin(Voisin * debutListeVoisin, Voisin * vois);
/**
 * @brief Fonction d'insertion d'un voisin au début d'une liste chaînée de voisin
 *
 * @param debutListeVoisin Pointeur vers le début de la liste chaînée des voisins
 * @param vois Voisin à insérer dans la liste
 * @return Pointeur vers le premier élément de la liste chaînée mise à jour.
 */
Voisin *insererVoisinDebut(Voisin * debutListeVoisin, Voisin * vois);

/**
 * @brief Fonction de création d'une nouvelle instance d'un objet Noeud
 *
 * @param u Numéro du noeud à créer
 * @param x Abscisse du noeud à créer
 * @param y Ordonnée du noeud à créer
 * @return Pointeur vers la nouvelle instance allouée d'un objet de type Noeud ou NULL.
 */
Noeud *creerNoeud(int u, double x, double y);

/**
 * @brief Fonction de création d'une nouvelle instance d'un objet CelluleLNoeud
 * @param ptrnoeud Pointeur vers le noeud contenu dans la cellule
 * @return Pointeur vers la nouvelle instance allouée d'un objet de type CelluleLNoeud ou NULL.
 */
CelluleLNoeud *creerCelluleLNoeud(Noeud * ptrnoeud);
/**
 * @brief Fonction d'insertion d'une cellule de noeud à la fin d'une liste chaînée de Noeud
 * @param debutListeNoeuds Pointeur vers le début de la liste chaînée des Noeuds
 * @param node Pointeur vers la cellule de Noeud à insérer dans la liste
 * @return Pointeur vers le premier élément de la liste chaînée mise à jour.
 */
CelluleLNoeud *insererCelluleLNoeud(CelluleLNoeud * debutListeNoeuds,
		CelluleLNoeud * node);
/**
 * @brief Fonction d'insertion d'une cellule de noeud au début d'une liste chaînée de Noeud
 * @param debutListeNoeuds Pointeur vers le début de la liste chaînée des Noeuds
 * @param node Pointeur vers la cellule de Noeud à insérer dans la liste
 * @return Pointeur vers le premier élément de la liste chaînée mise à jour.
 */
CelluleLNoeud *insererCelluleLNoeudDebut(CelluleLNoeud * debutListeNoeuds,
		CelluleLNoeud * node);

/**
 * @brief Fonction d'insertion d'une cellule de noeud à la fin d'une liste chaînée de Noeud si et seulement si le noeud n'est pas présent dans la liste
 * @param debutListeNoeuds Pointeur vers le début de la liste chaînée des Noeuds
 * @param node Pointeur vers le noeud à insérer dans la liste
 * @return Pointeur vers le premier élément de la liste chaînée mise à jour.
 */
CelluleLNoeud *insererCelluleLNoeudUnique(CelluleLNoeud * debutListeNoeuds,
		Noeud * node);

/**
 * @brief Fonction de création d'une cellule de commodité
 * @param extr1 Première extrémité
 * @param extr2 Deuxième extrémité
 * @return Pointeur vers la nouvelle instance allouée d'un objet de type CelluleLCommodite ou NULL.
 */
CelluleLCommodite *creerCelluleLCommodite(int extr1, int extr2);

/**
 * @brief Fonction d'insertion d'une cellule de commodité à la fin d'une liste chaînée de commodités
 * @param debutListeCommodite Pointeur vers le début de la liste chaînée des commodités
 * @param commodite Pointeur vers la commodité à insérer dans la liste
 * @return Pointeur vers le premier élément de la liste chaînée mise à jour.
 */
CelluleLCommodite *insererCelluleLCommidite(
		CelluleLCommodite * debutListeCommodite, CelluleLCommodite * commodite);

/**
 * @brief Fonction d'insertion d'une cellule de commodité au début d'une liste chaînée de commodités
 * @param debutListeCommodite Pointeur vers le début de la liste chaînée des commodités
 * @param commodite Commodité à insérer dans la liste
 * @return Pointeur vers le premier élément de la liste chaînée mise à jour.
 */
CelluleLCommodite *insererCelluleLCommiditeDebut(
		CelluleLCommodite * debutListeCommodite, CelluleLCommodite * commodite);


/**
 * @brief Fonction de création d'un réseau
 * @return Pointeur vers la nouvelle instance allouée d'un objet de type Reseau ou NULL.
 */
Reseau *creerReseau();

/**
 * @brief Fonction de destruction d'un voisin
 * @param vois Pointeur vers le voisin à détruire
 */
void freeOneVoisin(Voisin * vois);
/**
 * @brief Fonction de destruction d'une liste chaînée de voisin
 * @param debutListeVoisin Pointeur vers le début de la liste chaînée de voisin à détruire
 */
void freeAllVoisin(Voisin * debutListeVoisin);
/**
 * @brief Fonction de destruction d'un noeud
 * @param node Pointeur vers le noeud à détruire
 */
void freeNoeud(Noeud * node);
/**
 * @brief Fonction de destruction d'une cellule de noeud
 * @param CLNode Pointeur vers la cellule de noeud à détruire
 */
void freeOneCelluleLNoeud(CelluleLNoeud * CLNode);
/**
 * @brief Fonction de destruction d'une liste chaînée de noeud
 * @param debutListeCLNode Pointeur vers le début de la liste chaînée de noeud à détruire
 */
void freeAllCelluleLNoeud(CelluleLNoeud * debutListeCLNode);
/**
 * @brief Fonction de destruction d'une liste chaînée de noeud sans détruire les noeuds
 * @param debutListeCLNode Pointeur vers le début de la liste chaînée de noeud à détruire
 */
void freeAllCelluleLNoeudWithoutNoeud(CelluleLNoeud * debutListeCLNode);
/**
 * @brief Fonction de destruction d'une cellule de commodité
 * @param CLCommodite Pointeur vers la cellule de commodité à détruire
 */
void freeOneCelluleLCommodite(CelluleLCommodite * CLCommodite);
/**
 * @brief Fonction de destruction d'une liste chaînée de commodités
 * @param debutListeCLCommodite Pointeur vers le début de la liste chaînée de commodités à détruire
 */
void freeAllCelluleLCommodite(CelluleLCommodite * debutListeCLCommodite);
/**
 * @brief Fonction de destruction d'un réseau
 * @param R Pointeur vers le réseau à détruire
 */
void freeReseau(Reseau * R);
/**
 * @brief Fonction de suppression d'un noeud d'un réseau
 * @param R Pointeur vers le réseau
 * @param node Pointeur vers le noeud à supprimer
 */
void removeNoeud(Reseau *R, Noeud * node);
/**
 * @brief Fonction de suppression d'un voisin d'un noeud
 * @param node Pointeur vers le noeud
 * @param vois Entier représentant le voisin
 */
void removeVoisinFromNode(Noeud * node, int vois);
/**
 * @brief Fonction d'initialisation des paramètres d'un réseau à partir d'un flux
 * @param f Flux de lecture
 * @param R Pointeur vers le réseau à initialiser
 */
void initReseauProperties(FILE * f, Reseau * R);

/**
 * @brief Fonction d'initialisation d'un noeud
 * @param string Chaîne de caractères à partir de laquelle le noeud sera initialisé
 * @return Pointeur vers la nouvelle instance allouée et initialisée de type Noeud
 */
Noeud *initNoeud(char *string);
/**
 * @brief Fonction d'initialisation d'une commodité
 * @param subStringRight Chaîne de caractères à partir de laquelle la commodité sera initialisée
 * @return Pointeur vers la nouvelle instance allouée et initialisée de type CelluleLCommodite
 */
CelluleLCommodite *initCommodite(char *subStringRight);
/**
 * @brief Fonction d'initialisation d'un voisin
 * @param R Pointeur vers le réseau
 * @param string Chaîne de caractères à partir de laquelle le voisin sera initialisé
 * @return 1 si l'initialisation s'est déroulé avec succès, 0 sinon
 */
int initVoisin(Reseau * R, char *string);

/**
 * @brief Fonction de lecture d'un fichier réseau
 * @param f Flux vers le fichier à lire
 * @param R Pointeur vers le réseau
 */
void lecture_fichier_reseau(FILE * f, Reseau * R);

/**
 * @brief Fonction d'affichage des voisins d'une cellule de noeud
 * @param output Flux d'affichage
 * @param CLNode Pointeur vers une cellule de noeud
 */
void displayVoisinOneCelluleLNoeud(FILE * output, CelluleLNoeud * CLNode);
/**
 * @brief Fonction d'affichage des voisins d'une liste de noeud
 * @param output Flux d'affichage
 * @param debutListeCLNode Pointeur vers le début de la liste chaînée de noeud à afficher
 */
void displayVoisinAllCelluleLNoeud(FILE * output,
		CelluleLNoeud * debutListeCLNode);
/**
 * @brief Fonction d'affichage d'un noeud
 * @param output Flux d'affichage
 * @param node Pointeur vers le noeud à afficher
 */
void displayNoeud(FILE * output, Noeud * node);
/**
 * @brief Fonction d'affichage d'une cellule de noeud
 * @param output Flux d'affichage
 * @param CLNode Pointeur vers une cellule de noeud à afficher
 */
void displayOneCelluleLNoeud(FILE * output, CelluleLNoeud * CLNode);
/**
 * @brief Fonction d'affichage d'une cellule de noeud (affichage avec %.2f au lieu de %g)
 * @param output Flux d'affichage
 * @param CLNode Pointeur vers une cellule de noeud à afficher
 */
void displayOneCelluleLNoeudSimple(FILE * output, CelluleLNoeud * CLNode);
/**
 * @brief Fonction d'affichage d'une liste chaînée de noeud
 * @param output Flux d'affichage
 * @param debutListeCLNode Pointeur vers le début de la liste chaînée de noeud à afficher
 */
void displayAllCelluleLNoeud(FILE * output, CelluleLNoeud * debutListeCLNode);
/**
 * @brief Fonction d'affichage d'une commodité
 * @param output Flux d'affichage
 * @param CLCommodite Pointeur vers une cellule de commodité à afficher
 */
void
displayOneCelluleLCommodite(FILE * output, CelluleLCommodite * CLCommodite);
/**
 * @brief Fonction d'affichage d'une liste de commodités
 * @param output Flux d'affichage
 * @param debutListeCLCommodite Pointeur vers le début de la liste chaînée de commodités à afficher
 */
void displayAllCelluleLCommodite(FILE * output,
		CelluleLCommodite * debutListeCLCommodite);
/**
 * @brief Fonction d'affichage d'un commentaire
 * @param output Flux d'affichage
 */
void displayComment(FILE * output);
/**
 * @brief Fonction d'affichage d'un réseau
 * @param output Flux d'affichage
 * @param R Pointeur vers le réseau à afficher
 */
void displayReseau(FILE * output, Reseau * R);


/**
 * @brief Fonction de recherche d'un noeud par son numéro u
 * @param debutListeNoeuds Pointeur vers le début de la liste chaînée de noeud
 * @param u Numéro du noeud à chercher
 * @return Pointeur vers l'instance correspondante ou NULL si la recherche a échouée.
 */
Noeud *rechercheNoeud(CelluleLNoeud * debutListeNoeuds, int u);
/**
 * @brief Fonction qui compte le nombre de câbles présents dans le réseau
 * @param R Pointeur vers le réseau
 * @return Le nombre de câbles présents dans le réseau
 */
int compteCable(Reseau * R);
/**
 * @brief Fonction d'écriture du réseau dans un flux
 * @param R Pointeur vers le réseau
 * @param f Pointeur vers le flux de sortie
 */
void ecrit_reseau_disque(Reseau * R, FILE * f);

/**
 * @brief Fonction de recherche d'un voisin
 * @param nd Pointeur vers le noeud à parcourir
 * @param u Numéro du voisin à chercher
 * @return 1 si le u est voisin de nd, 0 sinon
 */
int recherche_voisin(Noeud * nd, int u);

#endif

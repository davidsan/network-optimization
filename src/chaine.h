/**
 * \file chaine.h
 * \brief En-tête de chaîne
 * \author David San
 */

#ifndef __CHAINE_H__
#define __CHAINE_H__
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "erreur.h"
#include "fichier.h"
#include "stringTools.h"

/**
 * @struct point
 * Structure d'un point d'une chaône
 */
typedef struct point {
	double x, y; /*!< Coordonnées du point */
	struct point *ptSuiv; /*!< Pointeur vers le point suivant dans la chaîne */
} Point;

/**
 * @struct chaine
 * Elément de la liste chaînée des chaines
 */
typedef struct chaine {
	int numero; /*!< Numéro de la chaîne */
	Point *uneExtremite; /*!< Début de la chaîne */
	struct chaine *chSuiv; /*!< Lien vers la chaîne suivante */
} Chaine;

/**
 * @struct listechaine
 * Liste chaînée des chaînes
 */
typedef struct listechaine {
	int gamma; /*!< Nombre maximal de fibres par chaîne */
	int nbchaine; /*!< Nombre de chaînes */
	Chaine *LCh; /*!< La liste des chaînes */
} ListeChaine;


/**
 * @brief Fonction de création d'un point
 * @param x Ordonnée
 * @param y Abscisse
 * @return Pointeur vers la nouvelle instance allouée de type Point
 */
Point *creerPoint(double x, double y);
/**
 * @brief Fonction d'insertion d'un point à la fin de la liste chaînée de point
 * @param debutListePoint Pointeur vers le début de la liste des points
 * @param p Pointeur vers le point à insérer
 * @return Pointeur vers la liste chaînée de points mise à jour
 */
Point *insererPoint(Point * debutListePoint, Point * p);
/**
 * @brief Fonction d'insertion d'un point au début de la liste chaînée de point
 * @param debutListePoint Pointeur vers le début de la liste des points
 * @param p Pointeur vers le point à insérer
 * @return Pointeur vers la liste chaînée de points mise à jour
 */
Point *insererPointDebut(Point * debutListePoint, Point * p);
/**
 * @brief Fonction de création d'une chaîne
 * @param numero Numéro de la chaîne
 * @return Pointeur vers la nouvelle instance allouée de type Chaine
 */
Chaine *creerChaine(int numero);
/**
 * @brief Fonction d'insertion d'une chaîne à la fin de la liste des chaînes
 * @param debutListeChaine Pointeur vers le début de la liste des chaînes
 * @param c Pointeur vers l'élément à insérer
 * @return Pointeur vers la liste chaînée de chaînes mise à jour
 */
Chaine *insererChaine(Chaine * debutListeChaine, Chaine * c);

/**
 * @brief Fonction de création d'une structure ListeChaine
 * @return Pointeur vers la nouvelle instance allouée de type ListeChaine
 */
ListeChaine *creerListeChaine();

/**
 * @brief Fonction de destruction d'un point
 * @param p Pointeur vers le point à détruire
 */
void freeOnePoint(Point * p);
/**
 * @brief Fonction de destruction d'une liste de points
 * @param debutListePoint Pointeur vers le début de la liste chaînée de points
 */
void freeAllPoint(Point * debutListePoint);
/**
 * @brief Fonction de destruction d'une chaîne
 * @param c Pointeur vers la chaîne à détruire
 */
void freeOneChaine(Chaine * c);
/**
 * @brief Fonction de destruction d'une liste chaînée de chaîne
 * @param debutListeChaine Pointeur vers le début de la liste chaînée de chaînes à détruire
 */
void freeAllChaine(Chaine * debutListeChaine);
/**
 * @brief Fonction de destruction d'une structure de type ListeChaine
 * @param LC Pointeur vers la structure de type ListeChaine à détruire
 */
void freeListeChaine(ListeChaine * LC);

/**
 * @brief Fonction d'initialisation du nombre de chaînes et du "gamma" d'une structure de type ListeChaine
 * @param f Pointeur vers le flux de lecture
 * @param L Pointeur vers la structure ListeChaine à initialiser
 */
void initListeChaineProperties(FILE * f, ListeChaine * L);
/**
 * @brief Fonction de lecture d'une ListeChaine à partir d'un flux
 * @param f Pointeur vers le flux de lecture
 * @param L Pointeur vers la structure ListeChaine à lire
 */
void lecture_chaine(FILE * f, ListeChaine * L);


/**
 * @brief Fonction d'affichage d'un point
 * @param output Pointeur vers la sortie d'affichage
 * @param p Pointeur vers le point à afficher
 */
void displayOnePoint(FILE * output, Point * p);

/**
 * @brief Fonction d'affichage d'une liste chaînée de points
 * @param output Pointeur vers la sortie d'affichage
 * @param debutListePoint Pointeur vers le début de la liste chaînée de points
 */
void displayAllPoint(FILE * output, Point * debutListePoint);
/**
 * @brief Fonction d'affichage d'une chaîne
 * @param output Pointeur vers la sortie d'affichage
 * @param c Pointeur vers la chaîne à afficher
 */
void displayOneChaine(FILE * output, Chaine * c);
/**
 * @brief Fonction d'affichage d'une liste chaînée de chaînes
 * @param output Pointeur vers la sortie d'affichage
 * @param debutListeChaine Pointeur vers le début de la liste chaînée de chaînes
 */
void displayAllChaine(FILE * output, Chaine * debutListeChaine);
/**
 * @brief Fonction d'affichage d'une structure de type ListeChaine
 * @param output Pointeur vers la sortie d'affichage
 * @param LC Pointeur vers la structure de type ListeChaine à afficher
 */
void displayListeChaine(FILE * output, ListeChaine * LC);

/**
 * @brief Fonction qui compte le nombre de points d'une liste chaînée de points
 * @param debutListePoint Pointeur vers le début de la liste chaînée de points
 * @return Le nombre de points présents dans la liste chaînée de points
 */
int compterPoint(Point * debutListePoint);

/* alias vers displayListeChaine(FILE *output, ListeChaine *LC) */
/**
 * @brief Fonction alias vers la fonction displayListeChaine
 * @param L Pointeur vers la structure de type ListeChaine
 * @param f Pointeur vers la sortie d'écriture
 */
void ecrit_chaine_txt(ListeChaine * L, FILE * f);

/**
 * @brief Fonction qui calcule la longueur d'une chaîne
 * @param L Pointeur vers la chaîne
 * @return La longueur de la chaîne
 */
double longueurChaine(Chaine * L);
/**
 * @brief Fonction qui calcule la longueur totale d'une structure de type ListeChaine
 * @param L Pointeur vers la structure de type ListeChaine
 * @return La longueur totale d'une structure de type ListeChaine
 */
double longueurTotale(ListeChaine * L);
/**
 * @brief Fonction qui compte le nombre de points d'une structure de type ListeChaine
 * @param L Pointeur vers la structure de type ListeChaine
 * @return Le nombre de points d'une structure de type ListeChaine
 */
int compte_point(ListeChaine * L);

#endif

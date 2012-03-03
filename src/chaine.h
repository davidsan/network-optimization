#ifndef __CHAINE_H__
#define __CHAINE_H__
#include <stdlib.h>
#include <string.h>
#include "erreur.h"
#include "fichier.h"
#include "stringTools.h"

/* Structure d’un point d’une chaine */
typedef struct point {
    double x, y;		/* Coordonnees du point */
    struct point *ptSuiv;	/* Pointeur vers le point suivant dans la chaine */
} Point;

/* Element de la liste chaine des chaines */
typedef struct chaine {
    int numero;			/* Numero de la chaine */
    Point *uneExtremite;	/* Une des 2 extremites de la chaine */
    struct chaine *chSuiv;	/* Lien vers la chaine suivante */
} Chaine;

/* Liste chainee des chaines */
typedef struct {
    int gamma;			/* Nombre maximal de fibres par chaine */
    int nbchaine;		/* Nombre de chaines */
    Chaine *LCh;		/* La liste des chaines */
} ListeChaine;

/* Fonctions */

Point *creerPoint(double x, double y);
Point *insererPoint(Point * debutListePoint, Point * p);
Chaine *creerChaine(int numero, Point * uneExtremite);
Chaine *insererChaine(Chaine * debutListeChaine, Chaine * c);
ListeChaine *creerListeChaine();

void freeOnePoint(Point * p);
void freeAllPoint(Point * debutListePoint);
void freeOneChaine(Chaine * c);
void freeAllChaine(Chaine * debutListeChaine);
void freeListeChaine(ListeChaine * LC);

void initListeChaineProperties(FILE * f, ListeChaine * L);
void lecture_chaine(FILE * f, ListeChaine * L);

void displayOnePoint(FILE * output, Point * p);
void displayAllPoint(FILE * output, Point * debutListePoint);
void displayOneChaine(FILE * output, Chaine * c);
void displayAllChaine(FILE * output, Chaine * debutListeChaine);
void displayListeChaine(FILE * output, ListeChaine * LC);

/* pour l'affichage */
int compterPoint(Point * debutListePoint);

/* alias vers displayListeChaine(FILE *output, ListeChaine *LC) */
void ecrit_chaine_txt(ListeChaine * L, FILE * f);

#endif

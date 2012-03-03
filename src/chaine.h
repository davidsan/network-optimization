#ifndef __CHAINE_H__
#define __CHAINE_H__
#include <stdlib.h>
#include "erreur.h"

/* Structure d’un point d’une chaine */
typedef struct point {
   double x, y;                 /* Coordonnees du point */
   struct point *ptSuiv;        /* Pointeur vers le point suivant dans la chaine */
} Point;

/* Element de la liste chaine des chaines */
typedef struct chaine {
   int numero;                  /* Numero de la chaine */
   Point *uneExtremite;         /* Une des 2 extremites de la chaine */
   struct chaine *chSuiv;       /* Lien vers la chaine suivante */
} Chaine;

/* Liste chainee des chaines */
typedef struct {
   int gamma;                   /* Nombre maximal de fibres par chaine */
   int nbchaine;                /* Nombre de chaines */
   Chaine *LCh;                 /* La liste des chaines */
} ListeChaine;

/* Fonctions */
Point *creerPoint(double x, double y);
Point *insererPoint(Point *debutListePoint, Point *p);
Chaine *creerChaine(int numero, Point *uneExtremite);
Chaine *insererChaine(Chaine *debutListeChaine, Chaine *c);
ListeChaine *creerListeChaine(int gamma, int nbchaine, Chaine *LCh);
void freeOnePoint(Point *p);
void freeAllPoint(Point *debutListePoint);
void freeOneChaine(Chaine *c);
void freeAllChaine(Chaine *debutListeChaine);
void freeListeChaine(ListeChaine *LC);
void lecture_chaine(FILE *f, ListeChaine *L);

#endif

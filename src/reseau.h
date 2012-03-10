#ifndef __RESEAU_H__
#define __RESEAU_H__
#include "stringTools.h"
#include "erreur.h"
#include "fichier.h"
#include <string.h>
#include <stdlib.h>

 /* Element de la liste des noeuds voisins d’un noeud du reseau */
typedef struct voisin {
    int v;			/* Numero du voisin dans le Reseau */
    struct voisin *voisSuiv;	/* Pointeur sur le voisin suivant */

} Voisin;

 /* Noeud du reseau */
typedef struct noeud {
    int u;			/* Numero du noeud dans le Reseau */
    double x, y;		/* Coordonnees du noeud */
    Voisin *LVoisins;		/* Liste des noeuds voisins de u */
} Noeud;

 /* Element de la liste chainee des noeuds du reseau */
typedef struct celluleLNoeud {
    Noeud *ptrnoeud;		/* Pointeur sur un noeud du reseau */
    struct celluleLNoeud *noeudSuiv;	/* Noeud suivant dans la liste des noeuds */
} CelluleLNoeud;

 /* Element de la liste chainee des commodites du reseau */
typedef struct celluleLCommodite {
    int extr1, extr2;
    struct celluleLCommodite *commSuiv;
} CelluleLCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;		/* Nombre total de noeuds dans le Reseau */
    int gamma;			/* Nombre maximal de fibres dans un cable */
    CelluleLCommodite *LCommodites;	/* Liste des commodites a relier */
    CelluleLNoeud *LNoeuds;	/* Liste des noeuds du Reseau */
} Reseau;

Voisin *creerVoisin(int v);
Voisin *insererVoisin(Voisin * debutListeVoisin, Voisin * vois);

Noeud *creerNoeud(int u, double x, double y);

CelluleLNoeud *creerCelluleLNoeud(Noeud * ptrnoeud);
CelluleLNoeud *insererCelluleLNoeud(CelluleLNoeud * debutListeNoeuds,
				    CelluleLNoeud * node);

CelluleLCommodite *creerCelluleLCommodite(int extr1, int extr2);
CelluleLCommodite *insererCelluleLCommidite(CelluleLCommodite *
					    debutListeCommodite,
					    CelluleLCommodite * commodite);

Reseau *creerReseau();

void freeOneVoisin(Voisin * vois);
void freeAllVoisin(Voisin * debutListeVoisin);
void freeNoeud(Noeud * node);
void freeOneCelluleLNoeud(CelluleLNoeud * CLNode);
void freeAllCelluleLNoeud(CelluleLNoeud * debutListeCLNode);
void freeOneCelluleLCommodite(CelluleLCommodite * CLCommodite);
void freeAllCelluleLCommodite(CelluleLCommodite * debutListCLCommodite);
void freeReseau(Reseau * R);

void initReseauProperties(FILE * f, Reseau * R);
void lecture_fichier_reseau(FILE * f, Reseau * R);

Noeud *initNoeud(char *string);
CelluleLCommodite *initCommodite(char *subStringRight);
int initVoisin(Reseau * R, char *string);

void displayVoisinOneCelluleLNoeud(FILE * output, CelluleLNoeud * CLNode);
void displayVoisinAllCelluleLNoeud(FILE * output,
				   CelluleLNoeud * debutListeCLNode);
void displayNoeud(FILE * output, Noeud * node);
void displayOneCelluleLNoeud(FILE * output, CelluleLNoeud * CLNode);
void displayAllCelluleLNoeud(FILE * output,
			     CelluleLNoeud * debutListeCLNode);
void displayOneCelluleLCommodite(FILE * output,
				 CelluleLCommodite * CLCommodite);
void displayAllCelluleLCommodite(FILE * output,
				 CelluleLCommodite *
				 debutListeCLCommodite);
void displayComment(FILE * output);
void displayReseau(FILE * output, Reseau * R);

Noeud *rechercheNoeud(CelluleLNoeud * debutListeNoeuds, int u);
int compteCable(Reseau * R);
void ecrit_reseau_disque(Reseau * R, FILE * f);
int recherche_voisin(Noeud * nd, int u);

#endif

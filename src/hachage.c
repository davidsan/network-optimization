/**
 * \file hachage.c
 * \brief Source d'hachage
 * \author David San
 */
#include "hachage.h"

Hachage *creerHachage(int m) {
	Hachage *h = NULL;
	int i;
	h = (Hachage *) (malloc(sizeof(Hachage)));
	if (!h) {
		leverErreur("creerHachage");
		return NULL;
	}
	h->m = m;
	h->nbElement = 0;
	h->tab = (CelluleLNoeud **) (malloc(sizeof(CelluleLNoeud *) * m));
	for (i = 0; i < m; i++) {
		h->tab[i] = NULL;
	}
	return h;
}

void insererHachage(Hachage * h, CelluleLNoeud * node) {
	int index = hash(generateKey(node->ptrnoeud->x, node->ptrnoeud->y), h);
	CelluleLNoeud *tmp = h->tab[index];
	CelluleLNoeud *prec = NULL;
	h->nbElement++;
	while (tmp) {
		prec = tmp;
		tmp = tmp->noeudSuiv;
	}
	if (prec == NULL) {
		h->tab[index] = node;
		return;
	}
	prec->noeudSuiv = node;
}

void freeHachageTable(Hachage * h) {
	int i;
	for (i = 0; i < h->m; i++) {
		freeAllCelluleLNoeudWithoutNoeud(h->tab[i]);
	}
}

void freeHachage(Hachage * h) {
	freeHachageTable(h);
	free(h->tab);
	free(h);
}

double generateKey(double x, double y) {
	return (y + (x + y) * (x + y + 1) / 2);
}

int hash(double k, Hachage * h) {
	double A = (2.23606798 - 1) / 2; // 2.23606798 =~ sqrt(5)
	return (abs((long) (h->m * ((k * A) - ((long) (k * A))))));
}

void displayHachage(Hachage * h) {
	int i;
	for (i = 0; i < h->m; i++) {
		CelluleLNoeud *tmp = h->tab[i];
		printf("[%d] : ", i);
		while (tmp) {
			displayOneCelluleLNoeudSimple(stdout, tmp);
			tmp = tmp->noeudSuiv;
		}
		printf("\n");
	}
	printf("\n");
}

Noeud *rechercheNoeudHachage(Hachage * h, double x, double y) {
	int index = hash(generateKey(x, y), h);
	CelluleLNoeud *tmp = h->tab[index];
	while (tmp) {
		if (tmp->ptrnoeud->x == x && tmp->ptrnoeud->y == y) {
			return tmp->ptrnoeud;
		}
		tmp = tmp->noeudSuiv;
	}
	return NULL;
}

Noeud *recherche_cree_noeud_hachage(Reseau * R, Hachage * h, double x, double y) {
	Noeud *match = NULL;
	CelluleLNoeud *node = NULL;
	match = rechercheNoeudHachage(h, x, y);
	/* si le noeud est déjà dans la hashtable */
	if (match != NULL) {
		return match;
	}
	/* insertion dans la hashtable */
	node = creerCelluleLNoeud(creerNoeud(h->nbElement, x, y));
	insererHachage(h, node);
	/* insertion dans le reseau (en tête de liste) */
	R->LNoeuds = insererCelluleLNoeudDebut(R->LNoeuds,
			creerCelluleLNoeud(node-> ptrnoeud));
	return NULL;
}

void recree_reseau_hachage(ListeChaine * L, Reseau * R, Hachage * H) {
	Chaine *tmp = NULL;
	Point *tmpPoint = NULL;
	Noeud *noeudMatch = NULL;
	Noeud *noeudNextMatch = NULL;
	int numVoisinCurrent;
	int numVoisinNext;
	/* initialisation du gamma */
	R->gamma = L->gamma;
	/* initialisation des noeuds du réseau */
	tmp = L->LCh;
	while (tmp) {
		tmpPoint = tmp->uneExtremite;
		recherche_cree_noeud_hachage(R, H, tmpPoint->x, tmpPoint->y);
		while (tmpPoint->ptSuiv) {
			recherche_cree_noeud_hachage(R, H, tmpPoint->ptSuiv->x,
					tmpPoint->ptSuiv->y);
			noeudMatch = rechercheNoeudHachage(H, tmpPoint->x, tmpPoint->y);
			noeudNextMatch = rechercheNoeudHachage(H, tmpPoint->ptSuiv->x,
					tmpPoint->ptSuiv->y);
			numVoisinCurrent = noeudMatch->u;
			numVoisinNext = noeudNextMatch->u;
			/* initialisation des voisins */
			/* ajoute le noeud suivant au voisin du noeud courant */
			if (!recherche_voisin(noeudMatch, numVoisinNext)) {
				noeudMatch->LVoisins = insererVoisinDebut(noeudMatch->LVoisins,
						creerVoisin(numVoisinNext));
			}
			/* ajoute le noeud courant au voisin du noeud suivant */
			if (!recherche_voisin(noeudNextMatch, numVoisinCurrent)) {
				noeudNextMatch->LVoisins
						= insererVoisinDebut(noeudNextMatch->LVoisins,
								creerVoisin(numVoisinCurrent));
			}
			tmpPoint = tmpPoint->ptSuiv;
		}
		R->LCommodites = insererCelluleLCommiditeDebut(
				R->LCommodites,
				creerCelluleLCommodite(
						recherche_noeud(R, tmpPoint->x, tmpPoint->y)->u,
						recherche_noeud(R, tmp-> uneExtremite-> x,
								tmp-> uneExtremite-> y)-> u));
		tmp = tmp->chSuiv;
	}
	/* initialisation du nombre d'éléments */
	R->nbNoeuds = H->nbElement;
}

/**
 * \file build.h
 * \brief Source de build
 * \author David San
 */
#include "build.h"

Noeud *recherche_noeud(Reseau * R, double x, double y) {
	CelluleLNoeud *tmp = NULL;
	if (R) {
		tmp = R->LNoeuds;
	}
	while (tmp) {
		if (tmp->ptrnoeud->x == x && tmp->ptrnoeud->y == y) {
			return tmp->ptrnoeud;
		}
		tmp = tmp->noeudSuiv;
	}
	return NULL;
}

Noeud *recherche_cree_noeud(Reseau * R, double x, double y) {
	Noeud *match = recherche_noeud(R, x, y);
	if (match) {
		return match;
	}
	Noeud *ptrnoeud = creerNoeud(R->nbNoeuds, x, y);
	CelluleLNoeud *CLn = creerCelluleLNoeud(ptrnoeud);
	R->LNoeuds = insererCelluleLNoeudTrie(R->LNoeuds, CLn);
	R->nbNoeuds++;
	return NULL; // important
}

int compare(double x1, double y1, double x2, double y2) {
	return ((x1 < x2) || (((fabs(x1 - x2)) < EPS) && (y1 < y2)));
}

CelluleLNoeud *rechercheCelluleLNoeud(Reseau * R, Noeud * node) {
	CelluleLNoeud *tmp = R->LNoeuds;
	while (tmp) {
		if (node == tmp->ptrnoeud) {
			return tmp;
		}
		tmp = tmp->noeudSuiv;
	}
	if (!tmp) {
		leverErreur("rechercheCelluleLNoeud");
	}
	return NULL;
}

CelluleLNoeud *purgeDuplicate(CelluleLNoeud * L) {
	CelluleLNoeud *tmp = L;
	CelluleLNoeud *result = NULL;
	while (tmp) {
		result = insererCelluleLNoeudUnique(result, tmp->ptrnoeud);
		tmp = tmp->noeudSuiv;
	}
	return result;
}

void renumberList(CelluleLNoeud * L) {
	CelluleLNoeud *tmp = L;
	int cpt = 0;
	while (tmp) {
		tmp->ptrnoeud->u = cpt;
		cpt++;
		tmp = tmp->noeudSuiv;
	}
}

void recree_reseau(ListeChaine * L, Reseau * R) {
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
		recherche_cree_noeud(R, tmpPoint->x, tmpPoint->y);
		while (tmpPoint->ptSuiv) {
			recherche_cree_noeud(R, tmpPoint->ptSuiv->x, tmpPoint->ptSuiv->y);
			noeudMatch = recherche_noeud(R, tmpPoint->x, tmpPoint->y);
			noeudNextMatch = recherche_noeud(R, tmpPoint->ptSuiv->x,
					tmpPoint->ptSuiv->y);
			numVoisinCurrent = recherche_noeud(R, tmpPoint->x, tmpPoint->y)->u;
			numVoisinNext = recherche_noeud(R, tmpPoint->ptSuiv->x,
					tmpPoint->ptSuiv->y)->u;
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
		R->LCommodites = insererCelluleLCommidite(
				R->LCommodites,
				creerCelluleLCommodite(
						recherche_noeud(R, tmpPoint->x, tmpPoint->y)->u,
						recherche_noeud(R, tmp-> uneExtremite-> x,
								tmp-> uneExtremite-> y)->u));
		tmp = tmp->chSuiv;
	}
}

CelluleLNoeud *insererCelluleLNoeudTrie(CelluleLNoeud * debutListeNoeuds,
		CelluleLNoeud * node) {
	CelluleLNoeud *tmp = debutListeNoeuds;
	CelluleLNoeud *prec = NULL;
	if (!tmp) {
		return node;
	}
	while (tmp) {
		if (!compare(tmp->ptrnoeud->x, tmp->ptrnoeud->y, node->ptrnoeud->x,
				node->ptrnoeud->y)) {
			break;
		}
		prec = tmp;
		tmp = tmp->noeudSuiv;
	}
	if (!tmp) {
		prec->noeudSuiv = node;
		return debutListeNoeuds;
	}
	if (tmp == debutListeNoeuds) {
		node->noeudSuiv = debutListeNoeuds;
		return node;
	}
	node->noeudSuiv = tmp;
	prec->noeudSuiv = node;

	return debutListeNoeuds;
}

/**
 * \file abr.c
 * \brief Source de abr
 * \author David San
 */
#include "abr.h"

AVL *creerAVL(Noeud * content, AVL * left, AVL * right) {
	AVL *new = (AVL *) (malloc(sizeof(AVL)));
	if (!new) {
		leverErreur("creerAVL allocation mémoire");
		return NULL;
	}
	new->content = content;
	new->left = left;
	new->right = right;
	new->height = 0;
	return new;
}

void freeAVL(AVL * root) {
	if (root) {
		freeAVL(root->left);
		freeAVL(root->right);
	}
	free(root);
}

int getHeight(AVL * node) {
	if (node != NULL) {
		return node->height;
	} else {
		return 0;
	}
}

int isBalanced(AVL * node) {
	int diff;
	if (!node) {
		return 1;
	}
	diff = abs(getHeight(node->left) - getHeight(node->right));
	return diff <= 1;
}

int checkBalance(AVL * root) {
	if (!root) {
		return 1;
	}
	return isBalanced(root) && checkBalance(root->left) && checkBalance(
			root->right);
}

int height(AVL * root) {
	if (!root) {
		return 0;
	} else {
		return 1 + max(height(root->left), height(root->right));
	}
}

int max(int a, int b) {
	if (a < b) {
		return b;
	}
	return a;
}

int compareNode(Noeud * a, Noeud * b) {
	return compare(a->x, a->y, b->x, b->y);
}

AVL *rotateLeft(AVL * root) {
	AVL *nroot = root->left;
	root->left = nroot->right;
	nroot->right = root;
	/* maj hauteur */
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	nroot->height = max(getHeight(nroot->left), getHeight(root)) + 1;
	return nroot;
}

AVL *rotateRight(AVL * root) {
	AVL *nroot = root->right;
	root->right = nroot->left;
	nroot->left = root;
	/* maj hauteur */
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	nroot->height = max(getHeight(nroot->right), getHeight(root)) + 1;
	return nroot;
}

AVL *doubleRotateLeft(AVL * root) {
	root->left = rotateRight(root->left);
	return rotateLeft(root);
}

AVL *doubleRotateRight(AVL * root) {
	root->right = rotateLeft(root->right);
	return rotateRight(root);
}

Noeud *rechercheNoeudAVL(AVL * root, double x, double y) {
	if (root == NULL) {
		return NULL;
	}
	if ((fabs(x - root->content->x) < EPS)
			&& (fabs(y - root->content->y) < EPS)) {
		return root->content;
	}
	if (compare(x, y, root->content->x, root->content->y)) {
		return rechercheNoeudAVL(root->left, x, y);
	} else {
		return rechercheNoeudAVL(root->right, x, y);
	}
}

AVL *insererAVL(AVL * root, Noeud * node) {
	/* insertion dans arbre vide */
	if (root == NULL) {
		root = creerAVL(node, NULL, NULL);
		return root;
	}
	/* insertion avant */
	if (compareNode(node, root->content)) {
		root->left = insererAVL(root->left, node);
	} else {
		/* insertion après (si noeud pas déjà présent) */
		if (node->x != root->content->x || node->y != root->content->y) {
			root->right = insererAVL(root->right, node);
		} else {
			/* sinon déjà présent */
			return root;
		}
	}
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	if (getHeight(root->left) - getHeight(root->right) == 2) {
		if (compareNode(node, root->left->content)) {
			root = rotateLeft(root);
		} else {
			root = doubleRotateLeft(root);
		}
	}
	if (getHeight(root->right) - getHeight(root->left) == 2) {
		if (compareNode(root->right->content, node)) {
			root = rotateRight(root);
		} else {
			root = doubleRotateRight(root);
		}
	}
	//      if (!checkBalance(root)) {
	//              fprintf(stderr, "L'arbre n'est pas équilibré\n");
	//      }

	return root;
}

void displayNodeAVL(AVL * node) {
	if (node) {
		if (node->content) {
			fprintf(stderr, "%d ", node->content->u);
		} else {
			fprintf(stderr, "@");
		}
	} else {
		fprintf(stderr, "#");
	}
}

void displayAVL(AVL * root) {
	displayNodeAVL(root);
	if (root) {
		fprintf(stderr, " g:");
		displayNodeAVL(root->left);
		fprintf(stderr, " d:");
		displayNodeAVL(root->right);
		fprintf(stderr, "\n");
		displayAVL(root->left);
		displayAVL(root->right);
	}
}

AVL *insererAVL_NoCheck(AVL * root, double x, double y, int * insertion,
		int * compteur, Noeud ** node) {
	/* insertion dans arbre vide */
	if (root == NULL) {
		*node = creerNoeud((*compteur)++, x, y);
		root = creerAVL(*node, NULL, NULL);
		*insertion = 1;
		return root;
	}
	/* insertion avant */
	if (compare(x, y, root->content->x, root->content->y)) {
		root->left = insererAVL_NoCheck(root->left, x, y, insertion, compteur,
				node);
	} else {
		/* insertion après (si noeud pas déjà présent) */
		if (x != root->content->x || y != root->content->y) {
			root->right = insererAVL_NoCheck(root->right, x, y, insertion,
					compteur, node);

		} else {
			/* sinon déjà présent */
			*node = root->content;
			return root;
		}
	}
	/* rééquilibrage */
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	if (getHeight(root->left) - getHeight(root->right) == 2) {

		if (compare(x, y, root->left->content->x, root->left->content->y)) {
			root = rotateLeft(root);
		} else {
			root = doubleRotateLeft(root);
		}
	}
	if (getHeight(root->right) - getHeight(root->left) == 2) {
		if (compare(root->right->content->x, root->right->content->y, x, y)) {
			root = rotateRight(root);
		} else {
			root = doubleRotateRight(root);
		}
	}
	return root;
}

void recree_reseau_AVL_NoCheck(ListeChaine * L, Reseau * R) {
	AVL *T = NULL;
	Chaine *tmp = NULL;
	Point *tmpPoint = NULL;
	Noeud *noeudMatch = NULL;
	Noeud *noeudNextMatch = NULL;
	int numVoisinCurrent;
	int numVoisinNext;
	int compteur = 0;
	int insertion = 0;
	/* initialisation du gamma */
	R->gamma = L->gamma;
	/* initialisation des noeuds du réseau */
	tmp = L->LCh;
	while (tmp) {

		tmpPoint = tmp->uneExtremite;
		noeudMatch = NULL;
		T = insererAVL_NoCheck(T, tmpPoint->x, tmpPoint->y, &insertion,
				&compteur, &noeudMatch);
		/* insertion dans le reseau (en tête de liste) */
		if (insertion == 1) {
			R->LNoeuds = insererCelluleLNoeudDebut(R->LNoeuds,
					creerCelluleLNoeud(noeudMatch));
			insertion = 0;
		}

		while (tmpPoint->ptSuiv) {

			noeudNextMatch = NULL;
			T = insererAVL_NoCheck(T, tmpPoint->ptSuiv->x, tmpPoint->ptSuiv->y,
					&insertion, &compteur, &noeudNextMatch);

			if (insertion == 1) {

				/* insertion dans le reseau (en tête de liste) */
				R->LNoeuds = insererCelluleLNoeudDebut(R->LNoeuds,
						creerCelluleLNoeud(noeudNextMatch));
				insertion = 0;
			}

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
			noeudMatch = noeudNextMatch;
		}

		R->LCommodites = insererCelluleLCommiditeDebut(
				R->LCommodites,
				creerCelluleLCommodite(
						recherche_noeud(R, tmpPoint->x, tmpPoint->y)->u,
						recherche_noeud(R, tmp->uneExtremite->x,
								tmp->uneExtremite-> y)->u));
		tmp = tmp->chSuiv;

	}
	/* initialisation du nombre d'éléments */
	R->nbNoeuds = compteur; // OK
	freeAVL(T);
}

void recree_reseau_AVL(ListeChaine * L, Reseau * R) {
	AVL *T = NULL;
	Chaine *tmp = NULL;
	Point *tmpPoint = NULL;
	Noeud *noeudMatch = NULL;
	Noeud *noeudNextMatch = NULL;
	int numVoisinCurrent;
	int numVoisinNext;
	int compteur = 0;
	/* initialisation du gamma */
	R->gamma = L->gamma;
	/* initialisation des noeuds du réseau */
	tmp = L->LCh;
	while (tmp) {
		tmpPoint = tmp->uneExtremite;
		noeudMatch = rechercheNoeudAVL(T, tmpPoint->x, tmpPoint->y);
		if (noeudMatch == NULL) {
			noeudMatch = creerNoeud(compteur++, tmpPoint->x, tmpPoint->y);
			T = insererAVL(T, noeudMatch);
			/* insertion dans le reseau (en tête de liste) */
			R->LNoeuds = insererCelluleLNoeudDebut(R->LNoeuds,
					creerCelluleLNoeud(noeudMatch));
		}
		while (tmpPoint->ptSuiv) {

			noeudNextMatch = rechercheNoeudAVL(T, tmpPoint->ptSuiv->x,
					tmpPoint->ptSuiv->y);

			if (noeudNextMatch == NULL) {
				noeudNextMatch = creerNoeud(compteur++, tmpPoint->ptSuiv->x,
						tmpPoint->ptSuiv->y);

				T = insererAVL(T, noeudNextMatch);

				/* insertion dans le reseau (en tête de liste) */
				R->LNoeuds = insererCelluleLNoeudDebut(R->LNoeuds,
						creerCelluleLNoeud(noeudNextMatch));
			}
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
			noeudMatch = noeudNextMatch;
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
	R->nbNoeuds = compteur; // OK

	//	fprintf(stderr, "Hauteur de l'arbre : %d\n", height(T));
	freeAVL(T);
}

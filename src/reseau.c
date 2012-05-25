/**
 * \file reseau.c
 * \brief Source de réseau
 * \author David San
 */
#include "reseau.h"

Voisin *creerVoisin(int v) {
	Voisin *new = NULL;
	if ((new = (Voisin *) (malloc(sizeof(Voisin)))) == NULL) {
		leverErreur("allocation mémoire");
		return NULL;
	}
	new->v = v;
	new->voisSuiv = NULL;
	new->gamma = 0;
	return new;
}

Voisin *insererVoisin(Voisin * debutListeVoisin, Voisin * vois) {
	Voisin *tmp = NULL;
	if (debutListeVoisin == NULL) {
		return vois;
	}
	tmp = debutListeVoisin;
	while (tmp->voisSuiv) {
		tmp = tmp->voisSuiv;
	}
	tmp->voisSuiv = vois;
	return debutListeVoisin;
}

Voisin *insererVoisinDebut(Voisin * debutListeVoisin, Voisin * vois) {
	vois->voisSuiv = debutListeVoisin;
	return vois;
}

Noeud *creerNoeud(int u, double x, double y) {
	Noeud *new = NULL;
	if ((new = (Noeud *) (malloc(sizeof(Noeud)))) == NULL) {
		leverErreur("allocation mémoire");
		return NULL;
	}
	new->u = u;
	new->x = x;
	new->y = y;
	new->LVoisins = NULL;
	return new;
}

CelluleLNoeud *creerCelluleLNoeud(Noeud * ptrnoeud) {
	CelluleLNoeud *new = NULL;
	if ((new = (CelluleLNoeud *) (malloc(sizeof(CelluleLNoeud)))) == NULL) {
		leverErreur("allocation mémoire");
		return NULL;
	}
	new->ptrnoeud = ptrnoeud;
	new->noeudSuiv = NULL;
	return new;
}

CelluleLNoeud *insererCelluleLNoeud(CelluleLNoeud * debutListeNoeuds,
		CelluleLNoeud * node) {
	CelluleLNoeud *tmp = debutListeNoeuds;
	if (tmp == NULL) {
		return node;
	}
	while (tmp->noeudSuiv) {
		tmp = tmp->noeudSuiv;
	}
	tmp->noeudSuiv = node;
	return debutListeNoeuds;
}

CelluleLNoeud *insererCelluleLNoeudDebut(CelluleLNoeud * debutListeNoeuds,
		CelluleLNoeud * node) {
	node->noeudSuiv = debutListeNoeuds;
	return node;
}

CelluleLNoeud *insererCelluleLNoeudUnique(CelluleLNoeud * debutListeNoeuds,
		Noeud * node) {
	CelluleLNoeud *tmp = debutListeNoeuds;
	CelluleLNoeud *prec = NULL;
	if (tmp == NULL) {
		return creerCelluleLNoeud(node);
	}
	while (tmp) {
		if (tmp->ptrnoeud->u == node->u) {
			return debutListeNoeuds;
		}
		prec = tmp;
		tmp = tmp->noeudSuiv;
	}
	prec->noeudSuiv = creerCelluleLNoeud(node);
	return debutListeNoeuds;
}

CelluleLCommodite *creerCelluleLCommodite(int extr1, int extr2) {
	CelluleLCommodite *new = NULL;
	if ((new = (CelluleLCommodite *) (malloc(sizeof(CelluleLCommodite))))
			== NULL) {
		leverErreur("allocation mémoire");
		return NULL;
	}
	new->extr1 = extr1;
	new->extr2 = extr2;
	new->commSuiv = NULL;
	return new;
}

CelluleLCommodite *insererCelluleLCommidite(
		CelluleLCommodite * debutListeCommodite, CelluleLCommodite * commodite) {
	CelluleLCommodite *tmp = NULL;
	if (debutListeCommodite == NULL) {
		return commodite;
	}
	tmp = debutListeCommodite;
	while (tmp->commSuiv) {
		tmp = tmp->commSuiv;
	}
	tmp->commSuiv = commodite;
	return debutListeCommodite;
}

CelluleLCommodite *insererCelluleLCommiditeDebut(
		CelluleLCommodite * debutListeCommodite, CelluleLCommodite * commodite) {
	commodite->commSuiv = debutListeCommodite;
	return commodite;
}

Reseau *creerReseau() {
	Reseau *new = NULL;
	if ((new = (Reseau *) (malloc(sizeof(Reseau)))) == NULL) {
		leverErreur("allocation mémoire");
		return NULL;
	}
	new->nbNoeuds = 0;
	new->gamma = 0;
	new->LCommodites = NULL;
	new->LNoeuds = NULL;
	return new;
}

void freeOneVoisin(Voisin * vois) {
	free(vois);
}

void freeAllVoisin(Voisin * debutListeVoisin) {
	Voisin *tmp = debutListeVoisin;
	Voisin *mem = NULL;
	while (tmp) {
		mem = tmp->voisSuiv;
		freeOneVoisin(tmp);
		tmp = mem;
	}
}

void freeNoeud(Noeud * node) {
	freeAllVoisin(node->LVoisins);
	free(node);
}

void freeOneCelluleLNoeud(CelluleLNoeud * CLNode) {
	freeNoeud(CLNode->ptrnoeud);
	free(CLNode);
}

void freeAllCelluleLNoeud(CelluleLNoeud * debutListeCLNode) {
	CelluleLNoeud *tmp = debutListeCLNode;
	CelluleLNoeud *mem = NULL;
	while (tmp) {
		mem = tmp->noeudSuiv;
		freeOneCelluleLNoeud(tmp);
		tmp = mem;
	}
}

void freeAllCelluleLNoeudWithoutNoeud(CelluleLNoeud * debutListeCLNode) {
	CelluleLNoeud *tmp = debutListeCLNode;
	CelluleLNoeud *mem = NULL;
	while (tmp) {
		mem = tmp->noeudSuiv;
		free(tmp);
		tmp = mem;
	}
}

void freeOneCelulleLCommodite(CelluleLCommodite * CLCommodite) {
	free(CLCommodite);
}

void freeAllCelulleLCommodite(CelluleLCommodite * debutListeCLCommodite) {
	CelluleLCommodite *tmp = debutListeCLCommodite;
	CelluleLCommodite *mem = NULL;
	while (tmp) {
		mem = tmp->commSuiv;
		freeOneCelulleLCommodite(tmp);
		tmp = mem;
	}
}

void freeReseau(Reseau * R) {
	freeAllCelulleLCommodite(R->LCommodites);
	freeAllCelluleLNoeud(R->LNoeuds);
	free(R);
}

void removeNoeud(Reseau *R, Noeud * node) {
	R->nbNoeuds--;
	CelluleLNoeud * current = R->LNoeuds;
	CelluleLNoeud * prec = NULL;
	if (node == NULL) {
		leverErreur("removeNoeud incorrect arg");
	}
	while (current) {
		if (current->ptrnoeud == node) {
			fprintf(stderr, "yoyo");
			break;
		}
		prec = current;
		current = current->noeudSuiv;
	}
	if (current == NULL) {
		leverErreur("removeNoeud");
	}
	if (prec) {
		prec->noeudSuiv = current->noeudSuiv;
	} else {
		R->LNoeuds = current->noeudSuiv;
	}
	Voisin * v = node->LVoisins;
	while (v) {
		Noeud * tmpNode = rechercheNoeud(R->LNoeuds, v->v);
		if (tmpNode) {
			removeVoisinFromNode(tmpNode, node->u);
		}
		v = v->voisSuiv;
	}

	freeOneCelluleLNoeud(current);
}

void removeVoisinFromNode(Noeud * node, int vois) {
	Voisin * current = node->LVoisins;
	Voisin * prec = NULL;
	while (current) {
		if (current->v == vois) {
			break;
		}
		prec = current;
		current = current->voisSuiv;
	}
	if (!prec) {
		node->LVoisins = current->voisSuiv;
	} else {
		prec->voisSuiv = current->voisSuiv;
	}
}

void initReseauProperties(FILE * f, Reseau * R) {
	char buffer[BUFFER_SIZE];
	if (!readLine(f, buffer)) {
		leverErreur("lecture fichier");
		return;
	}
	R->nbNoeuds = scanNbNodes(buffer);
	if (!readLine(f, buffer)) {
		leverErreur("lecture fichier");
		return;
	}
	// scanNbCables(buffer);
	if (!readLine(f, buffer)) {
		leverErreur("lecture fichier");
		return;
	}
	R->gamma = scanGamma(buffer);
}

Noeud *initNoeud(char *string) {
	float x, y;
	int u;
	sscanf(string, "%d %f %f", &u, &x, &y);
	return creerNoeud(u, x, y);
}

CelluleLCommodite *initCommodite(char *string) {
	int extr1, extr2;
	sscanf(string, "%d %d", &extr1, &extr2);
	return creerCelluleLCommodite(extr1, extr2);
}

int initVoisin(Reseau * R, char *string) {
	int extr1, extr2;
	Noeud *match = NULL;
	sscanf(string, "%d %d", &extr1, &extr2);
	/* chercher le noeud */
	match = rechercheNoeud(R->LNoeuds, extr1);
	if (!match) {
		return 0;
	}
	match->LVoisins = insererVoisin(match->LVoisins, creerVoisin(extr2));
	match = rechercheNoeud(R->LNoeuds, extr2);
	if (!match) {
		return 0;
	}
	match->LVoisins = insererVoisin(match->LVoisins, creerVoisin(extr1));
	return 1;
}

void lecture_fichier_reseau(FILE * f, Reseau * R) {
	char buffer[BUFFER_SIZE];
	char *subStringLeft = NULL;
	char *subStringRight = NULL;

	/* lecture et initialisation des propriétés du Reseau */
	initReseauProperties(f, R);
	/* boucle */
	while (readLine(f, buffer)) {
		/* ignorer si commentaire */
		if (isComment(buffer))
			continue;

		/* découpage en 2 parties à traiter */
		subStringLeft = strtok(buffer, " ");
		subStringRight = strtok(NULL, "\0");

		switch (subStringLeft[0]) {
		case 'v':
			R->LNoeuds = insererCelluleLNoeud(R->LNoeuds,
					creerCelluleLNoeud(initNoeud(subStringRight)));
			break;
		case 'a':
			if (!initVoisin(R, subStringRight)) {
				leverErreur("initialisation des voisins");
			}
			break;
		case 'k':
			R->LCommodites = insererCelluleLCommidite(R->LCommodites,
					initCommodite(subStringRight));
			break;
		}
	}
}

void displayVoisinOneCelluleLNoeud(FILE * output, CelluleLNoeud * CLNode) {
	int u = CLNode->ptrnoeud->u;
	Voisin *tmp = CLNode->ptrnoeud->LVoisins;
	while (tmp) {
		if (u < tmp->v) {
			fprintf(output, "a %d %d\n", u, tmp->v);
		}
		tmp = tmp->voisSuiv;
	}
}

void displayVoisinAllCelluleLNoeud(FILE * output,
		CelluleLNoeud * debutListeCLNode) {
	CelluleLNoeud *tmp = debutListeCLNode;
	while (tmp) {
		displayVoisinOneCelluleLNoeud(output, tmp);
		tmp = tmp->noeudSuiv;
	}
}

void displayNoeud(FILE * output, Noeud * node) {
	fprintf(output, "v %d %g %g\n", node->u, node->x, node->y);
}

void displayOneCelluleLNoeud(FILE * output, CelluleLNoeud * CLNode) {
	displayNoeud(output, CLNode->ptrnoeud);
}

void displayOneCelluleLNoeudSimple(FILE * output, CelluleLNoeud * CLNode) {
	fprintf(output, "%.2f %.2f ; ", CLNode->ptrnoeud->x, CLNode->ptrnoeud->y);
}

void displayAllCelluleLNoeud(FILE * output, CelluleLNoeud * debutListeCLNode) {
	CelluleLNoeud *tmp = debutListeCLNode;
	while (tmp) {
		displayOneCelluleLNoeud(output, tmp);
		tmp = tmp->noeudSuiv;
	}
}

void displayOneCelluleLCommodite(FILE * output, CelluleLCommodite * CLCommodite) {
	fprintf(output, "k %d %d\n", CLCommodite->extr1, CLCommodite->extr2);
}

void displayAllCelluleLCommodite(FILE * output,
		CelluleLCommodite * debutListeCLCommodite) {
	CelluleLCommodite *tmp = debutListeCLCommodite;
	while (tmp) {
		displayOneCelluleLCommodite(output, tmp);
		tmp = tmp->commSuiv;
	}
}

void displayComment(FILE * output) {
	fprintf(output, "c\n");
}

void displayReseau(FILE * output, Reseau * R) {
	fprintf(output, "c NbNodes: %d\n", R->nbNoeuds);
	fprintf(output, "c NbCables: %d\n", compteCable(R));
	fprintf(output, "c Gamma: %d\n", R->gamma);
	displayComment(output);
	displayAllCelluleLNoeud(output, R->LNoeuds);
	displayComment(output);
	displayVoisinAllCelluleLNoeud(output, R->LNoeuds);
	displayComment(output);
	displayAllCelluleLCommodite(output, R->LCommodites);
}

Noeud *rechercheNoeud(CelluleLNoeud * debutListeNoeuds, int u) {
	CelluleLNoeud *tmp = debutListeNoeuds;
	while (tmp) {
		if (tmp->ptrnoeud->u == u) {
			return tmp->ptrnoeud;
		}
		tmp = tmp->noeudSuiv;
	}
	leverErreur("noeud introuvable");
	return NULL;
}

int compteCable(Reseau * R) {
	CelluleLNoeud *tmp = R->LNoeuds;
	Voisin *tmpVoisin = NULL;
	int cpt = 0;
	while (tmp) {
		tmpVoisin = tmp->ptrnoeud->LVoisins;
		while (tmpVoisin) {
			cpt++;
			tmpVoisin = tmpVoisin->voisSuiv;
		}
		tmp = tmp->noeudSuiv;
	}
	return cpt / 2;
}

void ecrit_reseau_disque(Reseau * R, FILE * f) {
	displayReseau(f, R);
}

int recherche_voisin(Noeud * nd, int u) {
	Voisin *tmp = NULL;
	if (!nd) {
		leverErreur("argument invalide");
		return 0;
	}
	tmp = nd->LVoisins;
	while (tmp) {
		if (tmp->v == u) {
			return 1;
		}
		tmp = tmp->voisSuiv;
	}
	return 0;
}

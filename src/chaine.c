/**
 * \file chaine.c
 * \brief En-tête de chaîne
 * \author David San
 */
#include "chaine.h"

Point *creerPoint(double x, double y) {
	Point *p = (Point *) (malloc(sizeof(Point)));
	if (!p) {
		leverErreur("allocation mémoire Point");
		return NULL;
	}
	p->x = x;
	p->y = y;
	p->ptSuiv = NULL;
	return p;
}

/* insertion en fin de liste */
/* renvoie le Point du début de liste */
Point *insererPoint(Point * debutListePoint, Point * p) {
	Point *tmp = debutListePoint;
	if (tmp == NULL) {
		return p;
	}
	while (tmp->ptSuiv) {
		tmp = tmp->ptSuiv;
	}
	tmp->ptSuiv = p;
	return debutListePoint;
}

Point *insererPointDebut(Point * debutListePoint, Point * p) {
	p->ptSuiv = debutListePoint;
	return p;
}

Chaine *creerChaine(int numero) {
	Chaine *c = (Chaine *) (malloc(sizeof(Chaine)));
	if (!c) {
		leverErreur("allocation mémoire Chaine");
		return NULL;
	}
	c->numero = numero;
	c->uneExtremite = NULL;
	c->chSuiv = NULL;
	return c;
}

Chaine *insererChaine(Chaine * debutListeChaine, Chaine * c) {
	Chaine *tmp = NULL;
	if (debutListeChaine == NULL) {
		return c;
	}
	tmp = debutListeChaine;
	while (tmp->chSuiv) {
		tmp = tmp->chSuiv;
	}
	tmp->chSuiv = c;
	return debutListeChaine;
}

ListeChaine *creerListeChaine() {
	ListeChaine *LC = (ListeChaine *) (malloc(sizeof(ListeChaine)));
	if (!LC) {
		leverErreur("allocation mémoire ListeChaine");
		return NULL;
	}
	LC->gamma = -1;
	LC->nbchaine = -1;
	LC->LCh = NULL;
	return LC;
}

void freeOnePoint(Point * p) {
	free(p);
}

void freeAllPoint(Point * debutListePoint) {
	Point *tmp = debutListePoint;
	Point *mem = NULL;
	while (tmp) {
		mem = tmp->ptSuiv;
		freeOnePoint(tmp);
		tmp = mem;
	}
}

void freeOneChaine(Chaine * c) {
	if (c) {
		freeAllPoint(c->uneExtremite);
	}
	free(c);
}

void freeAllChaine(Chaine * debutListeChaine) {
	Chaine *tmp = debutListeChaine;
	Chaine *mem = NULL;
	while (tmp) {
		mem = tmp->chSuiv;
		freeOneChaine(tmp);
		tmp = mem;
	}
}

void freeListeChaine(ListeChaine * LC) {
	if (LC) {
		freeAllChaine(LC->LCh);
	}
	free(LC);
}

void initListeChaineProperties(FILE * f, ListeChaine * L) {
	char buffer[BUFFER_SIZE];
	if (!readLine(f, buffer)) {
		leverErreur("lecture ligne du fichier");
		return;
	}
	L->nbchaine = scanNbChain(buffer);

	if (!readLine(f, buffer)) {
		leverErreur("lecture ligne du fichier");
		return;
	}
	L->gamma = scanGamma(buffer);
}

void lecture_chaine(FILE * f, ListeChaine * L) {
	char buffer[BUFFER_SIZE];
	char *subStringLeft = NULL;
	char *subStringRight = NULL;
	char *subStringTmp = NULL;
	Chaine *tmp = NULL;
	float x, y;
	/* lecture et initialisation des propriétés de la ListeChaine */
	initListeChaineProperties(f, L);

	/* lecture du séparateur */
	if (!readLine(f, buffer)) {
		leverErreur("lecture ligne du fichier");
		return;
	}

	/* lecture des Chaine */
	while (readLine(f, buffer)) {
		/* découpage en 2 parties à traiter */
		subStringLeft = strtok(buffer, ":");
		subStringRight = strtok(NULL, "\0");
		/* traiter partie gauche */
		tmp = creerChaine(scanNumero(subStringLeft));
		/* traiter partie droite */
		subStringTmp = strtok(subStringRight, "/");
		while (sscanf(subStringTmp, " %f %f ", &x, &y) == 2) {
			tmp->uneExtremite = insererPoint(tmp->uneExtremite,
					creerPoint(x, y));
			subStringTmp = strtok(NULL, "/");
		}
		L->LCh = insererChaine(L->LCh, tmp);
	}
}

void displayOnePoint(FILE * output, Point * p) {
	if (!p) {
		leverErreur("displayOnePoint");
		return;
	}
	fprintf(output, "%g %g", p->x, p->y);
}

void displayAllPoint(FILE * output, Point * debutListePoint) {
	Point *tmp = debutListePoint;
	if (!debutListePoint) {
		leverErreur("displayAllPoint");
		return;
	}
	while (tmp) {
		displayOnePoint(output, tmp);
		/* séparateur */
		fprintf(output, " / ");
		tmp = tmp->ptSuiv;
	}
}

void displayOneChaine(FILE * output, Chaine * c) {
	if (!c) {
		leverErreur("displayOneChaine");
		return;
	}
	fprintf(output, "h %d %d : ", c->numero, compterPoint(c->uneExtremite));
	displayAllPoint(output, c->uneExtremite);
}

void displayAllChaine(FILE * output, Chaine * debutListeChaine) {
	Chaine *tmp = debutListeChaine;
	if (!tmp) {
		leverErreur("displayAllChaine");
		return;
	}
	while (tmp) {
		displayOneChaine(output, tmp);
		fprintf(output, "\n");
		tmp = tmp->chSuiv;
	}
}

void displayListeChaine(FILE * output, ListeChaine * LC) {
	if (!LC) {
		leverErreur("displayListeChaine");
		return;
	}
	fprintf(output, "c NbChain: %d\n", LC->nbchaine);
	fprintf(output, "c Gamma: %d\n", LC->gamma);
	fprintf(output, "c\n");
	displayAllChaine(output, LC->LCh);
}

/* pour l'affichage */
int compterPoint(Point * debutListePoint) {
	int i = 0;
	Point *tmp = debutListePoint;
	while (tmp) {
		tmp = tmp->ptSuiv;
		i++;
	}
	return i;
}

/* alias vers displayListeChaine(FILE *output, ListeChaine *LC) */
void ecrit_chaine_txt(ListeChaine * L, FILE * f) {
	displayListeChaine(f, L);
}

double longueurChaine(Chaine * L) {
	Point *ptCourant = NULL;
	Point *ptPrecedent = NULL;
	double longueur = 0;
	if (!L) {
		leverErreur("longueurTotale");
		return -1;
	}
	ptCourant = L->uneExtremite;
	while (ptCourant) {
		if (ptPrecedent) {
			/* calcule longueur entre pointPrecedent et pointCourant */
			longueur += sqrt(
					pow((ptCourant->x - ptPrecedent->x), 2.0) + pow(
							(ptCourant->y - ptPrecedent->y), 2.0));
		}
		ptPrecedent = ptCourant;
		ptCourant = ptCourant->ptSuiv;
	}
	return longueur;
}

double longueurTotale(ListeChaine * L) {
	Chaine *courant = NULL;
	double longueur = 0;
	if (!L) {
		leverErreur("longueurTotale");
		return -1;
	}
	courant = L->LCh;
	while (courant) {
		longueur += longueurChaine(courant);
		courant = courant->chSuiv;
	}
	return longueur;
}

int compte_point(ListeChaine * L) {
	Chaine *courant = NULL;
	Point *ptCourant = NULL;
	double nbPoint = 0;
	if (!L) {
		leverErreur("longueurTotale");
		return -1;
	}
	courant = L->LCh;
	while (courant) {
		ptCourant = courant->uneExtremite;
		while (ptCourant) {
			nbPoint++;
			ptCourant = ptCourant->ptSuiv;
		}
		courant = courant->chSuiv;
	}
	return nbPoint;
}

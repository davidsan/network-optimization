#include "reseau.h"

Voisin *creerVoisin(int v)
{
    Voisin *new = NULL;
    if ((new = (Voisin *) (malloc(sizeof(Voisin)))) == NULL) {
	leverErreur("allocation mémoire creerVoisin");
	return NULL;
    }
    new->v = v;
    new->voisSuiv = NULL;
    return new;
}

Voisin *insererVoisin(Voisin * debutListeVoisin, Voisin * vois)
{
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

Noeud *creerNoeud(int u, double x, double y)
{
    Noeud *new = NULL;
    if ((new = (Noeud *) (malloc(sizeof(Noeud)))) == NULL) {
	leverErreur("allocation mémoire creerNoeud");
	return NULL;
    }
    new->u = u;
    new->x = x;
    new->y = y;
    new->LVoisins = NULL;
    return new;
}

CelluleLNoeud *creerCelluleLNoeud(Noeud * ptrnoeud)
{
    CelluleLNoeud *new = NULL;
    if ((new = (CelluleLNoeud *) (malloc(sizeof(CelluleLNoeud)))) == NULL) {
	leverErreur("allocation mémoire creerCelluleLNoeud");
	return NULL;
    }
    new->ptrnoeud = ptrnoeud;
    new->noeudSuiv = NULL;
    return new;
}

CelluleLNoeud *insererCelluleLNoeud(CelluleLNoeud * debutListeNoeuds,
				    CelluleLNoeud * node)
{
    CelluleLNoeud *tmp = NULL;
    if (debutListeNoeuds == NULL) {
	return node;
    }
    tmp = debutListeNoeuds;
    while (tmp->noeudSuiv) {
	tmp = tmp->noeudSuiv;
    }
    tmp->noeudSuiv = node;
    return debutListeNoeuds;
}

CelluleLCommodite *creerCelluleLCommodite(int extr1, int extr2)
{
    CelluleLCommodite *new = NULL;
    if ((new =
	 (CelluleLCommodite *) (malloc(sizeof(CelluleLCommodite)))) ==
	NULL) {
	leverErreur("allocation mémoire creerCelluleLCommodite");
	return NULL;
    }
    new->extr1 = extr1;
    new->extr2 = extr2;
    new->commSuiv = NULL;
    return new;
}

CelluleLCommodite *insererCelluleLCommidite(CelluleLCommodite *
					    debutListeCommodite,
					    CelluleLCommodite * commodite)
{
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

Reseau *creerReseau()
{
    Reseau *new = NULL;
    if ((new = (Reseau *) (malloc(sizeof(Reseau)))) == NULL) {
	leverErreur("allocation mémoire creerReseau");
	return NULL;
    }
    new->nbNoeuds = 0;
    new->gamma = 0;
    new->LCommodites = NULL;
    new->LNoeuds = NULL;
    return new;
}


void freeOneVoisin(Voisin * vois)
{
    free(vois);
}

void freeAllVoisin(Voisin * debutListeVoisin)
{
    Voisin *tmp = debutListeVoisin;
    Voisin *mem = NULL;
    while (tmp) {
	mem = tmp->voisSuiv;
	freeOneVoisin(tmp);
	tmp = mem;
    }
}

void freeNoeud(Noeud * node)
{
    freeAllVoisin(node->LVoisins);
    free(node);
}

void freeOneCelluleLNoeud(CelluleLNoeud * CLNode)
{
    freeNoeud(CLNode->ptrnoeud);
    free(CLNode);
}

void freeAllCelluleLNoeud(CelluleLNoeud * debutListeCLNode)
{
    CelluleLNoeud *tmp = debutListeCLNode;
    CelluleLNoeud *mem = NULL;
    while (tmp) {
	mem = tmp->noeudSuiv;
	freeOneCelluleLNoeud(tmp);
	tmp = mem;
    }
}

void freeOneCelulleLCommodite(CelluleLCommodite * CLCommodite)
{
    free(CLCommodite);
}

void freeAllCelulleLCommodite(CelluleLCommodite * debutListCLCommodite)
{
    CelluleLCommodite *tmp = debutListCLCommodite;
    CelluleLCommodite *mem = NULL;
    while (tmp) {
	mem = tmp->commSuiv;
	freeOneCelulleLCommodite(tmp);
	tmp = mem;
    }
}

void freeReseau(Reseau * R)
{
    freeAllCelulleLCommodite(R->LCommodites);
    freeAllCelluleLNoeud(R->LNoeuds);
    free(R);
}

void initReseauProperties(FILE * f, Reseau * R)
{
    char buffer[BUFFER_SIZE];
    if (!readLine(f, buffer)) {
	leverErreur("lecture ligne du fichier");
	return;
    }
    R->nbNoeuds = scanNbNodes(buffer);
    if (!readLine(f, buffer)) {
	leverErreur("lecture ligne du fichier");
	return;
    }
    // scanNbCables(buffer);
    if (!readLine(f, buffer)) {
	leverErreur("lecture ligne du fichier");
	return;
    }
    R->gamma = scanGamma(buffer);
}

Noeud *initNoeud(char *string)
{
    float x, y;
    int u;
    sscanf(string, "%d %f %f", &u, &x, &y);
    return creerNoeud(u, x, y);
}

CelluleLCommodite *initCommodite(char *string)
{
    int extr1, extr2;
    sscanf(string, "%d %d", &extr1, &extr2);
    return creerCelluleLCommodite(extr1, extr2);
}

int initVoisin(Reseau * R, char *string)
{
    int extr1, extr2;
    sscanf(string, "%d %d", &extr1, &extr2);
    /* chercher le noeud */
    Noeud *match = rechercheNoeud(R->LNoeuds, extr1);
    if (!match) {
	return 0;
    }
    match->LVoisins = insererVoisin(match->LVoisins, creerVoisin(extr2));
    return 1;
}

void lecture_fichier_reseau(FILE * f, Reseau * R)
{
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

	/* traiter partie gauche */
	switch (subStringLeft[0]) {
	case 'v':
	    R->LNoeuds =
		insererCelluleLNoeud(R->LNoeuds,
				     creerCelluleLNoeud(initNoeud
							(subStringRight)));
	    break;
	case 'a':
	    if (!initVoisin(R, subStringRight)) {
		leverErreur("initVoisin");
	    }
	    break;
	case 'k':
	    R->LCommodites =
		insererCelluleLCommidite(R->LCommodites,
					 initCommodite(subStringRight));
	    break;
	}
	/* traiter partie droite */
    }
}


void displayVoisinOneCelluleLNoeud(FILE * output, CelluleLNoeud * CLNode)
{
    int u = CLNode->ptrnoeud->u;
    Voisin *tmp = CLNode->ptrnoeud->LVoisins;
    while (tmp) {
	fprintf(output, "a %d %d\n", u, tmp->v);
	tmp = tmp->voisSuiv;
    }
}

void displayVoisinAllCelluleLNoeud(FILE * output,
				   CelluleLNoeud * debutListeCLNode)
{
    CelluleLNoeud *tmp = debutListeCLNode;
    while (tmp) {
	displayVoisinOneCelluleLNoeud(output, tmp);
	tmp = tmp->noeudSuiv;
    }
}

void displayNoeud(FILE * output, Noeud * node)
{
    fprintf(output, "v %d %g %g\n", node->u, node->x, node->y);
}

void displayOneCelluleLNoeud(FILE * output, CelluleLNoeud * CLNode)
{
    displayNoeud(output, CLNode->ptrnoeud);
}

void displayAllCelluleLNoeud(FILE * output,
			     CelluleLNoeud * debutListeCLNode)
{
    CelluleLNoeud *tmp = debutListeCLNode;
    while (tmp) {
	displayOneCelluleLNoeud(output, tmp);
	tmp = tmp->noeudSuiv;
    }
}

void displayOneCelluleLCommodite(FILE * output,
				 CelluleLCommodite * CLCommodite)
{
    fprintf(output, "k %d %d\n", CLCommodite->extr1, CLCommodite->extr2);
}

void displayAllCelluleLCommodite(FILE * output,
				 CelluleLCommodite * debutListeCLCommodite)
{
    CelluleLCommodite *tmp = debutListeCLCommodite;
    while (tmp) {
	displayOneCelluleLCommodite(output, tmp);
	tmp = tmp->commSuiv;
    }
}

void displayComment(FILE * output)
{
    fprintf(output, "c\n");
}

void displayReseau(FILE * output, Reseau * R)
{
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

Noeud *rechercheNoeud(CelluleLNoeud * debutListeNoeuds, int u)
{
    CelluleLNoeud *tmp = debutListeNoeuds;
    while (tmp) {
	if (tmp->ptrnoeud->u == u) {
	    return tmp->ptrnoeud;
	}
	tmp = tmp->noeudSuiv;
    }
    leverErreur("rechercheNoeud (noeud introuvable)");
    return NULL;
}

int compteCable(Reseau * R)
{
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
    return cpt;
}

void ecrit_reseau_disque(Reseau * R, FILE * f)
{
    displayReseau(f, R);
}

int recherche_voisin(Noeud * nd, int u);

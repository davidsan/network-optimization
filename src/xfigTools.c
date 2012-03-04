#include "xfigTools.h"

void ecrit_entete_xfig(FILE * f)
{
    fprintf(f, "#FIG 3.2\n");
    fprintf(f, "Landscape\n");
    fprintf(f, "Center\n");
    fprintf(f, "Metric\n");
    fprintf(f, "A4\n");
    fprintf(f, "100.00\n");
    fprintf(f, "Single\n");
    fprintf(f, "-2\n");
    fprintf(f, "1200 2\n");
}

void ecrit_chaine_xfig(ListeChaine * L, FILE * f, int zoom, int epaisseur)
{
    Chaine *chaineCourante = NULL;
    Point *pointCourant = NULL;
    Point *pointPrecedent = NULL;
    if (!L) {
	leverErreur("ecrit_chaine_xfig");
    }
    chaineCourante = L->LCh;
    int i = 0;
    while (chaineCourante != NULL) {
	/* afficher la chaine courante */
	pointCourant = chaineCourante->uneExtremite;
	pointPrecedent = NULL;
	while (pointCourant != NULL) {
	    /* tracer une ligne entre pointPrecedent et pointCourant */
	    if (pointPrecedent != NULL) {
		fprintf(f, "2 1 0 %d %d 7 50 0 -1 0.000 0 0 -1 0 0 2\n",
			epaisseur, i + 8);
		fprintf(f, "         %d %d %d %d\n",
			(int) (pointPrecedent->x * zoom),
			(int) (pointPrecedent->y * zoom),
			(int) (pointCourant->x * zoom),
			(int) (pointCourant->y * zoom));
	    }
	    /* afficher le point */
	    fprintf(f,
		    "1 4 0 %d 0 0 50 0 20 0.000 1 0.000 %d %d 25 25 0 0 0 0\n",
		    epaisseur, (int) (pointCourant->x * zoom),
		    (int) (pointCourant->y * zoom));
	    pointPrecedent = pointCourant;
	    pointCourant = pointCourant->ptSuiv;

	}
	i = (i + 1) % 4;
	chaineCourante = chaineCourante->chSuiv;
    }
}

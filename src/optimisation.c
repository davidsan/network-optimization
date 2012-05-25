/**
 * \file optimisation.c
 * \brief Source d'optimisation
 * \author david
 * \date 28 avr. 2012
 */

#include "optimisation.h"

void recree_liste_chaine(ListeChaine *L, Reseau *R) {
	CelluleLCommodite * tmp = R->LCommodites;
	L->gamma = R->gamma;
	L->nbchaine = 0;
	while (tmp) {
		Noeud ** previous = dijkstra(R, tmp->extr2, tmp->extr1);
		Chaine * ch = convertPrevious(R, previous, tmp->extr1);
		free(previous);

		L->LCh = insererChaine(L->LCh, ch);
		ch->numero = L->nbchaine;
		L->nbchaine++;
		tmp = tmp->commSuiv;
	}
}


void recree_liste_chaine_csp(ListeChaine *L, Reseau *R) {
	CelluleLCommodite * tmp = R->LCommodites;
	L->gamma = R->gamma;
	L->nbchaine = 0;
	while (tmp) {
		Noeud ** previous = dijkstra_csp(R, tmp->extr2, tmp->extr1);
		Chaine * ch = convertPrevious_csp(R, previous, tmp->extr1);
		free(previous);

		L->LCh = insererChaine(L->LCh, ch);
		ch->numero = L->nbchaine;
		L->nbchaine++;
		tmp = tmp->commSuiv;
	}
	if(getMaxGamma(R) > R->gamma){
		leverErreur("Gamma NOK. ");
	}
	else{
		fprintf(stderr, "Gamma OK.");
	}
}


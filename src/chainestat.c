/**
 * \file chainestat.c
 * \brief Programme de statistiques sur fichiers .cha
 * \author david
 * \date 28 avr. 2012
 */

#include <stdio.h>
#include "chaine.h"
#include "fichier.h"

int main(int argc, char **argv) {
	FILE *f = NULL;
	ListeChaine *L = NULL;

	int i;
	if (argc < 2) {
		leverErreur("Usage : ./chainestat *.cha");
		return 1;
	}
	for (i = 1; i < argc; i++) {
		f = ouvrirFichier(argv[i]);
		if (f == NULL) {
			continue;
		}
		L = creerListeChaine();
		lecture_chaine(f, L);
		fprintf(stdout, "%f\n", longueurTotale(L));

		fermerFichier(f);
		freeListeChaine(L);
	}
	return 0;
}

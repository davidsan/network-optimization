/**
 * \file convertchaine.c
 * \brief Programme de génération des fichiers ListeChaine à partir d'un réseau via Dijkstra
 * \author david
 * \date 28 avr. 2012
 */

#include <stdio.h>
#include <libgen.h>		/* basename function */
#include "chaine.h"
#include "fichier.h"
#include "optimisation.h"
#include "reseau.h"
#include "xfigTools.h"

int main(int argc, char **argv) {
	FILE *f = NULL;
	FILE *output = NULL;
	Reseau *R = NULL;
	ListeChaine *L = NULL;

	char *filename = NULL;
	int i;
	if (argc < 2) {
		leverErreur("Usage : ./convertchaine *.res");
		return 1;
	}
	for (i = 1; i < argc; i++) {
		f = ouvrirFichier(argv[i]);
		if (f == NULL) {
			continue;
		}
		L = creerListeChaine();
		R = creerReseau();
		lecture_fichier_reseau(f, R);

		recree_liste_chaine(L, R);

		filename = basename(argv[i]);
		fprintf(stderr, "Conversion en ListeChaine du fichier %s...\n",
				argv[i]);
		filename = strtok(filename, ".");
		filename = strcat(filename, ".cha");
		output = fopen(filename, "w");
		if (!output) {
			leverErreur("Erreur création fichier de sortie");
			freeReseau(R);
			freeListeChaine(L);
			fermerFichier(f);
			return 1;
		}
		ecrit_chaine_txt(L, output);
		fermerFichier(output);
		fermerFichier(f);
		freeReseau(R);
		freeListeChaine(L);
	}
	return 0;
}

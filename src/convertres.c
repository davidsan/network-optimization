/**
 * \file convertres.c
 * \brief Programme de génération des fichiers réseaux par l'utilisation d'une liste chaînée
 * \author David San
 *
 *
 */
#include <stdio.h>
#include <libgen.h>		/* basename function */
#include "build.h"
#include "chaine.h"
#include "fichier.h"
#include "reseau.h"
#include "xfigTools.h"

int main(int argc, char **argv)
{
    FILE *f = NULL;
    FILE *output = NULL;
    Reseau *R = NULL;
    ListeChaine *L = NULL;
    char *filename = NULL;
    int i;
    if (argc < 2) {
	leverErreur("Usage : ./convertres *.cha");
	return 1;
    }
    for (i = 1; i < argc; i++) {
	f = ouvrirFichier(argv[i]);
	if (f == NULL) {
	    continue;
	}
	R = creerReseau();
	L = creerListeChaine();
	lecture_chaine(f, L);
	recree_reseau(L, R);
	filename = basename(argv[i]);
	fprintf(stderr, "Conversion en réseau du fichier %s...\n",
		argv[i]);
	filename = strtok(filename, ".");
	filename = strcat(filename, ".res");
	output = fopen(filename, "w");
	if (!output) {
	    leverErreur("Erreur création fichier de sortie");
	    freeReseau(R);
	    freeListeChaine(L);
	    fermerFichier(f);
	    return 1;
	}
	ecrit_reseau_disque(R, output);
	fermerFichier(output);
	fermerFichier(f);
	freeReseau(R);
	freeListeChaine(L);
    }
    return 0;
}

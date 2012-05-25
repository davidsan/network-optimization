/**
 * \file convertxfig.c
 * \brief Programme de conversion Xfig
 * \author David San
 *
 * Programme de conversion automatique des fichiers .cha ou .res en .fig
 *
 */
#include <stdio.h>
#include <libgen.h>		/* basename function */
#include "chaine.h"
#include "fichier.h"
#include "reseau.h"
#include "xfigTools.h"
#define XFIG_ZOOM 1

int main(int argc, char **argv)
{
    FILE *f = NULL;
    FILE *output = NULL;
    Reseau *R = NULL;
    ListeChaine *L = NULL;
    char *filename = NULL;
    int i;
    int isCha;
    if (argc < 2) {
	leverErreur("Usage : ./convertxfig *.cha");
	return 1;
    }
    for (i = 1; i < argc; i++) {
	f = ouvrirFichier(argv[i]);
	isCha = (strstr(argv[i], ".cha") != NULL);
	if (f == NULL) {
	    return 1;
	}
	filename = basename(argv[i]);
	fprintf(stderr, "Création d'un dessin Xfig à partir de %s...\n",
		argv[i]);
	filename = strtok(filename, ".");
	filename = strcat(filename, ".fig");
	output = fopen(filename, "w");
	if (!output) {
	    leverErreur("Erreur création fichier de sortie");
	    freeReseau(R);
	    freeListeChaine(L);
	    fermerFichier(f);
	    return 1;
	}

	ecrit_entete_xfig(output);
	if (isCha) {
	    L = creerListeChaine();
	    lecture_chaine(f, L);
	    ecrit_chaine_xfig(L, output, XFIG_ZOOM, 1);
	    freeListeChaine(L);
	} else {
	    R = creerReseau();
	    lecture_fichier_reseau(f, R);
	    ecrit_reseau_xfig(R, output, XFIG_ZOOM, 1);
	    freeReseau(R);
	}
	fermerFichier(output);
	fermerFichier(f);

    }
    return 0;
}

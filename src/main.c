#include <stdio.h>
#include "fichier.h"
#include "chaine.h"
#include "xfigTools.h"

int main(int argc, char **argv)
{
    FILE *f = NULL;
    FILE *fig = NULL;
    fig = fopen("output.fig", "w");
    if (!fig) {
	return 1;
    }
    ListeChaine *L = creerListeChaine();

    if (L == NULL) {
	leverErreur("création d'une ListeChaine vide");
	return 1;
    }

    if (argc == 1) {		/* pas d'argument */
	f = ouvrirFichier("../res/00014_burma.cha");

    } else {
	f = ouvrirFichier(argv[1]);
    }
    if (!f) {
	fclose(fig);
	return 1;
    }

    lecture_chaine(f, L);
    /* displayListeChaine(stdout, L); */

    ecrit_entete_xfig(fig);
    ecrit_chaine_xfig(L, fig, 1000, 1);

    fermerFichier(f);
    fermerFichier(fig);
    freeListeChaine(L);

    return 0;
}

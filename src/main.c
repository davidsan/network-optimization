#include <stdio.h>
#include "fichier.h"
#include "chaine.h"

int main(int argc, char **argv)
{
    FILE *f = NULL;
    ListeChaine *L = creerListeChaine();

    if (L == NULL) {
	leverErreur("création d'une ListeChaine vide");
    }

    if (argc == 1) {		/* pas d'argument */
	f = ouvrirFichier("../res/00014_burma.cha");
    } else {
	f = ouvrirFichier(argv[1]);
    }

    lecture_chaine(f, L);
    displayListeChaine(stdout, L);

    fermerFichier(f);
    freeListeChaine(L);

    return 0;
}

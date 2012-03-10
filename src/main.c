#include <stdio.h>
#include "fichier.h"
#include "chaine.h"
#include "xfigTools.h"
#include "reseau.h"
#include "menu.h"

int main(int argc, char **argv)
{
    FILE *f = NULL;
    Reseau *R = creerReseau();
    ListeChaine *L = creerListeChaine();

    int choix = -1;
    while (choix != 0) {
	showMenu();
	choix = readNombre();
	callChoix(&f, choix, &R, &L);
    }
    fermerFichier(f);
    freeReseau(R);
    freeListeChaine(L);
    return 0;
}

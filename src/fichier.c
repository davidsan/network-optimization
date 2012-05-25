/**
 * \file fichier.c
 * \brief Source de fichier
 * \author David San
 */
#include "fichier.h"

FILE *ouvrirFichier(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
	fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n",
		filename);
	return NULL;
    }
    return f;
}

void fermerFichier(FILE * f)
{
    fclose(f);
}

int readLine(FILE * f, char *buffer)
{
    return (fgets(buffer, BUFFER_SIZE, f) != NULL);
}

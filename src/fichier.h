#ifndef __FICHIER_H__
#define __FICHIER_H__

#include <stdio.h>
#include "erreur.h"

/* findLongestLines.sh (4434 ../res/07397_pla.cha) */
#define BUFFER_SIZE 4480

FILE *ouvrirFichier(char *filename);
void fermerFichier(FILE * f);
int readLine(FILE * f, char *buffer);

#endif

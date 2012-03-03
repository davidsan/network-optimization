#ifndef __FICHIER_H__
#define __FICHIER_H__
#include <stdio.h>
#include "erreur.h"

FILE *ouvrirFichier(char *filename);
void fermerFichier(FILE *f);
#endif

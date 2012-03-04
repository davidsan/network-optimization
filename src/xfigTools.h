#ifndef __XFIGTOOLS_H__
#define __XFIGTOOLS_H__
#include <stdio.h>
#include "chaine.h"
#include "erreur.h"
void ecrit_entete_xfig(FILE * f);
void ecrit_chaine_xfig(ListeChaine * L, FILE * f, int zoom, int epaisseur);

#endif

#ifndef MENU_H
#define MENU_H

#include "fichier.h"
#include "erreur.h"
#include "reseau.h"
#include "chaine.h"
#include "xfigTools.h"

void showMenu();
int readNombre();
void readString(char **s);
void callChoix(FILE ** f, int choix, Reseau ** R, ListeChaine ** L);

#endif

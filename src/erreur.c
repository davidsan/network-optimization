/**
 * \file erreur.c
 * \brief Source d'erreur
 * \author David San
 */
#include "erreur.h"

void leverErreur(char *message)
{
    fprintf(stderr, "Erreur : %s\n", message);
}

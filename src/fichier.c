#include "fichier.h"

FILE *ouvrirFichier(char *filename){
  FILE *f = fopen(filename, "r");
  if (!f){
    leverErreur("ouverture de fichier");
  }
  return f;
}

void fermerFichier(FILE *f){
  fclose(f);
}


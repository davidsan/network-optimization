#include "erreur.h"

void leverErreur(char *message){
  fprintf(stderr, "Erreur : %s\n", message);
}

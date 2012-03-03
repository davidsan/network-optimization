#include "chaine.h"

Point *creerPoint(double x, double y){
  Point *p=(Point*)(malloc(sizeof(Point)));
  if(!p){
    leverErreur("allocation mémoire Point");
    return NULL;
  }
  p->x=x;
  p->y=y;
  p->ptSuiv=NULL;
  return p;
}

/* insertion en fin de liste */
/* renvoie le Point du début de liste */
Point *insererPoint(Point *debutListePoint, Point *p){ 
  Point *tmp = NULL;
  if(debutListePoint==NULL){
    return p;
  }
  tmp=debutListePoint;
  while(tmp->ptSuiv){
    tmp=tmp->ptSuiv;
  }
  tmp->ptSuiv=p;
  return debutListePoint;
}

Chaine *creerChaine(int numero, Point *uneExtremite){
  Chaine *c=(Chaine *)(malloc(sizeof(Chaine)));
  if(!c){
    leverErreur("allocation mémoire Chaine");
    return NULL;
  }
  c->numero=numero;
  c->uneExtremite=uneExtremite;
  c->chSuiv=NULL;
  return c;
}

Chaine *insererChaine(Chaine *debutListeChaine, Chaine *c){
  Chaine *tmp = NULL;
  if(debutListeChaine==NULL){
    return c;
  }
  tmp=debutListeChaine;
  while(tmp->chSuiv){
    tmp=tmp->chSuiv;
  }
  tmp->chSuiv=c;
  return debutListeChaine;
}

ListeChaine *creerListeChaine(int gamma, int nbchaine, Chaine *LCh){
  ListeChaine *LC=(ListeChaine *)(malloc(sizeof(ListeChaine)));
  if(!LC){
    leverErreur("allocation mémoire ListeChaine");
    return NULL;
  }
  LC->gamma=gamma;
  LC->nbchaine=nbchaine;
  LC->LCh=LCh;
  return LC;
}

void freeOnePoint(Point *p){
  free(p);
}

void freeAllPoint(Point *debutListePoint){
  Point *tmp=debutListePoint;
  Point *mem=NULL;
  while(tmp){
    mem=tmp->ptSuiv;
    freeOnePoint(tmp);
    tmp=mem;
  }
}

void freeOneChaine(Chaine *c){
  if(c){
    freeAllPoint(c->uneExtremite);
  }
  free(c);
}

void freeAllChaine(Chaine *debutListeChaine){
  Chaine *tmp=debutListeChaine;
  Chaine *mem=NULL;
  while(tmp){
    mem=tmp->chSuiv;
    freeOneChaine(tmp);
    tmp=mem;
  }
}

void freeListeChaine(ListeChaine *LC){
  if(LC){
    freeAllChaine(LC->LCh);
  }
  free(LC);
}

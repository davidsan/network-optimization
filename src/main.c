/**
* @mainpage Projet Réseau
* @section intro_sec Introduction
* Une agglomération désire améliorer le réseau de fibres optiques de ses administrés.
*
* Une première phase de travail va consister à reconstituer le plan du réseau. En effet, plusieurs
opérateurs se partagent actuellement ce marché en possédant chacun quelques fibres des câbles du
réseau. Le réseau ayant grossi régulièrement, il n'existe pas à ce jour de plan complet de ce réseau.
En revanche, chaque opérateur connaît les tronçons de fibres optiques qu'il utilise dans le réseau. En
partant de l'hypothèse qu'il y a au moins une fibre utilisée par câble, il est ainsi possible de reconstituer
le réseau dans son intégralité.
*
* Une deuxième phase de travail va consister à réorganiser les attributions de fibres de chacun des
opérateurs. En effet, la répartition des fibres n'a jamais été remise en cause jusqu'ici : certains câbles
sont sous-exploités au détriment d'autres sur-exploités. En fait, chaque opérateur possède une liste de
paires de clients qu'il a relié l'un à l'autre par une chaîne de tronçons de fibres optiques. Comme les attributions de
fibres optiques n'ont jamais été remises en cause, certaines chaînes sont très longues à
cause de cette congestion. Ces problèmes de congestion et de longueurs excessives peuvent être résolus,
ou tout du moins améliorés, en attribuant aux opérateurs des chaînes moins longues et mieux réparties
dans le réseau.
*
* @section install_sec Installation
*
* $ make
*
* @subsection running Exécution
*
* - $ ./main
* - $ ./convertres
* - $ ./converthash
* - $ ./convertabr
* - $ ./convertxfig
* - $ ./converttimer
*
* @section author Auteur
* David San
*/

/**
 * \file main.c
 * \brief Programme de test avec menu
 * \author David San
 *
 *
 */

#include <stdio.h>
#include "chaine.h"
#include "fichier.h"
#include "menu.h"
#include "reseau.h"
#include "xfigTools.h"

int main(int argc, char **argv)
{
    FILE *f = NULL;
    Reseau *R = creerReseau();
    ListeChaine *L = creerListeChaine();

    if (argc == 2) {
	fprintf(stdout, "Ouverture du fichier %s\n", argv[1]);
	f = ouvrirFichier(argv[1]);
    }

    int choix = -1;
    while (choix != 0) {
	showMenu();
	choix = readNombre();
	callChoix(&f, choix, &R, &L);
    }
    printf("Fermeture en cours\n");
    if (f) {
	fermerFichier(f);
    }

    freeReseau(R);
    freeListeChaine(L);
    return 0;
}

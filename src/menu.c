/**
 * \file menu.c
 * \brief Source de menu
 * \author David San
 */
#include "menu.h"

void showMenu()
{
    printf("****************************************************\n");
    printf("*                       Menu                       *\n");
    printf("****************************************************\n");
    printf("1. Ouvrir un fichier (.res ou .cha)\n");
    printf("2. Lecture fichier chaine\n");
    printf("3. Affiche la liste de chaînes\n");
    printf("4. Générer le dessin xfig de la liste de chaînes\n");
    printf("5. Lecture fichier réseau\n");
    printf("6. Affiche le réseau\n");
    printf("7. Générer le dessin xfig du fichier réseau\n");
    printf
	("8. Conversion ListeChaine -> Réseau (via liste chainée triée)\n");
    printf
	("9. Conversion ListeChaine -> Réseau (via table de hachage)\n");
    printf("10. Conversion ListeChaine -> Réseau (via arbre AVL)\n");
    printf("0. Quitter\n");
    printf("\n");
    printf("Votre choix : ");
}

int readNombre()
{
    char buffer[BUFFER_SIZE];
    scanf(" %[^\n]s", buffer);
    printf("\n");
    return atoi(buffer);
}

void readString(char **s)
{
    char buffer[BUFFER_SIZE];
    scanf(" %[^\n]s", buffer);
    printf("\n");
    if ((*s = strdup(buffer)) == NULL) {
	leverErreur("Erreur lecture nom");
	return;
    }
}

void callChoix(FILE ** f, int choix, Reseau ** R, ListeChaine ** L)
{
    FILE *output = NULL;
    char *stringInput = NULL;

    switch (choix) {
    case 1:
	system("ls --format single-column ../res/*.cha ../res/*.res ");
	printf("Entrez le nom du fichier à ouvrir : ");
	readString(&stringInput);
	if (*f != NULL) {
	    printf("Fermeture du fichier ouvert\n");
	    fermerFichier(*f);
	}
	printf("Ouverture du fichier %s... ", stringInput);
	*f = ouvrirFichier(stringInput);
	break;
    case 2:
	if (!*f) {
	    printf("Aucun fichier ouvert\n");
	    return;
	}
	if ((*L)->LCh) {
	    printf("Liste de chaînes déjà lue\n");
	    return;
	}
	printf("Lecture de la liste de chaînes...\n");
	lecture_chaine(*f, *L);
	break;
    case 3:
	if (!(*L)->LCh) {
	    leverErreur("Liste non initialisée");
	    return;
	}
	printf("Entrez le nom du fichier de sortie\n");
	readString(&stringInput);
	output = fopen(stringInput, "w");
	if (output == NULL) {
	    leverErreur("Erreur création fichier de sortie");
	    return;
	}
	ecrit_chaine_txt(*L, output);
	printf("Nombre d'occurences de points total : %d\n",
	       compte_point(*L));
	printf("Longueur totale : %g\n", longueurTotale(*L));
	fermerFichier(output);
	break;
    case 4:
	if (!L) {
	    leverErreur("Liste non initialisée");
	    break;
	}
	printf("Entrez le nom du fichier de sortie\n");
	readString(&stringInput);
	output = fopen(stringInput, "w");
	if (output == NULL) {
	    leverErreur("Erreur création fichier de sortie");
	    return;
	}
	ecrit_entete_xfig(output);
	ecrit_chaine_xfig(*L, output, 200, 1);
	fermerFichier(output);
	break;
    case 5:
	if ((*R)->LNoeuds) {
	    printf("Réseau déjà lu\n");
	    return;
	}
	printf("Lecture du réseau...\n");
	lecture_fichier_reseau(*f, *R);
	break;
    case 6:
	if (!(*R)->LNoeuds) {
	    leverErreur("Réseau non initialisé");
	    return;
	}
	printf("Entrez le nom du fichier de sortie\n");
	readString(&stringInput);
	output = fopen(stringInput, "w");
	if (output == NULL) {
	    leverErreur("Erreur création fichier de sortie");
	    return;
	}
	ecrit_reseau_disque(*R, output);
	fermerFichier(output);
	break;
    case 7:
	if (!(*R)->LNoeuds) {
	    leverErreur("Réseau non initialisé");
	    return;
	}
	printf("Entrez le nom du fichier de sortie\n");
	readString(&stringInput);
	output = fopen(stringInput, "w");
	if (output == NULL) {
	    leverErreur("Erreur création fichier de sortie");
	    return;
	}
	ecrit_entete_xfig(output);
	ecrit_reseau_xfig(*R, output, 200, 1);
	fermerFichier(output);
	break;
    case 8:
	if (!(*L)->LCh) {
	    leverErreur("Liste de chaînes non initialisée");
	    return;
	}
	if ((*R)->LNoeuds) {
	    fprintf(stdout, "Destruction du réseau existant.\n");
	    freeReseau(*R);
	    fprintf(stdout, "Création d'un nouveau réseau vide.\n");
	    *R = creerReseau();
	}
	recree_reseau(*L, *R);
	fprintf(stdout,
		"Création d'un réseau à partir de la ListeChaine terminé.\n");

	break;
    case 9:
	if (!(*L)->LCh) {
	    leverErreur("Liste de chaînes non initialisée");
	    return;
	}
	if ((*R)->LNoeuds) {
	    fprintf(stdout, "Destruction du réseau existant.\n");
	    freeReseau(*R);
	    fprintf(stdout, "Création d'un nouveau réseau vide.\n");
	    *R = creerReseau();
	}
	Hachage *H = creerHachage(500);
	recree_reseau_hachage(*L, *R, H);
	fprintf(stdout,
		"Création d'un réseau à partir de la ListeChaine terminé.\n");
	freeHachage(H);
	break;
    case 10:
	if (!(*L)->LCh) {
	    leverErreur("Liste de chaînes non initialisée");
	    return;
	}
	if ((*R)->LNoeuds) {
	    fprintf(stdout, "Destruction du réseau existant.\n");
	    freeReseau(*R);
	    fprintf(stdout, "Création d'un nouveau réseau vide.\n");
	    *R = creerReseau();
	}
	recree_reseau_AVL(*L, *R);
	fprintf(stdout,
		"Création d'un réseau à partir de la ListeChaine terminé.\n");
	break;
    case 0:
	break;
    default:
	printf("Erreur : choix non reconnu\n");
	break;
    }
    free(stringInput);
}

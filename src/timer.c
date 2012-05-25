/**
 * \file timer.c
 * \brief Source des timers
 * \author David San
 */
#include "timer.h"

void timeAll(char *filename)
{
    clock_t temps_initial;	/* Temps initial en micro-secondes */
    clock_t temps_final;	/* Temps final en micro-secondes */
    float temps_cpu;		/* Temps total en secondes */
    Reseau *R = NULL;
    ListeChaine *L = NULL;
    Hachage *H = NULL;
    FILE *f = ouvrirFichier(filename);
    if (f == NULL) {
	leverErreur("ouverture de fichier");
	return;
    }

    /* LC */
    temps_initial = clock();
    R = creerReseau();
    L = creerListeChaine();
    lecture_chaine(f, L);
    recree_reseau(L, R);

    /* affichage nombre de points */
    fprintf(stdout, "%d ", R->nbNoeuds);

    freeReseau(R);
    freeListeChaine(L);

    /* affichage time */
    temps_final = clock();
    temps_cpu = (temps_final - temps_initial) * 1e-6;
    fprintf(stdout, "%f ", temps_cpu);

    /* déplace le curseur au début */
    rewind(f);

    /* Hash */
    temps_initial = clock();
    R = creerReseau();
    L = creerListeChaine();
    H = creerHachage(500);
    lecture_chaine(f, L);
    recree_reseau_hachage(L, R, H);

    /* affichage time */
    temps_final = clock();
    temps_cpu = (temps_final - temps_initial) * 1e-6;
    fprintf(stdout, "%f ", temps_cpu);

    freeHachage(H);
    freeReseau(R);
    freeListeChaine(L);

    /* déplace le curseur au début */
    rewind(f);

    /* AVL */
    temps_initial = clock();
    R = creerReseau();
    L = creerListeChaine();
    lecture_chaine(f, L);
    recree_reseau_AVL(L, R);

    /* affichage time */
    temps_final = clock();
    temps_cpu = (temps_final - temps_initial) * 1e-6;
    fprintf(stdout, "%f\n", temps_cpu);

    freeReseau(R);
    freeListeChaine(L);
    fermerFichier(f);
}

void timeLC(char *filename)
{
    clock_t temps_initial;	/* Temps initial en micro-secondes */
    clock_t temps_final;	/* Temps final en micro-secondes */
    float temps_cpu;		/* Temps total en secondes */
    temps_initial = clock();

    /* action */
    Reseau *R = creerReseau();
    ListeChaine *L = creerListeChaine();
    FILE *f = ouvrirFichier(filename);
    FILE *output = NULL;
    char *outputName = NULL;
    if (f == NULL) {
	freeReseau(R);
	freeListeChaine(L);
	leverErreur("ouverture de fichier");
	return;
    }
    lecture_chaine(f, L);
    recree_reseau(L, R);
    outputName = strtok(filename, ".");
    outputName = strtok(outputName, "/");
    outputName = strtok(NULL, "/");
    outputName = strcat(outputName, ".res");
    output = fopen(outputName, "w");
    if (!output) {
	leverErreur("Erreur création fichier de sortie");
	freeReseau(R);
	freeListeChaine(L);
	fermerFichier(f);
	return;
    }
    ecrit_reseau_disque(R, output);
    fermerFichier(output);
    fermerFichier(f);
    freeReseau(R);
    freeListeChaine(L);
    /* fin action */

    temps_final = clock();
    temps_cpu = (temps_final - temps_initial) * 1e-6;
    fprintf(stderr, "%f ", temps_cpu);
}

void timeHash(char *filename)
{
    clock_t temps_initial;	/* Temps initial en micro-secondes */
    clock_t temps_final;	/* Temps final en micro-secondes */
    float temps_cpu;		/* Temps total en secondes */
    temps_initial = clock();

    /* action */
    Reseau *R = creerReseau();
    ListeChaine *L = creerListeChaine();
    Hachage *H = creerHachage(500);
    FILE *f = ouvrirFichier(filename);
    FILE *output = NULL;
    char *outputName = NULL;

    if (f == NULL) {
	freeHachage(H);
	freeReseau(R);
	freeListeChaine(L);
	leverErreur("ouverture de fichier");
	return;
    }
    lecture_chaine(f, L);
    recree_reseau_hachage(L, R, H);
    outputName = strtok(filename, ".");
    outputName = strtok(outputName, "/");
    outputName = strtok(NULL, "/");
    outputName = strcat(outputName, ".res");
    output = fopen(outputName, "w");
    if (!output) {
	leverErreur("création de fichier de sortie");
	freeHachage(H);
	freeReseau(R);
	freeListeChaine(L);
	fermerFichier(f);
	return;
    }
    ecrit_reseau_disque(R, output);
    fermerFichier(output);
    fermerFichier(f);
    freeHachage(H);
    freeReseau(R);
    freeListeChaine(L);
    /* fin action */

    temps_final = clock();
    temps_cpu = (temps_final - temps_initial) * 1e-6;
    fprintf(stderr, "%f ", temps_cpu);
}

void timeAVL(char *filename)
{
    clock_t temps_initial;	/* Temps initial en micro-secondes */
    clock_t temps_final;	/* Temps final en micro-secondes */
    float temps_cpu;		/* Temps total en secondes */
    temps_initial = clock();

    /* action */
    Reseau *R = creerReseau();
    ListeChaine *L = creerListeChaine();
    FILE *f = ouvrirFichier(filename);
    FILE *output = NULL;
    char *outputName = NULL;
    if (f == NULL) {
	freeReseau(R);
	freeListeChaine(L);
	leverErreur("ouverture de fichier");
	return;
    }
    lecture_chaine(f, L);
    recree_reseau_AVL(L, R);
    outputName = strtok(filename, ".");
    outputName = strtok(outputName, "/");
    outputName = strtok(NULL, "/");
    outputName = strcat(outputName, ".res");
    output = fopen(outputName, "w");
    if (!output) {
	leverErreur("création de fichier de sortie");
	freeReseau(R);
	freeListeChaine(L);
	fermerFichier(f);
	return;
    }
    ecrit_reseau_disque(R, output);
    fermerFichier(output);
    fermerFichier(f);
    freeReseau(R);
    freeListeChaine(L);
    /* fin action */

    temps_final = clock();
    temps_cpu = (temps_final - temps_initial) * 1e-6;
    fprintf(stderr, "%f ", temps_cpu);
}

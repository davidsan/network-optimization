/**
 * \file converttimer.c
 * \brief Programme de génération des temps de performances
 * \author David San
 *
 *
 */
#include <stdio.h>
#include "timer.h"

int main(int argc, char **argv)
{

    int i;
    if (argc < 2) {
	leverErreur("Usage : ./converttimer *.cha");
	return 1;
    }

    for (i = 1; i < argc; i++) {
	/* executer la conversion via liste chaînée triée */
	timeAll(argv[i]);
    }
    return 0;
}

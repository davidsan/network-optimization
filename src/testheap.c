/**
 * \file testheap.c
 * \brief Programme de test du tas
 * \author David San
 *
 * Programme de test pour valider le tas
 *
 */

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>

int main() {
	int i;
	srand(time(NULL));
	Heap * h = createHeap(100);
	for (i = 0; i < 100; ++i) {
		if (i > 20) {
			heapAdd(h, createHeapNode(FLT_MAX, i));
			continue;
		}
		heapAdd(h, createHeapNode(rand() % 100, i));
	}

	displayHeap(h);
	for (i = 0; i < 10; ++i) {
		HeapNode *tmp = heapExtractHead(h);

		fprintf(stdout, "\nAncien noeud : ");
		displayHeapNode(tmp);
		fprintf(stdout, "\n");
		tmp->c = rand() * i % 100 + 100;
		fprintf(stdout, "Nouveau noeud : ");
		displayHeapNode(tmp);

		heapAdd(h, tmp);

		displayHeap(h);
	}

	HeapNode * tmp = heapExtract(h, 2);
	tmp->c = rand() % 100;

	heapAdd(h, tmp);

	displayHeap(h);

	freeHeap(h);

	return 0;
}

/**
 * \file heap.c
 * \brief Source de tas
 * \author David San
 */
#include "heap.h"

HeapNode *createHeapNode(double c, int i) {
	HeapNode *new = (HeapNode *) (malloc(sizeof(HeapNode)));
	if (!new) {
		leverErreur("allocation mémoire\n");
		return NULL;
	}
	new->c = c;
	new->i = i;
	return new;
}

void freeHeapNode(HeapNode * n) {
	free(n);
}

Heap *createHeap(int size) {
	int i;
	Heap *new = (Heap *) (malloc(sizeof(Heap)));
	if (!new) {
		leverErreur("allocation mémoire\n");
		return NULL;
	}
	new->count = 0;
	new->size = size;
	new->tab = (HeapNode **) (malloc(sizeof(HeapNode *) * size));
	if (!new->tab) {
		leverErreur("allocation mémoire\n");
		freeHeap(new);
		return NULL;
	}
	for (i = 0; i < size; ++i) {
		new->tab[i] = NULL;
	}
	return new;
}

void freeHeap(Heap * h) {
	int i;
	if (h) {
		for (i = 0; i < h->size; ++i) {
			freeHeapNode(h->tab[i]);
		}
		free(h->tab);
		free(h);
	}
}

int isPowerOfTwo(unsigned int x) {
	while (((x % 2) == 0) && x > 1)
		x /= 2;
	return (x == 1);
}

void displayHeap(Heap * h) {
	int i;
	fprintf(stdout, "===== Heap :: %d of %d used =====\n", h->count, h->size);
	for (i = 0; i < h->size; ++i) {
		if (isPowerOfTwo(i + 1)) {
			printf("\n");
		}
		displayHeapNode(h->tab[i]);
	}
	fprintf(stdout, "\n");
}

void displayHeapDijkstra(Heap * h) {
	int i;
	fprintf(stdout, "===== Heap :: %d of %d used =====\n", h->count, h->size);
	for (i = 0; i < h->size; ++i) {
		if (isPowerOfTwo(i + 1)) {
			printf("\n");
		}
		if (!h->tab[i]) {
			fprintf(stdout, "_ ");
		} else {
			fprintf(stdout, "%d ", h->tab[i]->i);
		}
	}
	fprintf(stdout, "\n");
}

void displayHeapNode(HeapNode * n) {
	if (!n) {
		fprintf(stdout, "[ ] ");
	} else {
		if (n->c >= FLT_MAX) {
			fprintf(stdout, "[] ");
		} else {
			fprintf(stdout, "[%g] ", n->c);
		}
	}
}

int getLeftChild(int node) {
	return 2 * node + 1;
}

int getRightChild(int node) {
	return 2 * node + 2;
}

int getParent(int node) {
	return floor((node - 1) / 2);
}

HeapNode *getMinimum(Heap * h) {
	if (!h) {
		leverErreur("heap not init");
		return NULL;
	}
	return h->tab[0];
}

void heapAddEnd(Heap * h, HeapNode * n) {
	if (!h) {
		leverErreur("heap not init");
		return;
	}
	if (h->count >= h->size) {
		leverErreur("heap out of capacity");
		return;
	}
	h->tab[h->count] = n;
	h->count++;
}

void heapSwap(Heap * h, int i, int j) {
	if (!h) {
		leverErreur("heap not init");
		return;
	}
	HeapNode *tmp = h->tab[i];
	h->tab[i] = h->tab[j];
	h->tab[j] = tmp;
}

void heapHeapifyUp(Heap * h, int i) {
	if (!h) {
		leverErreur("heap not init");
		return;
	}
	if (i != 0) {
		if (h->tab[i] == NULL) {
			return;
		}
		int parent = getParent(i);
		if (h->tab[parent]->c > h->tab[i]->c) {
			heapSwap(h, parent, i);
			heapHeapifyUp(h, parent);
		}

	}
}

void heapHeapifyDown(Heap * h, int i) {
	if (!h) {
		leverErreur("heap not init");
		return;
	}
	int left = getLeftChild(i);
	int right = getRightChild(i);
	int lowest = i;

	if (left < h->count && h->tab[left]->c < h->tab[lowest]->c) {
		lowest = left;
	}

	if (right < h->count && h->tab[right]->c < h->tab[lowest]->c) {
		lowest = right;
	}

	if (lowest != i) {
		heapSwap(h, lowest, i);
		heapHeapifyDown(h, lowest);
	}

	return;
}

void heapAdd(Heap * h, HeapNode * n) {
	heapAddEnd(h, n);
	heapHeapifyUp(h, h->count - 1);
}

int heapNodeNumberExists(Heap * h, int n) {
	int i;
	for (i = 0; i < h->size; ++i) {
		if (h->tab[i]->i == n) {
			return 1;
		}
	}
	return 0;
}

int heapNodeExists(Heap * h, int n) {
	if (!h) {
		leverErreur("heap not init");
		return 0;
	}
	return (h->tab[n] != NULL);
}

HeapNode *heapExtractHead(Heap * h) {
	if (!h) {
		leverErreur("heap not init");
		return NULL;
	}
	if (h->count == 0) {
		leverErreur("heap is empty");
		return NULL;
	}
	HeapNode *head = h->tab[0];
	h->tab[0] = NULL;
	heapSwap(h, 0, h->count - 1);
	h->count--;
	heapHeapifyDown(h, 0);
	return head;
}

HeapNode *heapExtract(Heap * h, int i) {
	if (!h) {
		leverErreur("heap not init");
		return NULL;
	}
	if (h->count == 0) {
		leverErreur("heap is empty");
		return NULL;
	}
	int index = heapFindIndex(h, i);
	HeapNode *head = h->tab[index];
	h->tab[index] = NULL;
	heapSwap(h, index, h->count - 1);
	h->count--;
	heapHeapifyDown(h, index);
	/* patch friday */
	heapHeapifyUp(h, index);

	return head;
}

int heapIsEmpty(Heap * h) {
	return (h->count == 0);
}

int heapFindIndex(Heap * h, int i) {
	int j;
	for (j = 0; j < h->count; ++j) {
		if (h->tab[j]->i == i) {
			return j;
		}
	}
	return -1;
}

int heapContains(Heap * h, int i) {
	int j;
	for (j = 0; j < h->count; j++) {
		if (h->tab[j]->i == i) {
			return 1;
		}
	}
	return 0;
}


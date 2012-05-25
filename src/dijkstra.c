/**
 * \file dijkstra.c
 * \brief Source de Dijkstra
 * \author david
 * \date 28 avr. 2012
 */

#include "dijkstra.h"

Noeud ** dijkstra(Reseau *R, int src, int target) {
	/* initialisation */
	float dist[R->nbNoeuds];
	Noeud ** previous = (Noeud **) (malloc(sizeof(Noeud*) * R->nbNoeuds));
	Heap * h = createHeap(R->nbNoeuds);

	int i = 0;
	for (i = 0; i < R->nbNoeuds; i++) {
		dist[i] = FLT_MAX;
		previous[i] = NULL;
	}
	dist[src] = 0;
	for (i = 0; i < R->nbNoeuds; i++) {
		heapAdd(h, createHeapNode(dist[i], i));
	}
	while (!heapIsEmpty(h)) {
		HeapNode * head = h->tab[0];
		int u = head->i;

		if (dist[u] == FLT_MAX) {
			break;
		}

		head = heapExtractHead(h);
		if (u == target) {
			freeHeapNode(head);
			freeHeap(h);
			return previous;
		}
		Noeud * currentNode = rechercheNoeud(R->LNoeuds, u);
		if (currentNode == NULL) {
			leverErreur("Noeud manquant");
			return NULL;
		}

		Voisin * tmpVoisin = currentNode->LVoisins;

		while (tmpVoisin) {
			if (!heapContains(h, tmpVoisin->v)) {
				tmpVoisin = tmpVoisin->voisSuiv;
				continue;
			}
			Noeud * neighbor = rechercheNoeud(R->LNoeuds, tmpVoisin->v);
			float longueur = sqrt(
					pow((currentNode->x - neighbor->x), 2.0)
							+ pow((currentNode->y - neighbor->y), 2.0));
			float alt = dist[currentNode->u] + longueur;

			if (alt < dist[neighbor->u]) {
				dist[neighbor->u] = alt;
				previous[neighbor->u] = currentNode;
				HeapNode * tmp = heapExtract(h, neighbor->u);
				tmp->c = dist[neighbor->u];
				heapAdd(h, tmp);
			}

			tmpVoisin = tmpVoisin->voisSuiv;
		}
		freeHeapNode(head);
	}
	freeHeap(h);
	return previous;
}

Chaine * convertPrevious(Reseau *R, Noeud ** previous, int target) {
	Chaine * ch = creerChaine(-1);
	Noeud * tmp = rechercheNoeud(R->LNoeuds, target);
	ch->chSuiv = NULL;
	ch->uneExtremite = insererPointDebut(ch->uneExtremite,
			creerPoint(tmp->x, tmp->y));
	tmp = previous[target];
	while (tmp) {
		ch->uneExtremite = insererPointDebut(ch->uneExtremite,
				creerPoint(tmp->x, tmp->y));
		tmp = previous[tmp->u];
	}
	return ch;
}

Noeud ** dijkstra_csp(Reseau *R, int src, int target) {
	/* initialisation */
	float dist[R->nbNoeuds];
	Noeud ** previous = (Noeud **) (malloc(sizeof(Noeud*) * R->nbNoeuds));
	Heap * h = createHeap(R->nbNoeuds);

	int i = 0;
	for (i = 0; i < R->nbNoeuds; i++) {
		dist[i] = FLT_MAX;
		previous[i] = NULL;
	}
	dist[src] = 0;
	for (i = 0; i < R->nbNoeuds; i++) {
		heapAdd(h, createHeapNode(dist[i], i));
	}
	while (!heapIsEmpty(h)) {
		HeapNode * head = h->tab[0];
		int u = head->i;

		if (dist[u] == FLT_MAX) {
			break;
		}

		head = heapExtractHead(h);
		if (u == target) {
			freeHeapNode(head);
			freeHeap(h);
			return previous;
		}
		Noeud * currentNode = rechercheNoeud(R->LNoeuds, u);
		if (currentNode == NULL) {
			leverErreur("Noeud manquant");
			return NULL;
		}

		Voisin * tmpVoisin = currentNode->LVoisins;

		while (tmpVoisin) {
			if (!heapContains(h, tmpVoisin->v) || (tmpVoisin->gamma==R->gamma)) {
				tmpVoisin = tmpVoisin->voisSuiv;
				continue;
			}
			Noeud * neighbor = rechercheNoeud(R->LNoeuds, tmpVoisin->v);
			float longueur = sqrt(
					pow((currentNode->x - neighbor->x), 2.0)
							+ pow((currentNode->y - neighbor->y), 2.0));
			float alt = dist[currentNode->u] + longueur;

			if (alt < dist[neighbor->u]) {
				dist[neighbor->u] = alt;
				previous[neighbor->u] = currentNode;
				HeapNode * tmp = heapExtract(h, neighbor->u);
				tmp->c = dist[neighbor->u];
				heapAdd(h, tmp);
			}

			tmpVoisin = tmpVoisin->voisSuiv;
		}
		freeHeapNode(head);
	}
	freeHeap(h);
	return previous;
}

Chaine * convertPrevious_csp(Reseau *R, Noeud ** previous, int target) {
	Chaine * ch = creerChaine(-1);
	Noeud * node = rechercheNoeud(R->LNoeuds, target);
	Noeud * prevnode = NULL;
	ch->chSuiv = NULL;
	ch->uneExtremite = insererPointDebut(ch->uneExtremite,
			creerPoint(node->x, node->y));
	prevnode = node;
	node = previous[target];
	while (node) {
		ch->uneExtremite = insererPointDebut(ch->uneExtremite,
				creerPoint(node->x, node->y));
		updateGamma(prevnode, node);
		prevnode = node;
		node = previous[node->u];
	}
	return ch;
}

void updateGamma(Noeud *u, Noeud *v) {
	// chercher le voisin v du noeud u et augmente son gamma
	chercheVoisin(u, v->u)->gamma++;
	// chercher le voisin u du noeud v et augmente son gamma
	chercheVoisin(v, u->u)->gamma++;

}

Voisin *chercheVoisin(Noeud *node, int vs) {
	Voisin *vois = node->LVoisins;
	while (vois) {
		if (vois->v == vs) {
			return vois;
		}
		vois=vois->voisSuiv;
	}
	leverErreur("Voisin non présent");
	return NULL;
}

int getMaxGamma(Reseau *R){
	CelluleLNoeud *cell=R->LNoeuds;
	Voisin *vois=NULL;
	int max=-1;
	while (cell){
		vois=cell->ptrnoeud->LVoisins;
		while(vois){
			if(vois->gamma > max){
				max=vois->gamma;
			}
			vois=vois->voisSuiv;
		}
		cell=cell->noeudSuiv;
	}
	return max;
}

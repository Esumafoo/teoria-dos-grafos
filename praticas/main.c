
#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

static void imprimir_vizinhos_matriz(GrafoMatriz *g, int n) {
	for (int v = 0; v < n; v++) {
		printf("vertice %d:", v);
		int first = 1;
		for (int u = 0; u < n; u++) {
			if (g->adj[v][u]) {
				if (first) { printf(" %d", u); first = 0; }
				else printf(" %d", u);
			}
		}
		printf("\n");
	}
}

static void imprimir_vizinhos_lista(GrafoLista *g, int n) {
	for (int v = 0; v < n; v++) {
		printf("vertice %d:", v);
		No *p = g->adj[v];
		int first = 1;
		while (p) {
			if (first) { printf(" %d", p->destino); first = 0; }
			else printf(" %d", p->destino);
			p = p->prox;
		}
		printf("\n");
	}
}

int main(void) {
	int n = 5;

	
	GrafoMatriz *gm = criar_grafo_matriz(n);
	if (!gm) { fprintf(stderr, "erro: criar grafo matriz\n"); return 1; }
	inserir_aresta_matriz(gm, 0, 1);
	inserir_aresta_matriz(gm, 0, 2);
	inserir_aresta_matriz(gm, 1, 2);
	inserir_aresta_matriz(gm, 3, 4);

	printf("Grafo Matriz - vizinhos por vertice:\n");
	imprimir_vizinhos_matriz(gm, n);

	remover_aresta_matriz(gm, 0, 1);
	printf("Removida aresta 0-1\n");
	printf("Grafo Matriz - vizinhos apos remocao:\n");
	imprimir_vizinhos_matriz(gm, n);

	liberar_grafo_matriz(gm);


	GrafoLista *gl = criar_grafo_lista(n);
	if (!gl) { fprintf(stderr, "erro: criar grafo lista\n"); return 1; }
	inserir_aresta_lista(gl, 0, 1);
	inserir_aresta_lista(gl, 0, 2);
	inserir_aresta_lista(gl, 1, 2);
	inserir_aresta_lista(gl, 3, 4);

	printf("\nGrafo Lista - vizinhos por vertice:\n");
	imprimir_vizinhos_lista(gl, n);

	remover_aresta_lista(gl, 0, 1);
	printf("Removida aresta 0-1\n");
	printf("Grafo Lista - vizinhos apos remocao:\n");
	imprimir_vizinhos_lista(gl, n);

	liberar_grafo_lista(gl);

	return 0;
}


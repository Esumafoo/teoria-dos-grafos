#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"

GrafoLista *criar_grafo(int n) {
    GrafoLista *g = (GrafoLista *) malloc(sizeof(GrafoLista));
    g->n = n;
    g->m = 0;
    for (int i = 0; i < n; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {
    Aresta *a1 = (Aresta *) malloc(sizeof(Aresta));
    a1->destino = v;
    a1->prox = g->adj[u];
    g->adj[u] = a1;

    Aresta *a2 = (Aresta *) malloc(sizeof(Aresta));
    a2->destino = u;
    a2->prox = g->adj[v];
    g->adj[v] = a2;

    g->m++;
}

void liberar_grafo(GrafoLista *g) {
    for (int i = 0; i < g->n; i++) {
        Aresta *atual = g->adj[i];
        while (atual != NULL) {
            Aresta *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g);
}

void dfs_articulacoes(GrafoLista *g, int u, int visitado[], int descoberta[],
                       int low[], int pai[], int eh_articulacao[], int *tempo) {
    int filhos = 0;
    visitado[u] = 1;
    descoberta[u] = low[u] = (*tempo)++;

    for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
        int v = a->destino;

        if (!visitado[v]) {
            filhos++;
            pai[v] = u;
            dfs_articulacoes(g, v, visitado, descoberta, low, pai, eh_articulacao, tempo);

            if (low[v] < low[u]) {
                low[u] = low[v];
            }

            if (pai[u] == -1 && filhos > 1) {
                eh_articulacao[u] = 1;
            }

            if (pai[u] != -1 && low[v] >= descoberta[u]) {
                eh_articulacao[u] = 1;
            }

        } else if (v != pai[u]) {
            if (descoberta[v] < low[u]) {
                low[u] = descoberta[v];
            }
        }
    }
}

void encontrar_articulacoes(GrafoLista *g) {
    int visitado[MAX_VERTICES] = {0};
    int descoberta[MAX_VERTICES] = {0};
    int low[MAX_VERTICES] = {0};
    int pai[MAX_VERTICES];
    int eh_articulacao[MAX_VERTICES] = {0};
    int tempo = 0;

    for (int i = 0; i < g->n; i++) {
        pai[i] = -1;
    }

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            dfs_articulacoes(g, i, visitado, descoberta, low, pai, eh_articulacao, &tempo);
        }
    }

    printf("Vertices de articulacao (pontos de corte):\n");
    int encontrado = 0;
    for (int i = 0; i < g->n; i++) {
        if (eh_articulacao[i]) {
            printf("  Vertice %d\n", i);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("  Nenhum\n");
    }
}

void dfs_pontes(GrafoLista *g, int u, int visitado[], int descoberta[],
                 int low[], int pai[]) {
    static int tempo = 0;
    visitado[u] = 1;
    descoberta[u] = low[u] = tempo++;

    for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
        int v = a->destino;

        if (!visitado[v]) {
            pai[v] = u;
            dfs_pontes(g, v, visitado, descoberta, low, pai);

            if (low[v] < low[u]) {
                low[u] = low[v];
            }

            if (low[v] > descoberta[u]) {
                printf("  Ponte: (%d, %d)\n", u, v);
            }

        } else if (v != pai[u]) {
            if (descoberta[v] < low[u]) {
                low[u] = descoberta[v];
            }
        }
    }
}

void detectar_pontes(GrafoLista *g) {
    int visitado[MAX_VERTICES] = {0};
    int descoberta[MAX_VERTICES] = {0};
    int low[MAX_VERTICES] = {0};
    int pai[MAX_VERTICES];

    for (int i = 0; i < g->n; i++) {
        pai[i] = -1;
    }

    printf("Pontes (arestas de corte):\n");

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            dfs_pontes(g, i, visitado, descoberta, low, pai);
        }
    }
}
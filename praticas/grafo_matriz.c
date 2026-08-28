#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo_matriz.h"

GrafoMatriz *criar_grafo_matriz(int n) {
    if (n <= 0) return NULL;
    GrafoMatriz *g = (GrafoMatriz *)malloc(sizeof(GrafoMatriz));
    if (!g) return NULL;
    g->n = n;
    g->adj = (int **)malloc(n * sizeof(int *));
    if (!g->adj) {
        free(g);
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        g->adj[i] = (int *)calloc(n, sizeof(int));
        if (!g->adj[i]) {
            for (int j = 0; j < i; j++) free(g->adj[j]);
            free(g->adj);
            free(g);
            return NULL;
        }
    }
    return g;
}

void inserir_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (!g) return;
    if (u >= 0 && u < g->n && v >= 0 && v < g->n) {
        g->adj[u][v] = 1;
        g->adj[v][u] = 1;
    }
}

void remover_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (!g) return;
    if (u >= 0 && u < g->n && v >= 0 && v < g->n) {
        g->adj[u][v] = 0;
        g->adj[v][u] = 0;
    }
}

int grau_matriz(GrafoMatriz *g, int v) {
    if (!g) return -1;
    if (v >= 0 && v < g->n) {
        int grau_v = 0;
        for (int i = 0; i < g->n; i++) {
            grau_v += g->adj[v][i];
        }
        return grau_v;
    }
    return -1;
}

int sao_adjacentes_matriz(GrafoMatriz *g, int u, int v) {
    if (!g) return 0;
    if (u >= 0 && u < g->n && v >= 0 && v < g->n) {
        return g->adj[u][v] == 1;
    }
    return 0;
}

void liberar_grafo_matriz(GrafoMatriz *g) {
    if (!g) return;
    for (int i = 0; i < g->n; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g);
}


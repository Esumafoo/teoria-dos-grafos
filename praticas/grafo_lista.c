#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo_lista(int n) {
    if (n <= 0) return NULL;

    GrafoLista *g = malloc(sizeof(GrafoLista));
    if (!g) return NULL;

    g->n = n;
    g->adj = malloc((size_t)n * sizeof(No *));
    if (!g->adj) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < n; i++) g->adj[i] = NULL;
    return g;
}

void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    if (!g || u < 0 || u >= g->n || v < 0 || v >= g->n) return;

    No *p = g->adj[u];
    while (p) {
        if (p->destino == v) break;
        p = p->prox;
    }

    if (!p) {
        No *no = malloc(sizeof(No));
        if (!no) return;
        no->destino = v;
        no->prox = g->adj[u];
        g->adj[u] = no;
    }

    p = g->adj[v];
    while (p) {
        if (p->destino == u) break;
        p = p->prox;
    }

    if (!p) {
        No *no = malloc(sizeof(No));
        if (!no) return;
        no->destino = u;
        no->prox = g->adj[v];
        g->adj[v] = no;
    }
}

void remover_aresta_lista(GrafoLista *g, int u, int v) {
    if (!g || u < 0 || u >= g->n || v < 0 || v >= g->n) return;

    No **pp = &g->adj[u];
    while (*pp) {
        if ((*pp)->destino == v) {
            No *tmp = *pp;
            *pp = tmp->prox;
            free(tmp);
            break;
        }
        pp = &(*pp)->prox;
    }

    pp = &g->adj[v];
    while (*pp) {
        if ((*pp)->destino == u) {
            No *tmp = *pp;
            *pp = tmp->prox;
            free(tmp);
            break;
        }
        pp = &(*pp)->prox;
    }
}

int grau_lista(GrafoLista *g, int v) {
    if (!g || v < 0 || v >= g->n) return -1;

    int cnt = 0;
    for (No *p = g->adj[v]; p; p = p->prox) cnt++;
    return cnt;
}

int sao_adjacentes_lista(GrafoLista *g, int u, int v) {
    if (!g || u < 0 || u >= g->n || v < 0 || v >= g->n) return 0;

    for (No *p = g->adj[u]; p; p = p->prox) {
        if (p->destino == v) return 1;
    }
    return 0;
}

void liberar_grafo_lista(GrafoLista *g) {
    if (!g) return;

    for (int i = 0; i < g->n; i++) {
        No *p = g->adj[i];
        while (p) {
            No *tmp = p;
            p = p->prox;
            free(tmp);
        }
    }

    free(g->adj);
    free(g);
}

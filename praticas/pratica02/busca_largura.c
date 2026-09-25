#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"

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

Fila *criar_fila(int capacidade) {
    Fila *f = (Fila *) malloc(sizeof(Fila));
    f->dados = (int *) malloc(sizeof(int) * capacidade);
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

int fila_vazia(Fila *f) {
    return f->tamanho == 0;
}

void enfileirar(Fila *f, int valor) {
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

int desenfileirar(Fila *f) {
    int valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return valor;
}

void liberar_fila(Fila *f) {
    free(f->dados);
    free(f);
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    int visitado[MAX_VERTICES] = {0};

    for (int i = 0; i < g->n; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    Fila *f = criar_fila(g->n);
    visitado[origem] = 1;
    dist[origem] = 0;
    enfileirar(f, origem);

    while (!fila_vazia(f)) {
        int u = desenfileirar(f);

        for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
            int v = a->destino;
            if (!visitado[v]) {
                visitado[v] = 1;
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(f, v);
            }
        }
    }

    liberar_fila(f);
}

int eh_bipartido(GrafoLista *g) {
    int cor[MAX_VERTICES];
    for (int i = 0; i < g->n; i++) {
        cor[i] = -1;
    }

    for (int s = 0; s < g->n; s++) {
        if (cor[s] != -1) continue;

        cor[s] = 0;
        Fila *f = criar_fila(g->n);
        enfileirar(f, s);

        while (!fila_vazia(f)) {
            int u = desenfileirar(f);

            for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
                int v = a->destino;

                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    enfileirar(f, v);
                } else if (cor[v] == cor[u]) {
                    liberar_fila(f);
                    return 0;
                }
            }
        }

        liberar_fila(f);
    }

    return 1;
}

int contar_componentes(GrafoLista *g) {
    int visitado[MAX_VERTICES] = {0};
    int componentes = 0;

    for (int s = 0; s < g->n; s++) {
        if (visitado[s]) continue;

        componentes++;
        visitado[s] = 1;
        Fila *f = criar_fila(g->n);
        enfileirar(f, s);

        while (!fila_vazia(f)) {
            int u = desenfileirar(f);

            for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
                int v = a->destino;
                if (!visitado[v]) {
                    visitado[v] = 1;
                    enfileirar(f, v);
                }
            }
        }

        liberar_fila(f);
    }

    return componentes;
}
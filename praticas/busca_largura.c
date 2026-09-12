#include <stdlib.h>
#include "busca_largura.h"

Fila *criar_fila(int capacidade) {
    if (capacidade <= 0) return NULL;

    Fila *fila = malloc(sizeof(Fila));
    if (!fila) return NULL;

    fila->dados = malloc((size_t)capacidade * sizeof(int));
    if (!fila->dados) {
        free(fila);
        return NULL;
    }

    fila->capacidade = capacidade;
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    return fila;
}

void enfileirar(Fila *fila, int valor) {
    if (!fila || fila->tamanho == fila->capacidade) return;

    fila->dados[fila->fim] = valor;
    fila->fim = (fila->fim + 1) % fila->capacidade;
    fila->tamanho++;
}

int desenfileirar(Fila *fila) {
    int valor;

    if (!fila || fila->tamanho == 0) return -1;

    valor = fila->dados[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;
    return valor;
}

int fila_vazia(Fila *fila) {
    return !fila || fila->tamanho == 0;
}

void liberar_fila(Fila *fila) {
    if (!fila) return;
    free(fila->dados);
    free(fila);
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    if (!g || !dist || !pred || origem < 0 || origem >= g->n) return;

    for (int i = 0; i < g->n; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    Fila *fila = criar_fila(g->n);
    if (!fila) return;

    dist[origem] = 0;
    enfileirar(fila, origem);

    while (!fila_vazia(fila)) {
        int u = desenfileirar(fila);

        for (No *p = g->adj[u]; p; p = p->prox) {
            int v = p->destino;

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(fila, v);
            }
        }
    }

    liberar_fila(fila);
}

int eh_bipartido(GrafoLista *g) {
    if (!g) return 0;

    int *cor = malloc((size_t)g->n * sizeof(int));
    if (!cor) return 0;

    for (int i = 0; i < g->n; i++) cor[i] = -1;

    Fila *fila = criar_fila(g->n);
    if (!fila) {
        free(cor);
        return 0;
    }

    for (int inicio = 0; inicio < g->n; inicio++) {
        if (cor[inicio] != -1) continue;

        cor[inicio] = 0;
        enfileirar(fila, inicio);

        while (!fila_vazia(fila)) {
            int u = desenfileirar(fila);

            for (No *p = g->adj[u]; p; p = p->prox) {
                int v = p->destino;

                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    enfileirar(fila, v);
                } else if (cor[v] == cor[u]) {
                    liberar_fila(fila);
                    free(cor);
                    return 0;
                }
            }
        }
    }

    liberar_fila(fila);
    free(cor);
    return 1;
}

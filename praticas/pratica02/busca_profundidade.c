#include <stdio.h>
#include <stdlib.h>
#include "busca_profundidade.h"

Pilha *criar_pilha(int capacidade) {
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));
    p->dados = (int *) malloc(sizeof(int) * capacidade);
    p->capacidade = capacidade;
    p->topo = -1;
    return p;
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, int valor) {
    p->topo++;
    p->dados[p->topo] = valor;
}

int desempilhar(Pilha *p) {
    int valor = p->dados[p->topo];
    p->topo--;
    return valor;
}

void liberar_pilha(Pilha *p) {
    free(p->dados);
    free(p);
}

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred,
                    int *tempo_entrada, int *tempo_saida, int *tempo) {
    visitado[u] = 1;
    tempo_entrada[u] = (*tempo)++;

    for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
        int v = a->destino;
        if (!visitado[v]) {
            pred[v] = u;
            dfs_recursiva(g, v, visitado, pred, tempo_entrada, tempo_saida, tempo);
        }
    }

    tempo_saida[u] = (*tempo)++;
}

void dfs_iterativa(GrafoLista *g, int origem, int *visitado, int *pred) {
    Pilha *p = criar_pilha(g->n * g->n + 1);
    empilhar(p, origem);

    while (!pilha_vazia(p)) {
        int u = desempilhar(p);

        if (!visitado[u]) {
            visitado[u] = 1;

            for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
                int v = a->destino;
                if (!visitado[v]) {
                    pred[v] = u;
                    empilhar(p, v);
                }
            }
        }
    }

    liberar_pilha(p);
}

static int dfs_ciclo(GrafoLista *g, int u, int pai, int *visitado) {
    visitado[u] = 1;

    for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
        int v = a->destino;

        if (!visitado[v]) {
            if (dfs_ciclo(g, v, u, visitado)) {
                return 1;
            }
        } else if (v != pai) {
            return 1;
        }
    }

    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int visitado[MAX_VERTICES] = {0};

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            if (dfs_ciclo(g, i, -1, visitado)) {
                return 1;
            }
        }
    }

    return 0;
}
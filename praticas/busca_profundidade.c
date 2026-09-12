#include <stdlib.h>
#include "busca_profundidade.h"

void dfs_recursiva(GrafoLista *g, int u, int *visitado,
                   int *entrada, int *saida, int *tempo) {
    if (!g || !visitado || !entrada || !saida || !tempo) return;
    if (u < 0 || u >= g->n) return;

    visitado[u] = 1;
    entrada[u] = ++(*tempo);

    for (No *p = g->adj[u]; p; p = p->prox) {
        int v = p->destino;
        if (!visitado[v]) {
            dfs_recursiva(g, v, visitado, entrada, saida, tempo);
        }
    }

    saida[u] = ++(*tempo);
}

int contar_componentes(GrafoLista *g) {
    if (!g) return 0;

    int *visitado = calloc((size_t)g->n, sizeof(int));
    int *entrada = calloc((size_t)g->n, sizeof(int));
    int *saida = calloc((size_t)g->n, sizeof(int));

    if (!visitado || !entrada || !saida) {
        free(visitado);
        free(entrada);
        free(saida);
        return 0;
    }

    int componentes = 0;
    int tempo = 0;

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            componentes++;
            dfs_recursiva(g, i, visitado, entrada, saida, &tempo);
        }
    }

    free(visitado);
    free(entrada);
    free(saida);
    return componentes;
}

static int dfs_ciclo(GrafoLista *g, int u, int *visitado, int pai) {
    visitado[u] = 1;

    for (No *p = g->adj[u]; p; p = p->prox) {
        int v = p->destino;

        if (!visitado[v]) {
            if (dfs_ciclo(g, v, visitado, u)) return 1;
        } else if (v != pai) {
            return 1;
        }
    }

    return 0;
}

int tem_ciclo(GrafoLista *g) {
    if (!g) return 0;

    int *visitado = calloc((size_t)g->n, sizeof(int));
    if (!visitado) return 0;

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i] && dfs_ciclo(g, i, visitado, -1)) {
            free(visitado);
            return 1;
        }
    }

    free(visitado);
    return 0;
}

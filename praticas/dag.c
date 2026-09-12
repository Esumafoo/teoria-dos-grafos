#include <stdlib.h>
#include "dag.h"

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

void inserir_aresta_direcionada(GrafoLista *g, int u, int v) {
    if (!g || u < 0 || u >= g->n || v < 0 || v >= g->n) return;

    for (No *p = g->adj[u]; p; p = p->prox) {
        if (p->destino == v) return;
    }

    No *no = malloc(sizeof(No));
    if (!no) return;

    no->destino = v;
    no->prox = g->adj[u];
    g->adj[u] = no;
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

typedef struct {
    int *dados;
    int inicio;
    int fim;
    int tamanho;
} Fila;

static Fila *criar_fila(int capacidade) {
    Fila *f = malloc(sizeof(Fila));
    if (!f) return NULL;

    f->dados = malloc((size_t)capacidade * sizeof(int));
    if (!f->dados) {
        free(f);
        return NULL;
    }

    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

static void enfileirar(Fila *f, int valor, int capacidade) {
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % capacidade;
    f->tamanho++;
}

static int desenfileirar(Fila *f, int capacidade) {
    int valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % capacidade;
    f->tamanho--;
    return valor;
}

static void liberar_fila(Fila *f) {
    if (!f) return;
    free(f->dados);
    free(f);
}

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    if (!g || !tamanho) return NULL;
    *tamanho = 0;

    int *grau_entrada = calloc((size_t)g->n, sizeof(int));
    int *ordem = malloc((size_t)g->n * sizeof(int));
    Fila *fila = criar_fila(g->n);

    if (!grau_entrada || !ordem || !fila) {
        free(grau_entrada);
        free(ordem);
        liberar_fila(fila);
        return NULL;
    }

    for (int u = 0; u < g->n; u++) {
        for (No *p = g->adj[u]; p; p = p->prox) {
            grau_entrada[p->destino]++;
        }
    }

    for (int i = 0; i < g->n; i++) {
        if (grau_entrada[i] == 0) {
            enfileirar(fila, i, g->n);
        }
    }

    while (fila->tamanho > 0) {
        int u = desenfileirar(fila, g->n);
        ordem[*tamanho] = u;
        (*tamanho)++;

        for (No *p = g->adj[u]; p; p = p->prox) {
            int v = p->destino;
            grau_entrada[v]--;

            if (grau_entrada[v] == 0) {
                enfileirar(fila, v, g->n);
            }
        }
    }

    free(grau_entrada);
    liberar_fila(fila);

    if (*tamanho != g->n) {
        free(ordem);
        *tamanho = 0;
        return NULL;
    }

    return ordem;
}

static int dfs_topologica(GrafoLista *g, int u, int *estado,
                          int *ordem, int *pos) {
    estado[u] = 1;

    for (No *p = g->adj[u]; p; p = p->prox) {
        int v = p->destino;

        if (estado[v] == 1) return 0;

        if (estado[v] == 0) {
            if (!dfs_topologica(g, v, estado, ordem, pos)) {
                return 0;
            }
        }
    }

    estado[u] = 2;
    ordem[--(*pos)] = u;
    return 1;
}

int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    if (!g || !tamanho) return NULL;
    *tamanho = 0;

    int *estado = calloc((size_t)g->n, sizeof(int));
    int *ordem = malloc((size_t)g->n * sizeof(int));

    if (!estado || !ordem) {
        free(estado);
        free(ordem);
        return NULL;
    }

    int pos = g->n;

    for (int i = 0; i < g->n; i++) {
        if (estado[i] == 0) {
            if (!dfs_topologica(g, i, estado, ordem, &pos)) {
                free(estado);
                free(ordem);
                return NULL;
            }
        }
    }

    free(estado);
    *tamanho = g->n;
    return ordem;
}

int eh_dag(GrafoLista *g) {
    if (!g) return 0;

    int tamanho = 0;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);

    if (!ordem) return 0;

    free(ordem);
    return 1;
}

#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H

#define MAX_VERTICES 100

typedef struct Aresta {
    int destino;
    struct Aresta *prox;
} Aresta;

typedef struct {
    int n;
    int m;
    Aresta *adj[MAX_VERTICES];
} GrafoLista;

GrafoLista *criar_grafo(int n);
void adicionar_aresta(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);

void dfs_articulacoes(GrafoLista *g, int u, int visitado[], int descoberta[],
                       int low[], int pai[], int eh_articulacao[], int *tempo);
void encontrar_articulacoes(GrafoLista *g);

void dfs_pontes(GrafoLista *g, int u, int visitado[], int descoberta[],
                 int low[], int pai[]);
void detectar_pontes(GrafoLista *g);

#endif
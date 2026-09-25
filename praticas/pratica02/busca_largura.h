#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

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

typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

GrafoLista *criar_grafo(int n);
void adicionar_aresta(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);

Fila *criar_fila(int capacidade);
int fila_vazia(Fila *f);
void enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f);
void liberar_fila(Fila *f);

void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int eh_bipartido(GrafoLista *g);
int contar_componentes(GrafoLista *g);

#endif
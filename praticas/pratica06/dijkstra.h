#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits.h>

#define INF INT_MAX


typedef struct No {
    int vertice;
    int peso;
    struct No *proximo;
} No;

typedef struct {
    No **lista;
    int num_vertices;
} GrafoListaPonderado;


typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; 
} MinHeap;


GrafoListaPonderado *criar_grafo(int num_vertices);

int adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso, int direcionado);
void liberar_grafo(GrafoListaPonderado *g);


MinHeap *criar_min_heap(int capacidade);
void inserir(MinHeap *h, int vertice, int distancia);
NoHeap extrair_minimo(MinHeap *h);
void diminuir_chave(MinHeap *h, int vertice, int nova_distancia);
int heap_vazio(MinHeap *h);
void liberar_min_heap(MinHeap *h);


void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);


int reconstruir_caminho(int origem, int destino, int *pred);

#endif

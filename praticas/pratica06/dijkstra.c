#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"



GrafoListaPonderado *criar_grafo(int num_vertices) {
    GrafoListaPonderado *g = malloc(sizeof(GrafoListaPonderado));
    if (!g) return NULL;
    g->num_vertices = num_vertices;
    g->lista = calloc(num_vertices, sizeof(No *));
    if (!g->lista) {
        free(g);
        return NULL;
    }
    return g;
}

static int inserir_adjacencia(GrafoListaPonderado *g, int u, int v, int peso) {
    No *novo = malloc(sizeof(No));
    if (!novo) return 0;
    novo->vertice = v;
    novo->peso = peso;
    novo->proximo = g->lista[u];
    g->lista[u] = novo;
    return 1;
}

int adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso, int direcionado) {
    if (u < 0 || u >= g->num_vertices || v < 0 || v >= g->num_vertices) return 0;
    if (peso < 0) return 0; /* Dijkstra não aceita pesos negativos */
    if (!inserir_adjacencia(g, u, v, peso)) return 0;
    if (!direcionado && !inserir_adjacencia(g, v, u, peso)) return 0;
    return 1;
}

void liberar_grafo(GrafoListaPonderado *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *no = g->lista[i];
        while (no) {
            No *prox = no->proximo;
            free(no);
            no = prox;
        }
    }
    free(g->lista);
    free(g);
}



static void trocar(MinHeap *h, int i, int j) {
    NoHeap tmp = h->dados[i];
    h->dados[i] = h->dados[j];
    h->dados[j] = tmp;
    h->posicao[h->dados[i].vertice] = i;
    h->posicao[h->dados[j].vertice] = j;
}

static void subir(MinHeap *h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (h->dados[pai].distancia <= h->dados[i].distancia) break;
        trocar(h, pai, i);
        i = pai;
    }
}

static void descer(MinHeap *h, int i) {
    for (;;) {
        int esq = 2 * i + 1, dir = 2 * i + 2, menor = i;
        if (esq < h->tamanho && h->dados[esq].distancia < h->dados[menor].distancia)
            menor = esq;
        if (dir < h->tamanho && h->dados[dir].distancia < h->dados[menor].distancia)
            menor = dir;
        if (menor == i) break;
        trocar(h, i, menor);
        i = menor;
    }
}

MinHeap *criar_min_heap(int capacidade) {
    MinHeap *h = malloc(sizeof(MinHeap));
    if (!h) return NULL;
    h->capacidade = capacidade;
    h->tamanho = 0;
    h->dados = malloc(capacidade * sizeof(NoHeap));
    h->posicao = malloc(capacidade * sizeof(int));
    if (!h->dados || !h->posicao) {
        free(h->dados);
        free(h->posicao);
        free(h);
        return NULL;
    }
    for (int i = 0; i < capacidade; i++) h->posicao[i] = -1;
    return h;
}

void inserir(MinHeap *h, int vertice, int distancia) {
    if (h->tamanho >= h->capacidade) return;
    int i = h->tamanho++;
    h->dados[i].vertice = vertice;
    h->dados[i].distancia = distancia;
    h->posicao[vertice] = i;
    subir(h, i);
}

NoHeap extrair_minimo(MinHeap *h) {
    NoHeap minimo = h->dados[0];
    NoHeap ultimo = h->dados[h->tamanho - 1];
    h->posicao[minimo.vertice] = -1; /* saiu do heap */
    h->tamanho--;
    if (h->tamanho > 0) {
        h->dados[0] = ultimo;
        h->posicao[ultimo.vertice] = 0;
        descer(h, 0);
    }
    return minimo;
}


void diminuir_chave(MinHeap *h, int vertice, int nova_distancia) {
    int i = h->posicao[vertice];
    if (i == -1) return;                          
    if (nova_distancia >= h->dados[i].distancia) return;
    h->dados[i].distancia = nova_distancia;
    subir(h, i);
}

int heap_vazio(MinHeap *h) {
    return h->tamanho == 0;
}

void liberar_min_heap(MinHeap *h) {
    if (!h) return;
    free(h->dados);
    free(h->posicao);
    free(h);
}



void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int n = g->num_vertices;
    MinHeap *heap = criar_min_heap(n);
    if (!heap) return;

    for (int v = 0; v < n; v++) {
        dist[v] = INF;
        pred[v] = -1;
    }
    dist[origem] = 0;

    for (int v = 0; v < n; v++)
        inserir(heap, v, dist[v]);

    while (!heap_vazio(heap)) {
        NoHeap atual = extrair_minimo(heap);
        int u = atual.vertice;

        if (atual.distancia == INF) break; /* o resto é inalcançável */

        for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
            int v = no->vertice;
            /* relaxamento de (u, v) */
            if (heap->posicao[v] != -1 && dist[u] + no->peso < dist[v]) {
                dist[v] = dist[u] + no->peso;
                pred[v] = u;
                diminuir_chave(heap, v, dist[v]);
            }
        }
    }

    liberar_min_heap(heap);
}



static void imprimir_caminho_rec(int origem, int v, int *pred) {
    if (v != origem) {
        imprimir_caminho_rec(origem, pred[v], pred);
        printf(" -> ");
    }
    printf("%c", 'A' + v);
}

int reconstruir_caminho(int origem, int destino, int *pred) {
    if (origem != destino && pred[destino] == -1) {
        printf("Nao existe caminho de %c ate %c\n", 'A' + origem, 'A' + destino);
        return 0;
    }
    imprimir_caminho_rec(origem, destino, pred);
    printf("\n");
    return 1;
}

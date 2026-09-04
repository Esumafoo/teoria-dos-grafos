#include <stdio.h>
#include "grafo_lista.h"

GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista*)malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->lista = (No**)malloc(num_vertices * sizeof(No*));
    
    for (int i = 0; i < num_vertices; i++) {
        g->lista[i] = (No*)malloc(sizeof(No));
        g->lista[i]->vertice = i;
        g->lista[i]->proximo = NULL;
    }
    
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {

}
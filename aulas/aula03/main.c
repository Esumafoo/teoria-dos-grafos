#include <stdio.h>
#include "grafo_lista.h"

int main() {
    GrafoLista *g = criar_grafo(5);
    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 0, 2);
    adicionar_aresta(g, 1, 3);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 3, 4);

    for (int i= 0; i < g->num_vertices; i++) {
        printf("%i: -> ", i+1);
        No *no = g->lista[i];
        while (no != NULL) {
            printf("%i -> ", no->vertice++);
            no = no->proximo;
        }
        printf("NULL\n");
    }

    return 0;
}

#ifndef GRAFO_LISTA
#define GRAFO_LISTA

typedef struct No {
    int vertice;
    struct No *proximo;
} No;

typedef struct{
    No **lista;
    int num_vertices;
}GrafoLista;

GrafoLista *criar_grafo_lista(int n);
void adicionar_aresta_lista(GrafoLista *g, int u, int v);

#endif
#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"
#include "planaridade.h"

int main(void) {
    int n, m;

    printf("Digite o numero de vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_VERTICES) {
        printf("Numero de vertices invalido.\n");
        return 1;
    }

    printf("Digite o numero de arestas: ");
    if (scanf("%d", &m) != 1 || m < 0) {
        printf("Numero de arestas invalido.\n");
        return 1;
    }

    GrafoLista *g = criar_grafo(n);

    printf("Digite as %d arestas (formato: u v), com vertices de 0 a %d:\n", m, n - 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2 || u < 0 || u >= n || v < 0 || v >= n) {
            printf("Aresta invalida, ignorando.\n");
            continue;
        }
        adicionar_aresta(g, u, v);
    }

    printf("\n--- Grafo carregado ---\n");
    printf("Vertices: %d | Arestas: %d\n\n", g->n, g->m);

    printf("--- Analise de Conectividade ---\n");
    encontrar_articulacoes(g);
    printf("\n");
    detectar_pontes(g);

    verificar_planaridade(g);

    liberar_grafo(g);
    return 0;
}
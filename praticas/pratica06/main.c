#include <stdio.h>
#include "dijkstra.h"

static void imprimir_resultado(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    printf("Distancias minimas a partir de %c:\n", 'A' + origem);
    for (int v = 0; v < g->num_vertices; v++) {
        if (dist[v] == INF)
            printf("  %c: inalcancavel\n", 'A' + v);
        else
            printf("  %c: %d\n", 'A' + v, dist[v]);
    }
    (void)pred;
}

int main(void) {
    int dist[5], pred[5];


    printf("=== Atividade guiada (nao orientado) ===\n");
    GrafoListaPonderado *g = criar_grafo(5);
    adicionar_aresta(g, 0, 1, 2, 0); /* A-B 2 */
    adicionar_aresta(g, 0, 2, 6, 0); /* A-C 6 */
    adicionar_aresta(g, 1, 2, 1, 0); /* B-C 1 */
    adicionar_aresta(g, 1, 3, 4, 0); /* B-D 4 */
    adicionar_aresta(g, 2, 3, 1, 0); /* C-D 1 */
    adicionar_aresta(g, 3, 4, 3, 0); /* D-E 3 */

    dijkstra(g, 0, dist, pred);
    imprimir_resultado(g, 0, dist, pred);

    printf("Caminho minimo de A ate E (custo %d): ", dist[4]);
    reconstruir_caminho(0, 4, pred);
    liberar_grafo(g);


    printf("\n=== Exemplo da aula (digrafo) ===\n");
    GrafoListaPonderado *g2 = criar_grafo(4);
    adicionar_aresta(g2, 0, 1, 4, 1); /* A->B 4 */
    adicionar_aresta(g2, 0, 2, 1, 1); /* A->C 1 */
    adicionar_aresta(g2, 1, 3, 1, 1); /* B->D 1 */
    adicionar_aresta(g2, 2, 1, 2, 1); /* C->B 2 */
    adicionar_aresta(g2, 2, 3, 5, 1); /* C->D 5 */

    dijkstra(g2, 0, dist, pred);
    imprimir_resultado(g2, 0, dist, pred);

    printf("Caminho minimo de A ate D (custo %d): ", dist[3]);
    reconstruir_caminho(0, 3, pred);


    printf("\n=== Origem D (nenhum vertice alcancavel alem dele) ===\n");
    dijkstra(g2, 3, dist, pred);
    imprimir_resultado(g2, 3, dist, pred);
    reconstruir_caminho(3, 0, pred);

    printf("\n=== Peso negativo ===\n");
    if (!adicionar_aresta(g2, 1, 2, -3, 1))
        printf("Aresta com peso negativo rejeitada (use Bellman-Ford).\n");

    liberar_grafo(g2);
    return 0;
}

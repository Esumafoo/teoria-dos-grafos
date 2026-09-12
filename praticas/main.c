#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

int main(void) {
    int n = 6;
    GrafoLista *g = criar_grafo_lista(n);

    if (!g) {
        printf("Erro ao criar grafo.\n");
        return 1;
    }

    inserir_aresta_lista(g, 0, 1);
    inserir_aresta_lista(g, 0, 2);
    inserir_aresta_lista(g, 1, 3);
    inserir_aresta_lista(g, 1, 4);
    inserir_aresta_lista(g, 2, 4);

    int *dist = malloc((size_t)n * sizeof(int));
    int *pred = malloc((size_t)n * sizeof(int));
    int *visitado = calloc((size_t)n, sizeof(int));
    int *entrada = calloc((size_t)n, sizeof(int));
    int *saida = calloc((size_t)n, sizeof(int));

    if (!dist || !pred || !visitado || !entrada || !saida) {
        printf("Erro de memoria.\n");
        free(dist); free(pred); free(visitado); free(entrada); free(saida);
        liberar_grafo_lista(g);
        return 1;
    }

    printf("=== BFS ===\n");
    bfs(g, 0, dist, pred);
    for (int i = 0; i < n; i++) {
        printf("vertice %d: distancia=%d, predecessor=%d\n",
               i, dist[i], pred[i]);
    }

    int tempo = 0;
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            dfs_recursiva(g, i, visitado, entrada, saida, &tempo);
        }
    }

    printf("\n=== DFS ===\n");
    for (int i = 0; i < n; i++) {
        printf("vertice %d: entrada=%d, saida=%d\n",
               i, entrada[i], saida[i]);
    }

    printf("\n=== COMPONENTES ===\n");
    printf("componentes: %d\n", contar_componentes(g));

    printf("\n=== CICLO ===\n");
    printf("tem ciclo: %s\n", tem_ciclo(g) ? "sim" : "nao");

    printf("\n=== BIPARTICAO ===\n");
    printf("eh bipartido: %s\n", eh_bipartido(g) ? "sim" : "nao");

    free(dist);
    free(pred);
    free(visitado);
    free(entrada);
    free(saida);
    liberar_grafo_lista(g);

    return 0;
}

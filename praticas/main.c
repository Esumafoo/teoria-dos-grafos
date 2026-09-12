#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

static void imprimir_ordem(const char *nome, int *ordem, int tamanho) {
    printf("%s: ", nome);

    if (!ordem) {
        printf("ciclo detectado\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        if (i > 0) printf(" -> ");
        printf("%d", ordem[i]);
    }
    printf("\n");
}

int main(void) {
    GrafoLista *g = criar_grafo_lista(6);

    if (!g) {
        printf("Erro ao criar grafo.\n");
        return 1;
    }

    inserir_aresta_direcionada(g, 0, 1);
    inserir_aresta_direcionada(g, 0, 2);
    inserir_aresta_direcionada(g, 1, 3);
    inserir_aresta_direcionada(g, 2, 3);
    inserir_aresta_direcionada(g, 3, 4);
    inserir_aresta_direcionada(g, 2, 5);

    int tamanho_kahn = 0;
    int *ordem_kahn = ordenacao_topologica_kahn(g, &tamanho_kahn);

    int tamanho_dfs = 0;
    int *ordem_dfs = ordenacao_topologica_dfs(g, &tamanho_dfs);

    printf("=== ORDENACAO TOPOLOGICA ===\n");
    imprimir_ordem("Kahn", ordem_kahn, tamanho_kahn);
    imprimir_ordem("DFS", ordem_dfs, tamanho_dfs);

    printf("Eh DAG? %s\n", eh_dag(g) ? "sim" : "nao");

    free(ordem_kahn);
    free(ordem_dfs);
    liberar_grafo_lista(g);

    return 0;
}

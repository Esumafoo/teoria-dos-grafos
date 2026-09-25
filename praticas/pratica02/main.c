#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
#include "busca_profundidade.h"

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

    int origem;
    printf("Digite o vertice de origem para BFS/DFS: ");
    if (scanf("%d", &origem) != 1 || origem < 0 || origem >= n) {
        printf("Vertice de origem invalido.\n");
        liberar_grafo(g);
        return 1;
    }

    printf("\n--- Grafo carregado ---\n");
    printf("Vertices: %d | Arestas: %d\n\n", g->n, g->m);

    int dist[MAX_VERTICES];
    int pred_bfs[MAX_VERTICES];
    bfs(g, origem, dist, pred_bfs);

    printf("--- BFS a partir do vertice %d ---\n", origem);
    for (int i = 0; i < n; i++) {
        printf("Vertice %d: dist = %d, pred = %d\n", i, dist[i], pred_bfs[i]);
    }

    int visitado[MAX_VERTICES] = {0};
    int pred_dfs[MAX_VERTICES];
    int tempo_entrada[MAX_VERTICES];
    int tempo_saida[MAX_VERTICES];
    int tempo = 0;

    for (int i = 0; i < n; i++) {
        pred_dfs[i] = -1;
    }

    printf("\n--- DFS recursiva (tempos de entrada/saida) ---\n");
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            dfs_recursiva(g, i, visitado, pred_dfs, tempo_entrada, tempo_saida, &tempo);
        }
    }
    for (int i = 0; i < n; i++) {
        printf("Vertice %d: entrada = %d, saida = %d, pred = %d\n",
               i, tempo_entrada[i], tempo_saida[i], pred_dfs[i]);
    }

    printf("\n--- Componentes Conexos ---\n");
    int num_componentes = contar_componentes(g);
    printf("Numero de componentes conexos: %d\n", num_componentes);

    printf("\n--- Deteccao de Ciclo ---\n");
    if (tem_ciclo(g)) {
        printf("O grafo contem ciclo.\n");
    } else {
        printf("O grafo NAO contem ciclo.\n");
    }

    printf("\n--- Teste de Bipartição ---\n");
    if (eh_bipartido(g)) {
        printf("O grafo E bipartido.\n");
    } else {
        printf("O grafo NAO e bipartido.\n");
    }

    liberar_grafo(g);
    return 0;
}
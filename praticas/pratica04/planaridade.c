#include <stdio.h>
#include <stdlib.h>
#include "planaridade.h"

static void construir_matriz(GrafoLista *g, int matriz[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            matriz[i][j] = 0;
        }
    }
    for (int u = 0; u < g->n; u++) {
        for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
            matriz[u][a->destino] = 1;
        }
    }
}

int eh_planar_euler(GrafoLista *g) {
    int n = g->n;
    int m = g->m;

    if (n < 3) {
        return 1;
    }

    return (m <= 3 * n - 6);
}

int contem_k5(GrafoLista *g) {
    int n = g->n;
    if (n < 5) return 0;

    int matriz[MAX_VERTICES][MAX_VERTICES];
    construir_matriz(g, matriz);

    int comb[5];

    for (comb[0] = 0; comb[0] < n; comb[0]++)
    for (comb[1] = comb[0] + 1; comb[1] < n; comb[1]++)
    for (comb[2] = comb[1] + 1; comb[2] < n; comb[2]++)
    for (comb[3] = comb[2] + 1; comb[3] < n; comb[3]++)
    for (comb[4] = comb[3] + 1; comb[4] < n; comb[4]++) {
        int completo = 1;
        for (int i = 0; i < 5 && completo; i++) {
            for (int j = i + 1; j < 5 && completo; j++) {
                if (!matriz[comb[i]][comb[j]]) {
                    completo = 0;
                }
            }
        }
        if (completo) {
            printf("  Subgrafo K5 encontrado: {%d, %d, %d, %d, %d}\n",
                   comb[0], comb[1], comb[2], comb[3], comb[4]);
            return 1;
        }
    }

    return 0;
}

int contem_k33(GrafoLista *g) {
    int n = g->n;
    if (n < 6) return 0;

    int matriz[MAX_VERTICES][MAX_VERTICES];
    construir_matriz(g, matriz);

    int A[3], B[3];

    for (A[0] = 0; A[0] < n; A[0]++)
    for (A[1] = A[0] + 1; A[1] < n; A[1]++)
    for (A[2] = A[1] + 1; A[2] < n; A[2]++)
    for (B[0] = 0; B[0] < n; B[0]++) {
        if (B[0] == A[0] || B[0] == A[1] || B[0] == A[2]) continue;
        for (B[1] = B[0] + 1; B[1] < n; B[1]++) {
            if (B[1] == A[0] || B[1] == A[1] || B[1] == A[2]) continue;
            for (B[2] = B[1] + 1; B[2] < n; B[2]++) {
                if (B[2] == A[0] || B[2] == A[1] || B[2] == A[2]) continue;

                int completo = 1;
                for (int i = 0; i < 3 && completo; i++) {
                    for (int j = 0; j < 3 && completo; j++) {
                        if (!matriz[A[i]][B[j]]) {
                            completo = 0;
                        }
                    }
                }

                if (completo) {
                    printf("  Subgrafo K3,3 encontrado: A={%d,%d,%d} B={%d,%d,%d}\n",
                           A[0], A[1], A[2], B[0], B[1], B[2]);
                    return 1;
                }
            }
        }
    }

    return 0;
}

void verificar_planaridade(GrafoLista *g) {
    printf("\n--- Verificacao de Planaridade ---\n");

    int euler_ok = eh_planar_euler(g);
    printf("Condicao de Euler (m <= 3n - 6): %s\n", euler_ok ? "satisfeita" : "violada");

    if (!euler_ok) {
        printf("Resultado: o grafo NAO e planar (falha na condicao de Euler).\n");
        return;
    }

    if (g->n <= 10) {
        int tem_k5 = contem_k5(g);
        int tem_k33 = contem_k33(g);

        if (tem_k5 || tem_k33) {
            printf("Resultado: o grafo NAO e planar (contem subgrafo K5 ou K3,3).\n");
        } else {
            printf("Resultado: o grafo E provavelmente planar (heuristica nao encontrou K5/K3,3).\n");
        }
    } else {
        printf("n > 10: heuristica de Kuratowski nao aplicada. Apenas a condicao de Euler foi usada.\n");
    }
}
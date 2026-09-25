#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "busca_largura.h"

typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

Pilha *criar_pilha(int capacidade);
int pilha_vazia(Pilha *p);
void empilhar(Pilha *p, int valor);
int desempilhar(Pilha *p);
void liberar_pilha(Pilha *p);

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred,
                    int *tempo_entrada, int *tempo_saida, int *tempo);
void dfs_iterativa(GrafoLista *g, int origem, int *visitado, int *pred);
int tem_ciclo(GrafoLista *g);

#endif
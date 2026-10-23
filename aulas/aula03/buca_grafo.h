#include "grafo_lista.h"


int pilha[10];
int visitado[10];
int topo = 0;


void dfs(GrafoLista *g, int u, int *p){
    visitado[u] = 1;
    No *no = g ->lista[u];
    while(no != NULL){
        int v=no->vertice;
        if(!visitado[u])dfs(g,v, p);
        no = no->proximo;
    }
    topo--;


}
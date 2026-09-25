#ifndef PLANARIDADE_H
#define PLANARIDADE_H

#include "conectividade.h"

int eh_planar_euler(GrafoLista *g);
int contem_k5(GrafoLista *g);
int contem_k33(GrafoLista *g);
void verificar_planaridade(GrafoLista *g);

#endif
#ifndef MOCHILA_PRIVADA
#define MOCHILA_PRIVADA

#include "mochila_publica.h"

int quicksort_r(pLoja L, int start, int end);
int bubblesort(pLoja L);

typedef struct item item;

typedef struct Mochila{
    
    float CapacidadeTotal;
    float CapacidadeDisponivel;
    int posicao;

    item *conteudo[MAXLOJA];
}Mochila;

typedef struct Loja{
    
    float CapacidadeTotal;
    float CapacidadeDisponivel;
    float PesoTotal;
    int posicao;

    item *conteudo[MAXLOJA];
}Loja;

struct item{
    int idItem;
    float peso;
    float valor;
    float cb;

};

#endif
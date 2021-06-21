#ifndef MOCHILA_PRIVADA
#define MOCHILA_PRIVADA

#include "mochila_publica.h"

typedef struct item item;

int OrdenarLoja(pLoja L);
int VerificaPeso(Mochila);

typedef struct Mochila{
    
    float CapacidadeTotal;
    float CapacidadeDisponivel;
    int posicao;

    item *conteudo[MAXLOJA];
}Mochila;

struct item{
    int idItem;
    float peso;
    float valor;
    float cb;

};

#endif
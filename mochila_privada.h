#ifndef MOCHILA_PRIVADA
#define MOCHILA_PRIVADA

#include "mochila_publica.h"

typedef struct item item;

int OrdenarItems(Loja);
int VerificaPeso(Mochila);

typedef struct Mochila{
    
    float CapacidadeTotal;
    float CapacidadeDisponivel;

    item *conteudo;
}Mochila;

struct item{
    int idItem;
    float peso;
    float valor;
    float cb;
    item *ant;
    item *prox;
};

#endif
#ifndef MOCHILA_PRIVADA
#define MOCHILA_PRIVADA

#include "mochila_publica.h"

int OrdenarItems(Loja);
int VerificaPeso(Mochila);
 
typedef struct {
    int *identificador;
    float *valor;
    float *QtdInicial;
    float *QtdDisponivel;
    float *cb;
}Loja;

typedef struct {
    float CapacidadeInicial;
    float CapacidadeDisponivel;
    float *idItem;
    float *peso;
}Mochila;

#endif
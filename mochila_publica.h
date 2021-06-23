#ifndef MOCHILA_PUBLICA
#define MOCHILA_PUBLICA

#define MAXLOJA 10

typedef struct Mochila Loja;
typedef struct Mochila Mochila;

typedef Mochila * pMochila;
typedef Loja * pLoja;

int CriarMochila(pMochila *M, float CapacidadeTotal);
int CarregaMochila(pMochila M, pLoja L, int Exibe);
int ImprimeMochila(pMochila M);
int DestruirMochila(pMochila M);

int CriarLoja(pLoja *L, float CapacidadeLoja);
int AddLoja(pLoja L, int ID, float valor, float QtdInicial, int Exibe);
int ImprimeLoja(pLoja L);
int OrdenarLoja(pLoja L, int Exibe);
int DestruirLoja(pLoja L);

#endif
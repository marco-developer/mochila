#ifndef MOCHILA_PUBLICA
#define MOCHILA_PUBLICA

#define MAXLOJA 100

typedef struct Mochila Loja;
typedef struct Mochila Mochila;

typedef Mochila * pMochila;
typedef Loja * pLoja;

int CriarMochila(pMochila *M, float CapacidadeTotal);
int CarregaMochila(pMochila M, pLoja L);
int ImprimeMochila(pMochila M);
int DestruirMochila(pMochila M);

int OrdenarLoja(pLoja L);

int CriarLoja(pLoja *L, float CapacidadeLoja);
int AddLoja(pLoja L, int ID, float valor, float QtdInicial);
int ImprimeLoja(pLoja L);
int DestruirLoja(pLoja L);

#endif

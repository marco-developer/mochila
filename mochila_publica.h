#ifndef MOCHILA_PUBLICA
#define MOCHILA_PUBLICA

#define MAXLOJA 100000

typedef struct Loja Loja;
typedef struct Mochila Mochila;

typedef Mochila * pMochila;
typedef Loja * pLoja;

int CriarMochila(pMochila *M, pLoja L);
int CarregaMochila(pMochila M, pLoja L);
int ImprimeMochila(pMochila M);
int DestruirMochila(pMochila M);

int CriarLoja(pLoja *L, float CapacidadeLoja);
int AddLoja(pLoja L, int ID, float valor, float QtdInicial);
int OrdenarLojaBubble(pLoja L);
int OrdenarLojaQuick(pLoja L);
int ImprimeLoja(pLoja L);
int DestruirLoja(pLoja L);

#endif

#ifndef MOCHILA_PUBLICA
#define MOCHILA_PUBLICA

int CriarMochila(Mochila M, float CapacidadeInicial);
int AddLoja(float valor, float QtdInicial);
int CarregaMochila(Mochila M, Loja *L);
int ImprimeMochila(Mochila M);
int DestruirMochila(Mochila M);

#endif
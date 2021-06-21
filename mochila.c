#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mochila_privada.h"

int CriarMochila(pMochila *M, float CapacidadeTotal) {
        
    // Aloca espaco em memoria para mochila (2 dados do tipo inteiro para cada item)
    // printf("Alocando memoria!\n");
    pMochila tmp_mochila = (pMochila) malloc(sizeof(Mochila));

    if(tmp_mochila == NULL){
        printf("Erro: Falha na alocacao de memoria!\n");
        return 1;
    }

    // Inicializa Mochila
    // OBS: Mochila remodelada para ter um header contendo capacidade total e disponível e um 
    // ponteiro para primeiro elemento. Os elementos sao armazenados em forma de fila.
    printf("Inicializando mochila!\n");
    tmp_mochila->CapacidadeTotal = CapacidadeTotal;
    tmp_mochila->CapacidadeDisponivel = CapacidadeTotal;
    // tmp_mochila->inicio = NULL;
    
    printf("Capacidade total da mochila: %f\n", tmp_mochila->CapacidadeTotal);
    printf("Capacidade disponivel na mochila: %f\n\n", tmp_mochila->CapacidadeDisponivel);

    // Atualiza ponteiro
    // printf("Atualizando ponteiro da mochila de fora!\n");
    *M = tmp_mochila;

    return 0;
}

int CriarLoja(pLoja *L, float CapacidadeLoja) {

    // Funcoes CriarLoja e CriarMochila sao redundantes. Aprimorar.
        
    // Aloca espaco em memoria para Loja (2 dados do tipo inteiro para cada item)
    // printf("Alocando memoria!\n");
    pLoja tmp_Loja = (pLoja) malloc(sizeof(Loja));

    if(tmp_Loja == NULL){
        printf("Erro: Falha na alocacao de memoria!\n");
        return 1;
    }

    // Inicializa Loja
    printf("Inicializando Loja!\n");
    tmp_Loja->CapacidadeTotal = CapacidadeLoja;
    tmp_Loja->CapacidadeDisponivel = CapacidadeLoja;
    tmp_Loja->posicao = 0;
    // tmp_Loja->inicio = tmp_Loja->fim = NULL;
    
    printf("Capacidade total da Loja: %f\n", tmp_Loja->CapacidadeTotal);
    printf("Capacidade disponivel na Loja: %f\n\n", tmp_Loja->CapacidadeDisponivel);

    // Atualiza ponteiro
    // printf("Atualizando ponteiro da Loja de fora!\n");
    *L = tmp_Loja;

    return 0;

}

int AddLoja(pLoja L, int ID, float valor, float QtdInicial){

    // verifica se ha espaco disponivel na loja
    // Para a Loja, a capacidade disponivel eh considerada em qtd de itens, diferente da mochila, que eh em peso.
    if(L->CapacidadeDisponivel==0) {
        printf("Sem espaco para alocar mais itens!\n");
        //exit(1);
        return 1;
    } else {

        //aloca struct para item
        item * I = (item*) malloc(sizeof(item));
        
        // armazena dados do item
        printf("\nCriando novo item ID = %d:\n", ID);
        I->idItem = ID;
        printf("Valor do novo item = %.2f:\n", valor);
        I->valor = valor;
        printf("Peso disponivel do novo item = %f:\n", QtdInicial);
        I->peso = QtdInicial;
        I->cb = valor/QtdInicial;
        printf("C/B do novo item = %.2f:\n", I->cb);
        
        // atualiza loja
        L->conteudo[L->posicao] = I;
        L->posicao++;
    }
        
    // reduz capacidade da loja
    L->CapacidadeDisponivel--;
    printf("Nova capacidade da loja: %.0f\n\n", L->CapacidadeDisponivel);
    return 0;
}

int ImprimeLoja(pLoja L) {

    if(L->conteudo == NULL) {
        printf("Nao ha itens na Loja!\n");
        return 1;
    }
    
    printf("\nIniciando impressao da Loja\n");

    for(int i=0; i < L->posicao; i++){
        printf("ID item: %d\n", L->conteudo[i]->idItem);
        printf("Peso disponivel: %f\n", L->conteudo[i]->peso);
        printf("Valor total do item: %f\n", L->conteudo[i]->valor);
        printf("C/B do item: %f\n\n", L->conteudo[i]->cb);
    }
    return 0;
}

int ImprimeMochila(pMochila M) {

    if(M->conteudo == NULL) {
        printf("Nao ha itens na Mochila!\n");
        return 1;
    }
    
    printf("\nIniciando impressao da Mochila\n");

    for(int i=0; i <=M->posicao; i++){
        printf("ID item: %d\n", M->conteudo[i]->idItem);
        printf("Peso: %f\n", M->conteudo[i]->peso);
        printf("Valor total do item: %f\n", M->conteudo[i]->valor);
        printf("C/B do item: %f\n\n", M->conteudo[i]->cb);
    }
    return 0;
}

int OrdenarLoja(pLoja L) {
    int i, j;
    item *aux;

    printf("Iniciando processo de ordenacao decrescente de c/b\n");
    for(i=L->posicao-1; i>0; i--){
    // tmp1 = proximo;
        for(j=0; j<i; j++){

            if(L->conteudo[j]->cb < L->conteudo[j+1]->cb) {
                printf("Atual cb eh menor q proximo cb. Inverter\n");

                aux = L->conteudo[j];
                L->conteudo[j] = L->conteudo[j+1];
                L->conteudo[j+1] = aux;

                printf("Inversao ok\n\n");
            }
        }
    }
    return 0;
}

int CarregaMochila(pMochila M, pLoja L) {

    int i = 0;
    float lucro = 0;
    float temp = 0;

    printf("\nIniciando carregamento da mochila...\n\n");
    printf("Capacidade Disponivel = %f\n",M->CapacidadeDisponivel);
    while(M->CapacidadeDisponivel!=0) {

        printf("Cap. Mochila: %f\n", M->CapacidadeDisponivel);
        printf("Carregando item: %d\n", L->conteudo[i]->idItem);
        printf("Peso total item: %f\n", L->conteudo[i]->peso);

        if(L->conteudo[i]->peso!=0){
            M->conteudo[i] = L->conteudo[i];

            if(M->CapacidadeDisponivel < L->conteudo[i]->peso) {
                
                printf("Capacidade da mochila eh menor que peso do item %d\n\n", L->conteudo[i]->idItem);

                M->conteudo[i]->peso = M->CapacidadeDisponivel;
                L->conteudo[i]->peso = L->conteudo[i]->peso - M->CapacidadeDisponivel;
                
                                
                temp = M->conteudo[i]->valor * M->CapacidadeDisponivel;
                M->CapacidadeDisponivel = 0;

                lucro = lucro + temp;
                M->posicao = i;
                
                i++;
                
            }else if(M->CapacidadeDisponivel == L->conteudo[i]->peso){
                printf("Capacidade da mochila eh igual peso do item %d\n\n", L->conteudo[i]->idItem);

                M->CapacidadeDisponivel = L->conteudo[i]->peso = 0;

                lucro = lucro + M->conteudo[i]->valor;
                M->posicao = i;
                
                i++;
                break;
            }else {
                printf("Capacidade da mochila eh maior que peso do item %d\n\n", L->conteudo[i]->idItem);

                M->CapacidadeDisponivel = M->CapacidadeDisponivel - L->conteudo[i]->peso;
                // printf("Peso analise item: %f\n", M->conteudo[i]->peso);
                L->conteudo[i]->peso = 0;

                lucro = lucro + M->conteudo[i]->valor;
                M->posicao = i;
                
                i++;

            }
            
        } else i++;
    }
    
    printf("\nPeso\t\tPreco \n");
    for(i=0;i<=M->posicao;i++)
        printf("%f\t%f\n", M->conteudo[i]->peso, M->conteudo[i]->valor);
    printf("\nLucro maximo: %f\n", lucro);

return 0;
}

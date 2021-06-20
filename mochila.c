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
    tmp_mochila->conteudo = NULL;
    
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
    tmp_Loja->conteudo = NULL;

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
        exit(1);
    } else {

        //aloca struct para item
        item * I = (item*) malloc(sizeof(item));
        I->prox = I->ant = NULL;

        // armazena dados do item
        printf("\nCriando novo item ID = %d:\n", ID);
        I->idItem = ID;
        printf("Valor do novo item = %.2f:\n", valor);
        I->valor = valor;
        printf("Peso disponivel do novo item = %f:\n", QtdInicial);
        I->peso = QtdInicial;
        I->cb = valor/QtdInicial;;
        printf("C/B do novo item = %.2f:\n", I->cb);
        
        // reduz capacidade da loja
        L->CapacidadeDisponivel--;
        printf("Nova capacidade da loja: %.0f\n\n", L->CapacidadeDisponivel);

        // atualiza loja
        item * temp = (item*) malloc(sizeof(item));
        
        if(L->conteudo==NULL) L->conteudo = I; 
        else {
            temp = L->conteudo;
            while(temp->prox!=NULL) {
                temp = temp->prox;
            }
            temp->prox = I;
            I->ant = temp;
            
        }
    }
}

int ImprimeLoja(pLoja L) {

    //aloca struct para item
    item * temp = (item*) malloc(sizeof(item));
    
    temp = L->conteudo;

    if(temp == NULL) {
        printf("Nao ha itens na Loja!\n");
        return 1;
    }
    
    printf("Iniciando impressao da Loja\n");

    if(temp->prox==NULL){
        printf("ID item: %d\n", temp->idItem);
        printf("Peso disponivel: %f\n", temp->peso);
        printf("Valor total do item: %f\n", temp->valor);
        printf("C/B do item: %f\n", temp->cb);
    } else {

        while(temp!=NULL) {
            printf("ID item: %d\n", temp->idItem);
            printf("Peso disponivel: %f\n", temp->peso);
            printf("Valor total do item: %f\n", temp->valor);
            printf("C/B do item: %f\n\n", temp->cb);
            temp = temp->prox;
        }
    }
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mochila_privada.h"

int CriarMochila(pMochila *M, pLoja L, int Exibe) {
        
    float CapacidadeTotal = L->PesoTotal*0.5;

    // Aloca espaco em memoria para mochila (2 dados do tipo inteiro para cada item)
    pMochila tmp_mochila;
    tmp_mochila = malloc(sizeof(Mochila));

    if(tmp_mochila == NULL){
        printf("Erro: Falha na alocacao de memoria!\n");
        return 1;
    }

    // Inicializa Mochila
    // OBS: Mochila remodelada para ter um header contendo capacidade total e disponível e um 
    // vetor de conteudo para os elementos.
    if (Exibe==1){printf("Inicializando mochila!\n");}
    tmp_mochila->CapacidadeTotal = CapacidadeTotal;
    tmp_mochila->CapacidadeDisponivel = CapacidadeTotal;

    if (Exibe==1){printf("Capacidade total da mochila: %f\n", tmp_mochila->CapacidadeTotal);}
    if (Exibe==1){printf("Capacidade disponivel na mochila: %f\n\n", tmp_mochila->CapacidadeDisponivel);}

    // Atualiza ponteiro
    *M = tmp_mochila;

    return 0;
}

int CriarLoja(pLoja *L, float CapacidadeLoja, int Exibe) {

    // Aloca espaco em memoria para Loja
    // printf("Alocando memoria!\n");
    pLoja tmp_Loja;
    tmp_Loja = malloc(sizeof(Loja));

    if(tmp_Loja == NULL){
        printf("Erro: Falha na alocacao de memoria!\n");
        return 1;
    }

    // Inicializa Loja
    if (Exibe==1){printf("Inicializando Loja!\n");}
    tmp_Loja->CapacidadeTotal = CapacidadeLoja;
    tmp_Loja->CapacidadeDisponivel = CapacidadeLoja;
    tmp_Loja->posicao = 0;
    
    if (Exibe==1){printf("Capacidade total da Loja: %f\n", tmp_Loja->CapacidadeTotal);}
    if (Exibe==1){printf("Capacidade disponivel na Loja: %f\n\n", tmp_Loja->CapacidadeDisponivel);}

    // Atualiza ponteiro
    // printf("Atualizando ponteiro da Loja de fora!\n");
    *L = tmp_Loja;

    return 0;

}

int AddLoja(pLoja L, int ID, float valor, float peso, int Exibe){

    // Verifica se ha espaco disponivel na loja
    // Para a Loja, a capacidade disponivel eh considerada em qtd de itens, diferente da mochila, que eh em peso.
    if(L->CapacidadeDisponivel==0) {
        if (Exibe==1){printf("Sem espaco para alocar mais itens!\n");}
        return 1;
    } else {

        //aloca struct para item
        // item * I = (item*) malloc(sizeof(item));
        L->conteudo[L->posicao] = malloc(sizeof(item));
        
        // armazena dados do item
        if (Exibe==1){printf("\nCriando novo item ID %d\n", ID);}
        L->conteudo[L->posicao]->idItem = ID;
        if (Exibe==1){printf("Valor do novo item: %.2f\n", valor);}
        L->conteudo[L->posicao]->valor = valor;
        if (Exibe==1){printf("Peso disponivel do novo item %f:\n", peso);}
        L->conteudo[L->posicao]->peso = peso;
        L->conteudo[L->posicao]->cb = valor/peso;
        if (Exibe==1){printf("C/B do novo item: %.2f\n", L->conteudo[L->posicao]->cb);}
        
        // atualiza loja
        //L->conteudo[L->posicao] = I;
        L->PesoTotal = L->PesoTotal + L->conteudo[L->posicao]->peso;
        L->posicao++;

        // reduz capacidade da loja
        L->CapacidadeDisponivel--;
        if (Exibe==1){printf("Nova capacidade da loja: %.0f\n\n", L->CapacidadeDisponivel);}
        return 0;
    }

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


int quicksort_r(pLoja L, int start, int end){
    if (start>=end) {
        return 0;
    }

    item * swp;
    item * pivot = L->conteudo[end];

    //set a pointer to divide array into two parts
    //one part is smaller than pivot and another larger
    int pointer = start;
    int i;

    for (i=start; i<end; i++) {
        if (L->conteudo[i]->cb > pivot->cb) {
            if (pointer!=i) {
                //swap a[i] with a[pointer]
                //a[pointer] behind larger than pivot
                swp = L->conteudo[i];
                L->conteudo[i] = L->conteudo[pointer];
                L->conteudo[pointer] = swp;
            }
            pointer++;
        }
    }
    //swap back pivot to proper position
    swp = L->conteudo[end];
    L->conteudo[end] = L->conteudo[pointer];
    L->conteudo[pointer] = swp;
    quicksort_r(L, start, pointer-1);
    quicksort_r(L, pointer+1, end);
    return 0;
}

int bubblesort(pLoja L){
    int i, j;
    item *aux;

    for(i=L->posicao-1; i>0; i--){
        for(j=0; j<i; j++){
            if(L->conteudo[j]->cb < L->conteudo[j+1]->cb) {
                //printf("Atual cb eh menor q proximo cb. Inverter\n");
                aux = L->conteudo[j];
                L->conteudo[j] = L->conteudo[j+1];
                L->conteudo[j+1] = aux;
            }
        }
    }
    return 0;
}

int OrdenarLojaQuick(pLoja L, int Exibe) {

    if (Exibe==1){printf("Iniciando processo de ordenacao decrescente de C/B (QuickSort)\n");}
    quicksort_r(L, 0, L->posicao - 1);
    return 0;
}


int OrdenarLojaBubble(pLoja L, int Exibe) {

    if (Exibe==1){printf("Iniciando processo de ordenacao decrescente de C/B (BubbleSort)\n");}
    bubblesort(L);

    return 0;
}

int CarregaMochila(pMochila M, pLoja L, int Exibe) {

    int i = 0;
    float lucro = 0;
    float temp = 0;


    if (Exibe==1){printf("\nIniciando carregamento da mochila...\n\n");}
    if (Exibe==1){printf("Capacidade Disponivel = %f\n",M->CapacidadeDisponivel);}

    while(M->CapacidadeDisponivel!=0 && L->CapacidadeDisponivel!=L->CapacidadeTotal) {

        if (Exibe==1){printf("Cap. Mochila: %f\n", M->CapacidadeDisponivel);}
        if (Exibe==1){printf("Carregando item: %d\n", L->conteudo[i]->idItem);}
        if (Exibe==1){printf("Peso total item: %f\n", L->conteudo[i]->peso);}

        if(L->conteudo[i]->peso!=0){

            // Coloca na mochila os itens
            // Ja estao organizados na loja do maior para menor
            M->conteudo[i] = malloc(sizeof(item)); 
            M->conteudo[i]->cb = L->conteudo[i]->cb; //M->conteudo[i] = L->conteudo[i];
            M->conteudo[i]->idItem = L->conteudo[i]->idItem;
            M->conteudo[i]->peso = L->conteudo[i]->peso;
            M->conteudo[i]->valor = L->conteudo[i]->valor;

            if(M->CapacidadeDisponivel < L->conteudo[i]->peso) {
                
                if (Exibe==1){printf("Capacidade da mochila eh menor que peso do item %d\n\n", L->conteudo[i]->idItem);}
                M->conteudo[i]->peso = M->CapacidadeDisponivel;
                L->conteudo[i]->peso = L->conteudo[i]->peso - M->CapacidadeDisponivel;

                temp = M->conteudo[i]->valor / M->CapacidadeDisponivel;
                M->CapacidadeDisponivel = 0;

                if (Exibe==1){printf("Valor proporcional ao peso colocado: %f\n", temp);}
                lucro = lucro + temp;
                M->posicao = i;
                
                i++;
            }else if(M->CapacidadeDisponivel == L->conteudo[i]->peso){
                if (Exibe==1){printf("Capacidade da mochila eh igual peso do item %d\n\n", L->conteudo[i]->idItem);}
                M->CapacidadeDisponivel = L->conteudo[i]->peso = 0;
                L->posicao--;
                L->CapacidadeDisponivel++;

                lucro = lucro + M->conteudo[i]->valor;
                M->posicao = i;
                
                i++;
                break;
            }else {
                if (Exibe==1){printf("Capacidade da mochila eh maior que peso do item %d\n\n", L->conteudo[i]->idItem);}
                M->CapacidadeDisponivel = M->CapacidadeDisponivel - L->conteudo[i]->peso;
                L->conteudo[i]->peso = 0;
                L->posicao--;
                L->CapacidadeDisponivel++;

                if (Exibe==1){printf("Valor proporcional ao peso colocado: %f\n", M->conteudo[i]->valor);}
                lucro = lucro + M->conteudo[i]->valor;
                M->posicao = i;
                
                i++;
            }
        } else i++;
    }
    if (Exibe==1){printf("\nPeso\t\tPreco \n");}
    for(i=0;i<=M->posicao;i++)
        if (Exibe==1){printf("%f\t%f\n", M->conteudo[i]->peso, M->conteudo[i]->valor);}
        if (Exibe==1){printf("\nLucro maximo: %f\n", lucro);}
        if (Exibe==1){printf("Espaco restante na mochila %f\n", M->CapacidadeDisponivel);}
    return 0;
}

int DestruirMochila(pMochila M){

    // CONDICAO PARA SAIDA EM CASO DE MOCHILA INEXISTENTE
    if(!M) {
        printf("Mochila nao alocada!\n");
        return 1;
    }

    // Se há elementos na mochila, remove todos
    if (M->CapacidadeDisponivel != M->CapacidadeTotal){
        for (int i=M->posicao;i>=0;i--){
            M->CapacidadeDisponivel = M->CapacidadeDisponivel+M->conteudo[M->posicao]->peso;
            free(M->conteudo[M->posicao]);
            M->conteudo[M->posicao] = NULL;
            M->posicao--;
        }
    }
    free(M);
    M = NULL;
    return 0;
}

int DestruirLoja(pLoja L, int Exibe){
    
    // CONDICAO PARA SAIDA EM CASO DE LOJA INEXISTENTE
    if(!L) {
        printf("Loja nao alocada!\n");
        return 1;
    }
    if (Exibe == 1){printf("\nIniciando destruicao da Loja.\n");}
    // Se há elementos na loja, remove todos
    if (L->CapacidadeDisponivel != L->CapacidadeTotal){
        for (int i=0;i<MAXLOJA;i++){//(int i=L->posicao;i>=0;i--){//(int i=MAXLOJA-2;i>=0;i--){
            free(L->conteudo[i]);//free(L->conteudo[L->posicao]);
            L->conteudo[i] = NULL;//L->conteudo[L->posicao] = NULL;
        }
    }
    L->posicao=0;
    L->CapacidadeDisponivel=L->CapacidadeTotal;
    free(L);
    L = NULL;
    return 0;
}

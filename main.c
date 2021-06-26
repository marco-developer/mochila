#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mochila_publica.h"
#include "time.h"

char* removeQuebra(char* linha)
{
    int tamLinha = strlen(linha);
    char* novo = (char*)malloc(tamLinha * sizeof(char));
    int j = 0;
    for (int i = 0; i < tamLinha; i++) {
        if (linha[i] != '\n') {
            memcpy(&novo[j], &linha[i], strlen(&linha[i]));
            j++;
            novo[j] = '\0';
        }
    }
    return novo;
}

void CriaVetor(float * vetor, int tamanho, float valorInicial, float valorFinal, int Crescente)
{
    if (tamanho == 0) {printf("\nVetor nulo");return;}

    // Define o passo de caimento de cada elemento do vetor
    float fator;
    fator = (valorFinal-valorInicial)/tamanho;

    if (Crescente==1){
        for (int i=0;i<tamanho;i++){
            vetor[i] = valorInicial + fator*i;
        }
    } else {
        for (int i=0;i<tamanho;i++){
            vetor[i] = valorFinal - fator*i;
        }
    }
    return;
}

int main(int argc, char *argv[]) {

    int i=0;
    char delim[] = ",";
    char line[200];
    char *token;
    pLoja L = NULL;
    pMochila M = NULL;

    if(argc==1) {
        printf ("Argumentos insuficientes. Informe o nome do arquivo.");
        exit(1);  
    }
    
    char *filename = argv[1];
    FILE *arq = fopen(filename, "r");
    
    if (arq == NULL) {
    	printf("Erro: falha ao abrir o arquivo %s\n", filename);
	exit(1);
    }

    int ordenacao = 0;
    if (argc>=3) { ordenacao = atoi(argv[2]);}

    // Seleciona impressao dos dados
    int Exibe = 1;
    if (argc>=4) { Exibe = atoi(argv[3]);}
    
    CriarLoja(&L, MAXLOJA, Exibe);
    
    if (Exibe==1){
        printf("\n==================================");
        printf("\nLENDO ARQUIVO:\n");
    }
    
    float valor[MAXLOJA], qtd_inicial[MAXLOJA], id[MAXLOJA];

    // Enquanto a linha não ser nula, fgets pega a linha
    while (fgets(line, sizeof(line), arq))
    {
        // Transforma a linha em uma string composta de tokens
        token = strtok(line, delim);
        // Converte o primeiro token (id) em float e add no vetor
        id[i] = strtod(token, NULL);
        // Transforma a linha em uma string composta de tokens
        token = strtok(NULL, delim);
        // Converte o primeiro token (valor) em float e add no vetor
        valor[i] = strtod(token, NULL);
        // Pega o segundo token...
        token = strtok(NULL, delim);
        // E converte o segundo token (qtd_inicial) em float e add no vetor
        qtd_inicial[i] = strtod(token, NULL);
        i++;
        if (i>MAXLOJA){break;}
    }
    
    // Adiciona na Loja o array de pares valor/peso
    clock_t add_time;
    add_time = clock();
    for(int j=0;j<i;j++) {
        AddLoja(L, id[i], valor[j], qtd_inicial[j], Exibe);
    }
    add_time = clock() - add_time;

    fclose(arq);

    if (Exibe==1){
        printf("\nLoja criada e itens adicionados:\n");
        ImprimeLoja(L);
    }

    
    // Define proporcao entre capacidade mochila/capacidade loja
    float proporcao = 0.5;
    CriarMochila(&M, L, proporcao, Exibe);

    //Ordena Loja
    clock_t order_time;
    order_time = clock();
    if(ordenacao==0){
        if (Exibe==1){
            printf("\nAlgoritmo de ordenacao quick sort.\n");
        }
        OrdenarLojaQuick(L, Exibe);
    } else if(ordenacao==1){
        if (Exibe==1){
            printf("\nAlgoritmo de ordenacao bubble sort.\n");
        }
        OrdenarLojaBubble(L, Exibe);
    } else {
        printf("Metodo de ordenacao nao identificado! Saindo...\n");
        exit (1);
    }
    order_time = clock() - order_time;

    if (Exibe==1){
        ImprimeLoja(L);
    }

    clock_t load_time;
    load_time = clock();
    CarregaMochila(M, L, Exibe);
    load_time = clock() - load_time;

    if (Exibe==1){
        ImprimeMochila(M);
        printf("\nACAO EXECUTADA \t\t\tTEMPO (s)\n");
        printf("-----------------------------------------\n");
        printf("Adicionar itens na loja: \t%lf\n", ((double)add_time)/((CLOCKS_PER_SEC)));
        printf("Ordenar itens da loja: \t\t%lf\n", ((double)order_time)/((CLOCKS_PER_SEC)));
        printf("Carregar mochila: \t\t%lf\n", ((double)load_time)/((CLOCKS_PER_SEC)));
        printf("-----------------------------------------\n");
        printf("TEMPO TOTAL: \t\t\t%lf\n", (((double)add_time+(double)order_time+(double)load_time)/((CLOCKS_PER_SEC))));
    } else {
        if (ordenacao==0){
            printf("\nQuickSort");
        } else {
            printf("\nBubbleSort");
        }
        printf(",Proporcao loja/mochila=%.2f",proporcao);
        printf(",n=%d",(int)MAXLOJA);
        printf(",tAddLoja=%lf",((double)add_time)/((CLOCKS_PER_SEC)));
        printf(",tOrdenarLoja=%lf",((double)order_time)/((CLOCKS_PER_SEC)));
        printf("tCarregaMochila=%lf", ((double)load_time)/((CLOCKS_PER_SEC)));
        printf(",tTotal=%lf\n", ((double)add_time+(double)order_time+(double)load_time)/(CLOCKS_PER_SEC));
    }

    // Libera os ponteiros
    DestruirLoja(L, Exibe);
    DestruirMochila(M, Exibe);
}

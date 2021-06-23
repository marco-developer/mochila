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
    for (int i = 0; i < strlen(linha); i++) {
        if (linha[i] != '\n') {
            memcpy(&novo[j], &linha[i], strlen(&linha[i]));
            j++;
            novo[j] = '\0';
        }
    }
    return novo;
}
float * CriaVetor(int tamanho, int valorInicial, int Crescente)
{
    float * vetor;
    vetor = malloc(tamanho*sizeof(float));

    // Define o passo de caimento de cada elemento do vetor
    int fator;
    fator = valorInicial/tamanho;

    if (Crescente==1){
        for (int i=0;i<tamanho;i++){
            vetor[i] = fator + fator*i;
        }
    } else {
        for (int i=0;i<tamanho;i++){
            vetor[i] = valorInicial - fator*i;
        }
    }

    return vetor;
}

int main(int argc, char *argv[])
{

    float cap;
    int i=0;
    const char delim[2] = " ";
    char line[MAXLOJA];
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

    // printf ("Informe o numero de itens da Loja: ");
    // scanf ("%d", &qtditens);

    printf ("Informe a capacidade da mochila: ");
    scanf ("%f", &cap);

    CriarLoja(&L, MAXLOJA);
    CriarMochila(&M, cap);

    printf("\n==================================");
    printf("\nLENDO ARQUIVO:\n");
    
    float valor[MAXLOJA], qtd_inicial[MAXLOJA];
    
    // Enquanto a linha não ser nula, fgets pega a linha
    while (fgets(line, sizeof(line), arq))
    {
        // Transforma a linha em uma string composta de tokens
        token = strtok(line, delim);
        // Converte o primeiro token (valor) em float e add no vetor
        valor[i] = strtod(token, NULL);
        // Pega o segundo token...
        token = strtok(NULL, delim);
        // E converte o segundo token (qtd_inicial) em float e add no vetor
        qtd_inicial[i] = strtod(token, NULL);
        i++;
    }
    
    printf("\nValor     Qtd_inicial:\n");
    for (int i = 0; i < 5; i++) {
        printf("%f %f\n", valor[i], qtd_inicial[i]);
    }
    
    // Adiciona na Loja o array de pares valor/peso
    clock_t add_time;

    add_time = clock();
    for(int j=0;j<i;j++) {
        AddLoja(L, j, valor[j], qtd_inicial[j]);
    }
    add_time = clock() - add_time;

    fclose(arq);









/*
    int *Resultado;

    float * qdeInicial;
    float * valor;

    // Cria os elementos para serem inseridos na mochila
    int numElementosDisponiveis;
    numElementosDisponiveis = 50;

    qdeInicial = CriaVetor(numElementosDisponiveis, 10, 0);
    valor = CriaVetor(numElementosDisponiveis, 50, 1);
    cap=10;

    CriarLoja(&L, numElementosDisponiveis);
    CriarMochila(&M, cap);

    // Adiciona na Loja o array de pares valor/peso
    for(int j=0;j<numElementosDisponiveis;j++) {

        AddLoja(L, j, valor[j], qdeInicial[j]);
        j=j+3;  // Para diminuir itens armazenados na loja
    }
    free(qdeInicial);
    free(valor);

*/







    ImprimeLoja(L);
    clock_t order_time;
    order_time = clock();
    OrdenarLoja(L);
    order_time = clock() - order_time;
    ImprimeLoja(L);
    clock_t load_time;
    load_time = clock();
    CarregaMochila(M, L);
    load_time = clock() - load_time;
    //ImprimeMochila(M);
    

    // Imprime tempos de execucao
    printf("\nACAO EXECUTADA \t\t\tTEMPO (s)\n");
    printf("-----------------------------------------\n");
    printf("Adicionar itens na loja: \t%lf\n", ((double)add_time)/((CLOCKS_PER_SEC/1000)));
    printf("Ordenar itens da loja: \t\t%lf\n", ((double)order_time)/((CLOCKS_PER_SEC/1000)));
    printf("Carregar mochila: \t\t%lf\n", ((double)load_time)/((CLOCKS_PER_SEC/1000)));
    printf("-----------------------------------------\n");
    printf("TEMPO TOTAL: \t\t\t%lf\n", (((double)add_time+(double)order_time+(double)load_time)/((CLOCKS_PER_SEC/1000))));




    // Libera os ponteiros
    DestruirLoja(L);
    DestruirMochila(M);

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mochila_publica.h"


char* removeQuebra(char* linha)
{
    int tamLinha = strlen(linha);
    char* novo = (char*)malloc(tamLinha * sizeof(char));
    int j = 0;
    for (unsigned int i = 0; i < strlen(linha); i++) {
        if (linha[i] != '\n') {
            memcpy(&novo[j], &linha[i], strlen(&linha[i]));
            j++;
            novo[j] = '\0';
        }
    }
    return novo;
}

int main(int argc, char *argv[])
{
    float cap;
    //float cb[MAXLOJA];
    int i=0, qtditens;
    const char delim[2] = " ";
    char line[MAXLOJA], *tmp, *campos[2*MAXLOJA], *tmp1;

    

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

    printf ("Informe o numero de itens da Loja: ");
    scanf ("%d", &qtditens);

    printf ("Informe a capacidade da mochila: ");
    scanf ("%f", &cap);

    CriarLoja(&L, qtditens);
    CriarMochila(&M, cap);
    
    char *token;

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
    for(int j=0;j<i;j++) {
        AddLoja(L, j, valor[j], qtd_inicial[j]);
    }

    // ImprimeLoja(L);
    printf("################ ORDENAR LOJA ################\n");
    OrdenarLoja(L);
    printf("################ IMPRIME LOJA ################\n");
    ImprimeLoja(L);
    printf("################ CARREGA MOCHILA ################\n");
    CarregaMochila(M, L);
    printf("################ IMPRIME MOCHILA ################\n");
    ImprimeMochila(M);
    

    return 0; 
}

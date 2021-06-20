#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mochila_publica.h"


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

void main(int argc, char *argv[])
{
    FILE *arq;
    float cap, cb[MAXLOJA];
    int i=0, qtditens;
    const char delim[2] = " ";
    char line[MAXLOJA], *tmp, *campos[2*MAXLOJA], *tmp1, *tmp2, *tmp3;
    pLoja L = NULL;
    pMochila bolsa = NULL;

    if(argc==1) {
        printf ("Argumentos insuficientes. Informe o nome do arquivo.");
        exit(1);  
    } 

    printf ("Informe o numero de itens da Loja: \n");
    scanf ("%d", &qtditens);

    printf ("Informe a capacidade da mochila: \n");
    scanf ("%f", &cap);

    CriarMochila(&bolsa, cap);
    CriarLoja(&L, qtditens);

    arq = fopen(argv[1], "rt");
    
    if (!arq) {
        printf("Problemas na abertura do arquivo\n");
        exit(1);
    }

    while(!feof(arq)) {
        
        fgets(line, sizeof line, arq); //recebe linha do arquivo 
        tmp1 = strdup(removeQuebra(line)); // remove quebra de linha
        printf("Armazenando novo item... \n");
        tmp = strtok(tmp1, delim); //obtem primeiro elemento do arquivo
        
        while( tmp != NULL ) {
            campos[i] = tmp; // armazena elemento no array
            tmp = strtok(NULL, delim); //obtem proximo elemento
            i++;
        }
    }
    
    
    // Adiciona na Loja o array de pares valor/peso
    for(int j=0;j<i;j++) {

        AddLoja(L, j, atof(campos[j]), atof(campos[j+1]));
        j++;
    }

    ImprimeLoja(L);
    
    fclose(arq);
}

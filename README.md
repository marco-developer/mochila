# Introdução
Este trabalho foi desenvolvido por Danilo, Douglas, Marco e Marcos, para a atividade Trabalho Final, da disciplina PAA - Projeto e Análise de Algoritmos, do primeiro semestre de 2021, e tem como objetivo o desenvolvimento de um TDA que implemente uma resolução utilizando algoritmo guloso para o problema da Mochila Fracionária.

O trabalho é composto pelos seguintes arquivos:

- main.c: Aplicação desenvolvida para executar a solução proposta.
- mochila.c: Arquivo .c contendo os códigos das funções do TDA.
- mochila_privada.h: Header contendo os structs e funções privadas do TDA.
- mochila_publica.h: Header contendo as funções públicas do TDA.
- arquivos .txt: Três arquivos .txt contendo tamanhos de entrada diferentes para a execução da aplicação.

O problema da mochila fracionária envolve uma situação hipotética, na qual há uma loja que contém determinado conjunto de itens. Um ladrão possui uma mochila que pode carregar um peso menor que o disponível na loja. Assim, a questão proposta é: Com quais itens e seus respectivos pesos o ladrão deve preencher a mochila, de modo a maximizar o lucro?

Para solução do problema, foram criados três tipos de dados: Item, Loja e Mochila, conforme abaixo:

```
struct item{
    int idItem;
    float peso;
    float valor;
    float cb;

};

typedef struct Loja{
    
    float CapacidadeTotal;
    float CapacidadeDisponivel;
    float PesoTotal;
    int posicao;

    item *conteudo[MAXLOJA];
}Loja;

typedef struct Mochila{
    
    float CapacidadeTotal;
    float CapacidadeDisponivel;
    int posicao;

    item *conteudo[MAXLOJA];
}Mochila;
```


# Main
A aplicação main deve ser executada da seguinte forma:
  ./main \<arquivo de entrada> \<tipo de ordenação> \<modo debug>
 
sendo:
  - \<arquivo de entrada>: arquivo de entrada contendo os itens a serem carregados na loja e utilizados durante a execução. Cada linha do arquivo representa um item, sendo composta por:
    - \<id do item>,\<peso do item>,\<valor total>
  - \<tipo de ordenação>: permite a seleção do tipo de ordenação a ser utilizada durante a execução, podendo ser:
    - 0: Utiliza o método QuickSort
    - 1: Utiliza o método BubbleSort
  - \<modo debug>: exibe ou omite mensagens de debug, podendo ser:
    - 0: Exibe debug
    - 1: Omite debug

# Mochila.c
Contém os códigos do TDA Mochila, com as seguintes funções:

## CriarMochila
## CriarLoja

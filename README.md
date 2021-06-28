# Introdução
Este trabalho foi desenvolvido por Danilo, Douglas, Marco e Marcos, para a atividade Trabalho Final, da disciplina PAA - Projeto e Análise de Algoritmos, do primeiro semestre de 2021, e tem como objetivo o desenvolvimento de um TDA que implemente uma resolução utilizando algoritmo guloso para o problema da Mochila Fracionária.

O trabalho é composto pelos seguintes arquivos:

- main.c: Aplicação desenvolvida para executar a solução proposta.
- mochila.c: Arquivo .c contendo os códigos das funções do TDA.
- mochila_privada.h: Header contendo os structs e funções privadas do TDA.
- mochila_publica.h: Header contendo as funções públicas do TDA.
- arquivos .txt: Três arquivos .txt contendo tamanhos de entrada diferentes para a execução da aplicação.

O problema da mochila fracionária envolve uma situação hipotética, na qual há uma loja que contém determinado conjunto de itens. Um ladrão possui uma mochila que pode carregar um peso menor que o disponível na loja. Assim, a questão proposta é: Com quais itens e seus respectivos pesos o ladrão deve preencher a mochila, de modo a maximizar o lucro?

Para solução do problema, deve-se ordenar os itens disponíveis na loja, em ordem decrescente de \<peso>/\<valor> e, utilizando uma abordagem gulosa, preencher a mochila com o maior peso possível dos itens com maior \<peso>/\<valor>. 

## Implementação

A implementação envolveu a criação de três tipos de dados: Item, Loja e Mochila, conforme abaixo:

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

Os tipos de dados Mochila e Loja são similares, tendo como diferencial o campo PesoTotal, presente no header na Loja, que indica o peso total dos itens que esta contém. O armazenamento dos itens é feito em um vetor conteudo, de tamanho máximo pré definido por meio da constante MAXLOJA, presente no arquivo mochila_publica.h.

O tipo de dado item representa o item, e possui os campos \<id do item>, \<peso do item> e \<valor total>, além de um campo \<cb>, que representa o custo benefício do item, dado por \<valor>/\<peso inicial>.

O primeiro passo da execução envolve a criação da Lojaseguida da coleta das informações contidas no arquivo de entrada, com as quais são criados três vetores: valor, qtd_inicial e id.

Após a criação dos vetores, é realizado um laço for, para adicionar os itens coletados à Loja:

```
    for(int j=0;j<i;j++) {
        AddLoja(L, id[i], valor[j], qtd_inicial[j], Exibe);
    }
```

Em seguida é realizada a criação da Mochila, seguida da ordenação decrescente do vetor de itens da Loja, considerando o campo \<cb>, utilizando a função BubbleSortLoja ou QuickSortLoja.

Por fim, a função CarregaMochila avalia a capacidade disponível na mochila, preenchendo-a com os itens de maior \<cb> da Loja, até que a capacidade da mochila seja igual a 0.

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

- int CriarMochila(pMochila \*M, pLoja L, float proporcao, int Exibe): Cria mochila M, com base nos itens existentes na loja L. A mochila tem tamanho igual ao tamanho da loja multiplicado pelo parâmetro proporcao.

- int CriarLoja(pLoja \*L, float CapacidadeLoja, int Exibe): Cria loja L, com capacidade dada pelo parâmetro CapacidadeLoja.

- int AddLoja(pLoja L, int ID, float valor, float peso, int Exibe): Adiciona à loja L novo idem com os dados ID, valor e peso informados.

- int ImprimeLoja(pLoja L): Imprime os itens e suas respectivas informações, presentes na loja L.
 
- int ImprimeMochila(pMochila M): Imprime os itens e suas respectivas informações, presentes na mochila M.

- int quicksort_r(pLoja L, int start, int end): Ordena a loja L utilizando o algoritmo quicksort, utilizando os parâmetros início e fim.

- int bubblesort(pLoja L): Ordena a loja L utilizando o algoritmo BubbleSort.

- int QuickSortLoja(pLoja L, int Exibe): Chama a execução da ordenação da loja L, utilizando o algoritmo QuickSort.

- int BubbleSortLoja(pLoja L, int Exibe): Chama a execução da ordenação da loja L, utilizando o algoritmo BubbleSort.

- int CarregaMochila(pMochila M, pLoja L, int Exibe): Executa a função gulosa, que carrega a mochila com os itens de maior \<cb> presentes na loja L.

- int DestruirMochila(pMochila M, int Exibe): Desaloca a memória referente aos itens e à mochila M.

- int DestruirLoja(pLoja L, int Exibe): Desaloca a memória referente aos itens e à loja L.

# Introdução
Este trabalho foi desenvolvido para a atividade Trabalho Final, da disciplina PAA - Projeto e Análise de Algoritmos, do primeiro semestre de 2021, e tem como objetivo o desenvolvimento de um TDA que implemente uma resolução utilizando algoritmo guloso para o problema da Mochila Fracionária.

O trabalho é composto pelos seguintes arquivos:

- main.c: Aplicação desenvolvida para executar a solução proposta.
- mochila.c: Arquivo .c contendo os códigos das funções do TDA.
- mochila_privada.h: Header contendo os structs e funções privadas do TDA.
- mochila_publica.h: Header contendo as funções públicas do TDA.
- arquivos .txt: Três arquivos .txt contendo tamanhos de entrada diferentes para a execução da aplicação.

# Main
A aplicação main deve ser executada da seguinte forma:
  ./main <arquivo de entrada> <tipo de ordenação> <modo debug>
 
sendo:
  - <arquivo de entrada>: arquivo de entrada contendo os itens a serem carregados na loja e utilizados durante a execução. Cada linha do arquivo representa um item, sendo composta por:
    - <id do item>,<peso do item>,<valor total>
  - <tipo de ordenação>: permite a seleção do tipo de ordenação a ser utilizada durante a execução, podendo ser:
    - 0: Utiliza o método QuickSort
    - 1: Utiliza o método BubbleSort
  - <modo debug>: exibe ou omite mensagens de debug, podendo ser:
    - 0: Exibe debug
    - 1: Omite debug

# Mochila.c

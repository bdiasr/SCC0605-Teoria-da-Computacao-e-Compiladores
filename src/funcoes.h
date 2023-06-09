#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef FUNCOES_H
#define FUNCOES_H

#define NUM_SIMBOLOS 30 //numero fixo de simbolos na tabela de simbolos
#define TAM 10000 //tamanho maximo da lista inicial de caracteres

//estrutura da lista de tokens e simbolos
struct elemento{
    char simbolo[20];
    char token[20];
};

typedef struct elemento* elem;


/**
 * @brief verifica se caractere corresponde a um numero
 * 
 * @param x 
 * @return true 
 * @return false 
 */
bool numero(char x);

/**
 * @brief verifica se caractere corresponde a uma letra
 * 
 * @param x 
 * @return true 
 * @return false 
 */
bool letra(char x);

/**
 * @brief Limpa o arquivo e saida
 * 
 */
void limpa_saida();

/**
 * @brief Escreve no arquivo de saida o par simbolo, token correspondente 
 * 
 * @param simbolo 
 * @param token 
 */
void printa_saida(char* simbolo, char* token);

/**
 * @brief Funcao auxiliar que transforma o char* palavra em caixa baixa, facilitando as comparacoes. 
 * 
 * @param palavra 
 * @return char* 
 */
char* caixa_baixa(char* palavra);

/**
 * @brief percorre a lista de palavras reconhecidas, retornando o token caso encontrada. 
 * 
 * @param palavra 
 * @param lista_simbolos 
 * @return char* 
 */
char* busca_palavra_reconhecida(char* palavra, elem lista_simbolos);

/**
 * @brief Criacao da lista de caracteres de entrada. 
 * 
 * @return char* 
 */
char* cria_lista_caracteres();

/**
 * @brief preenche a lista de simbolo-token. 
 * 
 * @param file 
 * @return struct elemento 
 */
struct elemento preenche_simbolos(FILE* file);

/**
 * @brief Cria a lista de simbolo-token. 
 * 
 * @return elem 
 */
elem cria_lista_simbolos();

#endif 
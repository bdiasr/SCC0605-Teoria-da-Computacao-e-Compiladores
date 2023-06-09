#ifndef AUTOMATOS_H
#define AUTOMATOS_H

#include "funcoes.h"

/**
 * @brief automato reconhecedor de palavras reservadas e identificadores
 * 
 * @param lista 
 * @param pos 
 * @param list_simbolos 
 * @return int 
 */
int automato1(char* lista, int pos, elem list_simbolos);

/**
 * @brief Automato reconhecedor de numeros 
 * 
 * @param lista 
 * @param pos 
 * @return int 
 */
int automato2(char* lista, int pos);

/**
 * @brief automato reconhecedor de simbolos unitarios
 * 
 * @param lista 
 * @param pos 
 * @param list_simbolos 
 * @return int 
 */
int automato3(char* lista, int pos, elem list_simbolos);

/**
 * @brief automato reconhecedor de comparacoes
 * 
 * @param lista 
 * @param pos 
 * @param list_simbolos 
 * @return int 
 */
int automato4(char* lista, int pos, struct elemento* list_simbolos);

/**
 * @brief automato reconhecedor de atribuicoes
 * 
 * @param lista 
 * @param pos 
 * @return int 
 */
int automato5(char* lista, int pos);

/**
 * @brief automato reconhecedor de cometarios.
 * 
 * @param lista 
 * @param pos 
 * @return int 
 */
int automato6(char* lista, int pos);


/**
 * @brief funcao do analisador lexico, define posicao inicial de analise como inicio da lista de caracteres, 
 * acionando os automatos reconhecedores, incrementando posicao na lista se ha sucesso de reconhecimento. 
 * Se nao for reconhecido por nenhum automato, retorna erro de leitura do caractere. 
 * 
 * @param lista 
 * @param lista_s 
 */
void analisador (char* lista, elem lista_s); 

#endif 
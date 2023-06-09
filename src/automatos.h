#ifndef AUTOMATOS_H
#define AUTOMATOS_H

#include "funcoes.h"

/*
* automato reconhecedor de palavras reservadas e identificadores
*/
int automato1(char* lista, int pos, elem list_simbolos);

/*
* Automato reconhecedor de numeros 
*/
int automato2(char* lista, int pos);

/*
* automato reconhecedor de simbolos unitarios
*/
int automato3(char* lista, int pos, elem list_simbolos);

/*
* automato reconhecedor de comparacoes
*/
int automato4(char* lista, int pos);

/*
* automato reconhecedor de atribuicoes
*/
int automato5(char* lista, int pos);

/*
* automato reconhecedor de cometarios
*/
int automato6(char* lista, int pos);

void analisador (char* lista, elem lista_s); 

#endif 
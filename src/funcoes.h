#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef FUNCOES_H
#define FUNCOES_H

#define NUM_SIMBOLOS 27 //numero fixo de simbolos na tabela de simbolos
#define TAM 1000 //tamanho maximo da lista inicial de caracteres

//estrutura da lista de tokens e simbolos
struct elemento{
    char simbolo[20];
    char token[20];
};

typedef struct elemento* elem;

bool numero(char x);
bool letra(char x);

void limpa_saida();
void printa_saida(char* simbolo, char* token);
char* caixa_baixa(char* palavra);
char* busca_palavra_reconhecida(char* palavra, elem lista_simbolos);
char* cria_lista_caracteres();
struct elemento preenche_simbolos(FILE* file);
elem cria_lista_simbolos();

/*
int automato1(char* lista, int pos, elem list_simbolos);
int automato2(char* lista, int pos);
int automato3(char* lista, int pos, elem list_simbolos);
int automato4(char* lista, int pos);
int automato5(char* lista, int pos);
int automato6(char* lista, int pos);
*/

#endif 
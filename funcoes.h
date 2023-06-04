#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "automatos.h" 

#define TAM 1000

typedef char Dado[20];

//estrutura da lista de tokens e simbolos
struct elemento{
    char simbolo[20];
    char token[20];
    struct elemento *prox;
};

typedef struct elemento elem;
typedef struct elemento* Lista;



bool numero(char x);
bool letra(char x);

char* cria_lista_caracteres();

Lista* cria_lista();
void imprime_lista(Lista* li);
Lista* cria_lista_simbolos();

//void analisador (char* lista, elem* lista_s);
//char* busca_palavra_reconhecida(char* palavra, elem* lista_simbolos);


void lista_caracteres(FILE* arq );

//int insere_lista_ordenada(Lista* li, Tipo_Dado dt);
int isSpecialChar(char c); 
void printWords(char** words, int numWords); 
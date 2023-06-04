#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM 1000

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

//Lista* cria_lista_caracteres();

Lista* cria_lista();
void imprime_lista(Lista* li);


//elem* cria_lista_simbolos();
//void analisador (char* lista, elem* lista_s);
//char* busca_palavra_reconhecida(char* palavra, elem* lista_simbolos);

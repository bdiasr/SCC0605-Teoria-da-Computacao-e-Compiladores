#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"
#include "automatos.h"


//funcao principal
int main(int argc, char*argv[]){
    int p;

    //cria lista de caracteres do arquivo
    Lista* lista_entrada = cria_lista();
    //cria_lista_caracteres();
    imprime_lista(lista_entrada);

    //cria e preenche lista de simbolos
    //Lista* lista_simbolos = cria_lista_simbolos();
    //lista_simbolos  = (elem*) malloc(sizeof(elem));
    
    //imprime_lista(lista_simbolos);

    //chama analisador para o programa lido
    //analisador(lista_entrada,lista_simbolos);

    //libera memoria
    free(lista_entrada);
    //free(lista_simbolos);

    //finaliza execucao
    return 0;

}

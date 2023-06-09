#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "automatos.h"

//funcao principal
int main(int argc, char*argv[]){

    //cria lista de caracteres do arquivo
    char* lista_caracteres = cria_lista_caracteres();

    //cria e preenche lista de simbolos
    elem lista_simbolos = cria_lista_simbolos();

    //limpa saida
    limpa_saida();
    //chama analisador para o programa lido
    analisador(lista_caracteres,lista_simbolos);

    //libera memoria
    free(lista_caracteres);
    free(lista_simbolos);

    //finaliza execucao
    return 0;

}


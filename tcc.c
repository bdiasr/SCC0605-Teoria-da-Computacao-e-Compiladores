#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"
#include "automatos.h"


//funcao principal
int main(int argc, char*argv[]){
    int p;

    //abrir arquivo txt de entrada
    FILE *prog_inicial;
    prog_inicial = fopen("meu_programa.txt", "r");
    if(prog_inicial == NULL){
        printf("erro no arquivo de entrada!\n");
        exit(1);
    }
    //cria lista de caracteres do arquivo
    lista_caracteres(prog_inicial);

    //for (int i =0; sizeof(lista_entrada)> i; i++){
        //printf("%s", lista_entrada[i]);
    //}

    //cria e preenche lista de simbolos
    //Lista* lista_simbolos = cria_lista_simbolos();
    //lista_simbolos  = (elem*) malloc(sizeof(elem));
    
    //imprime_lista(lista_simbolos);

    //chama analisador para o programa lido
    //analisador(lista_entrada,lista_simbolos);

    //libera memoria
    //free(lista_entrada);
    //free(lista_simbolos);

    //finaliza execucao
    return 0;

}

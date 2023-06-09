#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"
#include "automatos.h"

//analisador lexico
void analisador (char* lista, elem lista_s){ //recebe lista de caracteres e de simbolos

    //define posicao inicial de analise como inicio da lista de caracteres
    int pos = 0;
    
    //percorre lista de caracteres
    while(lista[pos]!='\0'){
        
        //ignorando caracteres iniciais da cadeia se forem espaco ou quebra de linha
        while(lista[pos]==' ' || lista[pos]=='\n'){
            pos++;
        }
        int pos_init = pos; //marca posicao do caractere atual

        //acionar automatos reconhecedores, incrementando posicao na lista se ha sucesso de reconhecimento
        pos = automato1(lista, pos, lista_s);
        pos = automato2(lista, pos);
        pos = automato3(lista, pos, lista_s);
        pos = automato4(lista, pos);
        pos = automato5(lista, pos);
        pos = automato6(lista, pos);

        //se caractere nao reconhecido por nenhum automato
        if(pos == pos_init){
            if(lista[pos+1]!='\0'){ //se nao eh o caractere de fim de arquivo

                //retorna erro de leitura do caractere
                char erro[2];
                erro[0] = lista[pos];
                erro[1] = '\0';
                printa_saida(erro,"erro('caractere nao permitido')\n");
            }
            pos++;
        }

    }
    
}



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
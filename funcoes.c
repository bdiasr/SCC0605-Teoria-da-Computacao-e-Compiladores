#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"
#include "automatos.h"


//verifica se caractere corresponde a um numero
bool numero(char x){
    if(x>47 && x<58){
        return true;
    }
    return false;
}

//verifica se caractere corresponde a uma letra
bool letra(char x){
    if(x<65 || (x>90 && x<97) || x>122){
        return false;
    }
    return true;
}

/*
char* busca_palavra_reconhecida(char* palavra, elem* lista_simbolos){

    int i;
    //percorre a lista de palavras reconhecidas
    for (i = 0;i<29;i++){
        
        if(strcmp(palavra,lista_simbolos[i].simbolo)==0){//se encontrar simbolo igual, retorna token
            return lista_simbolos[i].token;
        }
    }
    return "id"; //se nao encontrou simbolo igual, retorna que eh um id
}
*/


//cria e preenche lista de caracteres de entrada
char* cria_lista_caracteres(){

    char* lista = (char*) malloc (TAM*sizeof(char));

    int i;
    for(i = 0;i<TAM;i++){
        lista[i] = '\0';
    }

    //abrir arquivo txt de entrada
    FILE *prog_inicial;
    prog_inicial = fopen("meu_programa.txt", "r");
    if(prog_inicial == NULL){
        printf("erro no arquivo de entrada!\n");
        exit(1);
    }

    //le cada caractere do arquivo de entrada
    while(!feof(prog_inicial)){
        char p = fgetc(prog_inicial);
        int i;

        if(p!='\t' && p!=feof(prog_inicial)){
            
            for(i = 0;i<TAM;i++){
                if(lista[i]=='\0'){
                    lista[i] = p;
                    break;
                }
            
            }
        }
    }
    fclose(prog_inicial);
    return lista;
}


/*
elem* cria_lista_simbolos(){

    //abrir tabela de simbolos
    FILE *list_s;
    list_s = fopen("tabela_simbolos.txt", "r");
    if(list_s == NULL){
        printf("erro na tabela de simbolos!\n");
        exit(1);
    }

    elem *no = (elem*) malloc(sizeof(elem));
    elem* lista = (elem*) malloc (28*sizeof(elem));
    //elem no;
    char simbolo[20];
    char token[20];
    int i = 0;

    while(fscanf(list_s,"%[^|]%*c ",simbolo)==1){
        fscanf(list_s,"%[^\n]%*c ",token);

        strcpy(no[i].simbolo,simbolo);
        strcpy(no[i].token,token);

        //lista = *no;
        i++;
        
    }

    fclose(list_s);
    return lista;
}
*/
/*
//analisador lexico
void analisador (char* lista, elem* lista_s){ //recebe lista de caracteres e de simbolos

    //abrir arquivo txt de saida
    FILE *saida;
    saida = fopen("saida.txt", "a+");
    if(saida == NULL){
        printf("erro no arquivo de saida!\n");
        exit(1);
    }

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
        pos = automato1(lista, pos, lista_s, saida);
        pos = automato2(lista, pos, saida);
        pos = automato3(lista, pos, lista_s, saida);
        pos = automato4(lista, pos, lista_s, saida);
        pos = automato5(lista, pos, lista_s, saida);
        pos = automato6(lista, pos, saida);

        //se caractere nao reconhecido por nenhum automato
        if(pos == pos_init){
            if(lista[pos+1]!='\0'){ //se nao eh o caractere de fim de arquivo

                //retorna erro de leitura do caractere
                char erro[2];
                erro[0] = lista[pos];
                erro[1] = '\0';
                fprintf(saida,erro);
                fprintf(saida,", ");
                fprintf(saida,"erro('caractere nao permitido\n')");

            }
            pos++;
        }

    }
    
    //fecha arquivo txt de saida
    fclose(saida);
}
*/

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    elem* no = *li;
    while(no != NULL){
        printf("Dado: %s\n",no->dado);
        no = no->prox;
    }
    printf("-------------- FIM LISTA -----------------\n");
}


Lista* cria_lista(){
    Lista* li;
    li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}
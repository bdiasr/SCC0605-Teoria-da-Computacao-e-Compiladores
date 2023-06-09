#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"
#include "automatos.h"

void limpa_saida(){

    //abrir arquivo txt de saida com w+
    FILE *saida;
    saida = fopen("saida.txt", "w+");
    if(saida == NULL){
        printf("erro no arquivo de saida!\n");
        exit(1);
    }
    //fecha arquivo txt de saida
    fclose(saida);
}

void printa_saida(char* simbolo, char* token){

    //abrir arquivo txt de saida
    FILE *saida;
    saida = fopen("saida.txt", "a+");
    if(saida == NULL){
        printf("erro no arquivo de saida!\n");
        exit(1);
    }

    fprintf(saida,simbolo);
    fprintf(saida,", ");
    fprintf(saida,token);

    //fecha arquivo txt de saida
    fclose(saida);
}

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

//função que coloca as palavras em caixa alta para facilitar comparações
char* caixa_baixa(char* palavra){
    int i;

    for(i = 0; palavra[i]!= '\0'; i++){
        if(palavra[i] >= 'A' && palavra[i] <= 'Z'){
            palavra[i] = palavra[i] + 32;
        }
    }
    return palavra;

}

char* busca_palavra_reconhecida(char* palavra, elem lista_simbolos){

    //percorre a lista de palavras reconhecidas
    for (int i = 0;i<NUM_SIMBOLOS;i++){
        
        if(strcmp(caixa_baixa(palavra),lista_simbolos[i].simbolo)==0){//se encontrar simbolo igual, retorna token
            return lista_simbolos[i].token;
        }
    }
    return "id"; //se nao encontrou simbolo igual, retorna que eh um id
}


//cria e preenche lista de caracteres de entrada
char* cria_lista_caracteres(){
    char* lista = (char*) malloc (TAM*sizeof(char));
    for(int i = 0;i<TAM;i++){
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
        if(p!='\t' && p!=feof(prog_inicial)){
            for(int i = 0;i<TAM;i++){
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

struct elemento preenche_simbolos(FILE* file){

    char linha[50];
    struct elemento no;
    char simbolo[20];
    char token[20];
    long int tam = ftell(file);
      
    fscanf(file, "%[^\n]%*c ", linha);

    if(tam<399){
        int k = 0;
        int i = 0;
        while(linha[i]!='|'){
            simbolo[k] = linha[i];
            k++;
            i++;           
        }
        simbolo[k] = '\0';
        
        k = 0;
        i++;
        while(linha[i]!='\n' && linha[i]!='\0'){
            token[k] = linha[i];
            k++;
            i++;
        }
        token[k] = '\0';
          
        strcpy(no.simbolo, simbolo);
        strcpy(no.token, token);  
    }
    else{
        strcpy(no.simbolo, "\0");
        strcpy(no.token, "\0");
    }

    return no; 

}

elem cria_lista_simbolos(){

    //abrir tabela de simbolos
    FILE *list_s;
    list_s = fopen("tab_simb.txt", "a+");
    if(list_s == NULL){
        printf("erro na tabela de simbolos!\n");
        exit(1);
    }

    
    elem lista = (elem) malloc (NUM_SIMBOLOS*sizeof(struct elemento));
    
    for(int i = 0;i<NUM_SIMBOLOS;i++){
        lista[i] = preenche_simbolos(list_s);
    }
    
    
    fclose(list_s);
    return lista;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"
#include "automatos.h"

/*
//automato reconhecedor de palavras reservadas e identificadores
int automato1(char* lista, int pos, elem* list_simbolos,FILE *saida){

    char palavra[30];
    palavra[0] = lista[pos];

    //verifica se primeiro caractere eh letra, se nao, nao eh reconhecido por esse automato
    if(letra(palavra[0])==false){
        return pos;
    }

    //lendo toda a palavra
    pos++;
    int j = 1;
    int i;
    for(i=pos;numero(lista[i])==true || letra(lista[i])==true;i++){ //enquanto for letra ou numero
        palavra[j] = lista[i];
        j++;
    }
    //finaliza palavra e salva posicao final
    palavra[j]='\0'; 
    pos = i;

    //busca na lista de palavras reconhecidas
    char result[20];
    strcpy(result,busca_palavra_reconhecida(palavra,list_simbolos));
    strcat(result,"\n");

    //escreve resultado no arquivo
    fprintf(saida,palavra);
    fprintf(saida,", ");
    fprintf(saida,result);

    //retorna posicao atual
    return pos;
}

//automato reconhecedor de numeros
int automato2(char* lista, int pos,FILE *saida){

    //ignorando caracteres iniciais da cadeia se forem espaco ou quebra de linha
    char palavra[30];
    while(lista[pos]==' ' || lista[pos]=='\n'){
        pos++;
    }
    palavra[0] = lista[pos];

    //verifica se primeiro caractere eh numero, se nao, nao eh reconhecido por esse automato
    if(numero(palavra[0])==false){
        return pos;
    }

    //lendo todo o numero
    pos++;
    int j = 1;
    while(true){
        //enquanto o simbolo lido for numero, continua neste estado
        if(numero(lista[pos])==true){
            palavra[j] = lista[pos];
            pos++;
            j++;
            continue;
        }
        //se ler virgula, e se ha garantia de que depois da virgula ha outro numero, so pode ser real
        //portanto, continua lendo os numeros ate encontrar outro caractere e retorna numero real
        else if(lista[pos]==',' && numero(lista[pos+1])==true){ 
            palavra[j] = lista[pos];
            pos++;
            j++;
            while(numero(lista[pos])==true){
                palavra[j] = lista[pos];
                pos++;
                j++;
            }
            palavra[j]='\0';
            //escreve resultado no arquivo
            fprintf(saida,palavra);
            fprintf(saida,", ");
            fprintf(saida,"num_real\n");
            return pos;
        }
        //se ler qualquer outro caractere ou se houver uma virgula nao seguida de numeros, retorna inteiro
        else{
            palavra[j]='\0';
            //escreve resultado no arquivo
            fprintf(saida,palavra);
            fprintf(saida,", ");
            fprintf(saida,"num_inteiro\n");
            return pos;
        }

    }

    return pos;
}

//automato reconhecedor de simbolos unitarios
int automato3(char* lista, int pos, elem* list_simbolos,FILE *saida){

    //ignorando caracteres iniciais da cadeia se forem espaco ou quebra de linha
    char simb[2];
    while(lista[pos]==' ' || lista[pos]=='\n'){
        pos++;
    }
    simb[0] = lista[pos];
    simb[1] = '\0';

    //se for numero, letra ou se nao estiver na lista de reservadas, nao pode ser um simbolo unitario
    if(simb[0]==':' || simb[0]=='>' || simb[0]=='<' || numero(simb[0])==true || letra(simb[0])==true || busca_palavra_reconhecida(simb,list_simbolos)=="id"){
        return pos;
    }

    pos++;
    char result[20];
    strcpy(result,busca_palavra_reconhecida(simb,list_simbolos));
    strcat(result,"\n");

    //escreve resultado no arquivo
    fprintf(saida,simb);
    fprintf(saida,", ");
    fprintf(saida,result);
    
    return pos;
}

//automato reconhecedor de comparacoes
int automato4(char* lista, int pos, elem* list_simbolos,FILE *saida){

    //ignorando caracteres iniciais da cadeia se forem espaco ou quebra de linha
    char simb[3];
    while(lista[pos]==' ' || lista[pos]=='\n'){
        pos++;
    }
    simb[0] = lista[pos];
    simb[2] = '\0';

    //se nao iniciar com maior ou menor, nao eh comparacao
    if(simb[0]!='>' && simb[0]!='<' ){
        return pos;
    }

    char result[20];

    if(simb[0]=='>'){
        if(lista[pos+1]=='='){
            pos++;
            simb[1] = '=';
            strcpy(result, "simb_maiorig\n");
        }
        else{
            simb[1] = '\0';
            strcpy(result, "simb_maior\n");
        }
    }
    else{
        if(lista[pos+1]=='='){
            pos++;
            simb[1] = '=';
            strcpy(result, "simb_menorig\n");
        }
        else if(lista[pos+1]=='>'){
            pos++;
            simb[1] = '>';
            strcpy(result, "simb_diff\n");
        }
        else{
            simb[1] = '\0';
            strcpy(result, "simb_menor\n");
        }

    }

    pos++;

    //escreve resultado no arquivo
    fprintf(saida,simb);
    fprintf(saida,", ");
    fprintf(saida,result);
    
    return pos;
}

//automato reconhecedor de atribuicoes
int automato5(char* lista, int pos, elem* list_simbolos,FILE *saida){

    //ignorando caracteres iniciais da cadeia se forem espaco ou quebra de linha
    char simb[3];
    while(lista[pos]==' ' || lista[pos]=='\n'){
        pos++;
    }
    simb[0] = lista[pos];
    simb[2] = '\0';

    //se nao iniciar com maior ou menor, nao eh comparacao
    if(simb[0]!=':'){
        return pos;
    }

    char result[20];


    if(lista[pos+1]=='='){
        pos++;
        simb[1] = '=';
        strcpy(result, "simb_atrib\n");
    }
    else{
        simb[1] = '\0';
        strcpy(result, "simb_dp\n");
    }

    pos++;

    //escreve resultado no arquivo
    fprintf(saida,simb);
    fprintf(saida,", ");
    fprintf(saida,result);
    
    return pos;
}

//automato reconhecedor de comentarios
int automato6(char* lista, int pos,FILE *saida){

    //ignorando caracteres iniciais da cadeia se forem espaco ou quebra de linha
    char palavra[50];
    while(lista[pos]==' ' || lista[pos]=='\n'){
        pos++;
    }
    palavra[0] = lista[pos];

    //se nao iniciar {, nao eh comentario
    if(palavra[0]!='{'){
        return pos;
    }

    char result[50];

    int j = 1;
    pos++;
    while(true){
        if(palavra[pos]=='\n'){
            strcpy(result,"erro: conjunto de caracteres nao reconhecido\n");

            //escreve resultado no arquivo
            fprintf(saida,palavra);
            fprintf(saida,", ");
            fprintf(saida,result);

            return pos;
        }
        else if (palavra[pos]=='}'){
            palavra[j] = lista[pos];
            strcpy(result,"comment\n");

            //escreve resultado no arquivo
            fprintf(saida,palavra);
            fprintf(saida,", ");
            fprintf(saida,result);

            return pos;
        }
        else{
            palavra[j] = lista[pos];
            j++;
            pos++;
        }
    }
    
}

*/
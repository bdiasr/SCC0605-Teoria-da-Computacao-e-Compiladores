#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
        pos = automato4(lista, pos,lista_s);
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

//automato reconhecedor de palavras reservadas e identificadores
int automato1(char* lista, int pos, elem list_simbolos){

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
    printa_saida(palavra,result);

    //retorna posicao atual
    return pos;
}

/*
* automato reconhecedor de numeros
*/
int automato2(char* lista, int pos){

    char msg_erro[30];
    strcpy(msg_erro,"erro: numero mal formatado\n");

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
        //enquanto o simbolo lido for numero, continua neste estado (q1)
        if(numero(lista[pos])==true){
            palavra[j] = lista[pos];
            pos++;
            j++;
            continue;
        }
        //se o simbolo lido for letra, vai para o estado intermediario de erro (q6)
        else if(letra(lista[pos])==true){
            do{
                palavra[j] = lista[pos];
                pos++;
                j++;
            }
            while(letra(lista[pos])==true || numero(lista[pos])==true);

            //vai para o estado final de erro (q7)
            palavra[j] = '\0';
            printa_saida(palavra, msg_erro);
            return pos+1;
        }
        //se ler ponto, vai para o estado intermediario dos reais (q3)
        else if(lista[pos]=='.'){ 
            palavra[j] = lista[pos];
            pos++;
            j++;
            //se o simbolo lido for letra, vai para o estado intermediario de erro (q6)
            if(letra(lista[pos])==true){
                do{
                    palavra[j] = lista[pos];
                    pos++;
                    j++;
                }
                while(letra(lista[pos])==true || numero(lista[pos])==true);

                //vai para o estado final de erro (q7)
                palavra[j] = '\0';
                printa_saida(palavra, msg_erro);
                return pos+1;
                }
            
            //enquanto le digitos, fica no estado q4
            while(numero(lista[pos])==true){
                palavra[j] = lista[pos];
                pos++;
                j++;
            }

            if(letra(lista[pos])==true){
                do{
                    palavra[j] = lista[pos];
                    pos++;
                    j++;
                }
                while(letra(lista[pos])==true || numero(lista[pos])==true);

                //vai para o estado final de erro (q7)
                palavra[j] = '\0';
                printa_saida(palavra, msg_erro);
                return pos+1;
            }

            palavra[j]='\0';
            //escreve resultado no arquivo
            printa_saida(palavra, "num_real\n");
            return pos;
        }
        //se ler qualquer outro caractere, vai para o estado final inteiro (q2)
        else{
            palavra[j]='\0';
            //escreve resultado no arquivo
            printa_saida(palavra, "num_inteiro\n");
            return pos;
        }
    }
    return pos;
}

//automato reconhecedor de simbolos unitarios
int automato3(char* lista, int pos, elem list_simbolos){

    //ignorando caracteres iniciais da cadeia se forem espaco ou quebra de linha
    char simb[2];
    while(lista[pos]==' ' || lista[pos]=='\n'){
        pos++;
    }
    simb[0] = lista[pos];
    simb[1] = '\0';

    //se for numero, letra ou se nao estiver na lista de reservadas, nao pode ser um simbolo unitario
    if(simb[0]==':' || simb[0]=='>' || simb[0]=='<' || simb[0]=='=' || numero(simb[0])==true || letra(simb[0])==true || 
    strcmp(busca_palavra_reconhecida(simb,list_simbolos), "id")== 0){
        return pos;
    }

    pos++;
    char result[20];
    strcpy(result,busca_palavra_reconhecida(simb,list_simbolos));
    strcat(result,"\n");

    //escreve resultado no arquivo
    printa_saida(simb,result);
    
    return pos;
}

//automato reconhecedor de comparacoes
int automato4(char* lista, int pos, struct elemento* list_simbolos){
    //ignorando caracteres iniciais da cadeia se forem espaco ou quebra de linha
    char simb[3];
    while(lista[pos]==' ' || lista[pos]=='\n'){
        pos++;
    }
    simb[0] = lista[pos];
    simb[1] = lista[pos+1];
    simb[2] = '\0';

    //se nao iniciar com maior ou menor, nao eh comparacao
    if(simb[0]!='>' && simb[0]!='<' && simb[0]!='='){
        return pos;
    }
    else if(simb[1]!='=' && simb[1]!='>'){
        simb[1] = '\0';
        pos--;
    }

    pos+=2;
    char result[20];
    strcpy(result,busca_palavra_reconhecida(simb,list_simbolos));
    strcat(result,"\n");

    //escreve resultado no arquivo
    printa_saida(simb,result);
    
    return pos;
    
}

//automato reconhecedor de atribuicoes
int automato5(char* lista, int pos){

    char simb[3];
    char result[20];

    //ignorando caracteres iniciais da cadeia se forem espaco ou quebra de linha
    while(lista[pos]==' ' || lista[pos]=='\n'){
        pos++;
    }
    simb[0] = lista[pos];
    simb[2] = '\0';

    //se nao iniciar com :, nao eh atribuicao
    if(simb[0]!=':'){
        return pos;
    }

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
    printa_saida(simb,result);
    
    return pos;
}

//automato reconhecedor de comentarios
int automato6(char* lista, int pos){

    char palavra[50];

    //ignorando caracteres iniciais da cadeia se forem espaco ou quebra de linha
    while(lista[pos]==' ' || lista[pos]=='\n'){
        pos++;
    }

    //palavra inicial
    palavra[0] = lista[pos];

    //se a primeira letra for diferentes de chaves -> nao eh comentario
    if(palavra[0]!='{'){
        return pos;
    }

    char result[50];

    int j = 1;
    pos++;
    while(lista[pos]!='\n'){

        if (lista[pos]=='}'){
            palavra[j] = lista[pos];
            palavra[j+1] = '\0';

            strcpy(result,"comment\n");

            //escreve resultado no arquivo
            printa_saida(palavra, result);
            return pos+1;
        }
        else{
            palavra[j] = lista[pos];
            j++;
            pos++;
        }
    }
    palavra[j+1] = '\0';
    
    //deu erro!!
    strcpy(result,"erro: comentario nao finalizado\n");

    //escreve resultado no arquivo
    printa_saida(palavra, result);

    return pos;
    
}
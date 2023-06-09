#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "funcoes.h"

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


/*
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

//automato reconhecedor de numeros
int automato2(char* lista, int pos){

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
        else if(lista[pos]=='.' && numero(lista[pos+1])==true){ 
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
            printa_saida(palavra, "num_real\n");
            return pos;
        }
        //se ler qualquer outro caractere ou se houver uma virgula nao seguida de numeros, retorna inteiro
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
    if(simb[0]==':' || simb[0]=='>' || simb[0]=='<' || numero(simb[0])==true || letra(simb[0])==true || busca_palavra_reconhecida(simb,list_simbolos)=="id"){
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
int automato4(char* lista, int pos){

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
    printa_saida(simb,result);
    
    return pos;
}

//automato reconhecedor de atribuicoes
int automato5(char* lista, int pos){

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
    printa_saida(simb,result);
    
    return pos;
}

//automato reconhecedor de atribuicoes
int automato6(char* lista, int pos){

    //ignorando caracteres iniciais da cadeia se forem espaco ou quebra de linha
    char palavra[50];
    while(lista[pos]==' ' || lista[pos]=='\n'){
        pos++;
    }
    palavra[0] = lista[pos];

    //se nao iniciar com maior ou menor, nao eh comparacao
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
            printa_saida(palavra,result);
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
    printa_saida(palavra,result);

    return pos;
    
}


*/
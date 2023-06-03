#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"

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

char* busca_palavra_reconhecida(char* palavra, struct elemento* lista_simbolos){

    int i;
    //percorre a lista de palavras reconhecidas
    for (i = 0;i<29;i++){
        
        if(strcmp(palavra,lista_simbolos[i].simbolo)==0){//se encontrar simbolo igual, retorna token
            return lista_simbolos[i].token;
        }
    }
    return "id"; //se nao encontrou simbolo igual, retorna que eh um id
}


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

struct elemento preenche_simbolos(FILE* file){

    char linha[50];

    while(!feof(file)){
        
        fgets(linha,50,file);

        char simbolo[20];
        char token[20];

        int k = 0;
        int i=0;
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
        
        struct elemento no;
        strcpy(no.simbolo, simbolo);
        strcpy(no.token, token);
        return no;        
    }

}

struct elemento* cria_lista_simbolos(){

    //abrir tabela de simbolos
    FILE *list_s;
    list_s = fopen("tabela_simbolos.txt", "r");
    int i;
    if(list_s == NULL){
        printf("erro na tabela de simbolos!\n");
        exit(1);
    }

   struct elemento* lista = (struct elemento*) malloc (30*sizeof(struct elemento));
    for(i = 0;i<29;i++){
        lista[i] = preenche_simbolos(list_s);
    }
    
    
    fclose(list_s);
    return lista;
}

//automato reconhecedor de palavras reservadas e identificadores
int automato1(char* lista, int pos, struct elemento* list_simbolos,FILE *saida){

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
int automato3(char* lista, int pos, struct elemento* list_simbolos,FILE *saida){

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
int automato4(char* lista, int pos, struct elemento* list_simbolos,FILE *saida){

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
int automato5(char* lista, int pos, struct elemento* list_simbolos,FILE *saida){

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

//automato reconhecedor de atribuicoes
int automato6(char* lista, int pos,FILE *saida){

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

//analisador lexico
void analisador (char* lista, struct elemento* lista_s){ //recebe lista de caracteres e de simbolos

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



//funcao principal
int main(int argc, char*argv[]){

    //cria lista de caracteres do arquivo
    char* lista_caracteres = cria_lista_caracteres();

    //cria e preenche lista de simbolos
    struct elemento* lista_simbolos = cria_lista_simbolos();

    //chama analisador para o programa lido
    analisador(lista_caracteres,lista_simbolos);

    //libera memoria
    free(lista_caracteres);
    free(lista_simbolos);

    //finaliza execucao
    return 0;

}
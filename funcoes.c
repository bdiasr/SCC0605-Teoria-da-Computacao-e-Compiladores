#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "funcoes.h"
#include "automatos.h"


#define MAX_SIZE 100

int isSpecialChar(char c) {
    char specialChars[] = { ';', '@', ':', '.', '{', '}', '(', ')' };
    int numSpecialChars = sizeof(specialChars) / sizeof(char);
    for (int i = 0; i < numSpecialChars; i++) {
        if (c == specialChars[i]) {
            return 1;
        }
    }
    return 0;
}

void printWords(char** words, int numWords) {
    for (int i = 0; i < numWords; i++) {
        printf("%s\n", words[i]);
    }
}



void lista_caracteres(FILE* arquivo ){

    char** vetor = (char**) malloc(1000 * sizeof(char*));
    if (vetor == NULL) {
        printf("Erro ao alocar memória.\n");
    }

    char palavra[100];

    int indice = 0;

    // Lê cada palavra do arquivo
    while (fscanf(arquivo, "%s", palavra) == 1) {
        int i;
        int tamanhoPalavra = strlen(palavra);
        int caracteresEspeciais = 0;
        char aux[2];
        bool notAlfa = false;

        // Verifica se a palavra contém caracteres especiais
        for (i = 0; i < tamanhoPalavra; i++) {
            if (!isalpha(palavra[i]) && !isdigit(palavra[i])) {
                caracteresEspeciais++;
                break;
            }
        }

        // Cria uma nova palavra para armazenar a palavra completa
        char* novaPalavra = (char*) malloc((tamanhoPalavra + 1) * sizeof(char));
        
        strcpy(novaPalavra, palavra);

        // Cria uma nova palavra para armazenar a parte da palavra sem o caractere especial
        char* novaPalavra1 = (char*) malloc((tamanhoPalavra + 1) * sizeof(char));
        novaPalavra1[0] = '\0';
        novaPalavra1[1] = '\0';

        printf("NOVA PALAVRA -> %s \n", novaPalavra); //APAGAR

        // Isola os caracteres especiais
        if (caracteresEspeciais > 0) {
            for (i = 0; i < tamanhoPalavra; i++) {
                if(isalpha(palavra[i]) || isdigit(palavra[i])){
                    aux[0] = palavra[i];

                    strcat(novaPalavra1, aux); // concatena valores em novaPalavra1

                    if(!isalpha(palavra[i+1]) && !isdigit(palavra[i+1])){

                        vetor[indice] = novaPalavra1;
                        
                        printf("VETOR-> %d PALAVRA->%s\n", indice, vetor[indice]);

                        indice++;

                    }
                }else{
                    // Cria uma nova palavra para armazenar o caractere especial isolado
                    char* novaPalavra2 = (char*) malloc(2 * sizeof(char));
                    novaPalavra2[0] = palavra[i];
                    novaPalavra2[1] = '\0';

                    
                    // Salva a nova palavra com o caractere especial no vetor de palavras
                    vetor[indice] = novaPalavra2;

                    printf("VETOR-> %d PALAVRA->%s\n", indice, vetor[indice]);

                    indice++;

                    //strcpy(novaPalavra1,"");
                    
                }
            }
        } else {
            // Salva a palavra completa no vetor de palavras
            vetor[indice] = novaPalavra;

            printf("VETOR-> %d PALAVRA->%s\n", indice, vetor[indice]);
            indice++;
        }
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Exibe as palavras do vetor
    printf("Palavras no vetor:\n");
    for (int i = 0; i < indice; i++) {
        printf("indice ->%d palavra ->%s\n", i, vetor[i]);
    }

    // Libera a memória alocada
    for (int i = 0; i < indice; i++) {
        free(vetor[i]);
    }
    free(vetor);

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
Lista* cria_lista_simbolos(){

    //abrir tabela de simbolos
    FILE *list_s;
    list_s = fopen("tabela_simbolos.txt", "r");
    if(list_s == NULL){
        printf("erro na tabela de simbolos!\n");
        exit(1);
    }

    elem *no = (elem*) malloc(sizeof(elem));
    //elem* lista = (elem*) malloc (28*sizeof(elem));
    Lista* li = cria_lista();
    //elem no;
    char simbolo[20];
    char token[20];
    int i = 0;

    while(fscanf(list_s,"%[^|]%*c ",simbolo)==1){
        fscanf(list_s,"%[^\n]%*c ",token);

        strcpy(no[i].simbolo,simbolo);
        strcpy(no[i].token,token);
        i++;

        if ((*li) == NULL) { //lista vazia: insere in�cio
            no->prox = NULL;
            *li = no;
        }
        else{
            elem *ant, *atual = *li;
            //while(no != NULL){
                ant = atual; 
                atual = atual->prox;
            //}
            if (atual == *li) { //insere inicio
                no->prox = (*li);
                *li = no;
            }
            else
            {
                no->prox = atual;
                printf("simbolo: %s token %s\n",no->simbolo, no->token);
                ant->prox = no;
            }
        }
*/ 

        /*
        if ((*li) == NULL) { //lista vazia: insere in�cio
            no->prox = NULL;
            *li = no;
        }
        else{
            elem *ant, *atual = *li;
            while (atual != NULL){
                ant = atual;
                atual = atual->prox;
                if (atual == *li) { //insere inicio
                    no->prox = (*li);
                    *li = no;
                }
                else
                {
                    no->prox = atual;
                    ant->prox = no;
                }
                break; 
            }
        }
        
    }
    fclose(list_s);
    return li;
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
        printf("simbolo: %s token %s\n",no->simbolo, no->token);
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

/*
int insere_lista_ordenada(Lista* li, Tipo_Dado dt){
    if (li == NULL) return ERRO;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return ERRO;

    strcpy(no->dado, dt);
    if ((*li) == NULL) { //lista vazia: insere in�cio
        no->prox = NULL;
        *li = no;
        return OK;
    }
    else {
        Elem *ant, *atual = *li;
        while (atual != NULL && atual->dado < dt) {
            ant = atual;
            atual = atual->prox;
        }
        if (atual == *li) { //insere inicio
            no->prox = (*li);
            *li = no;
        }
        else
        {
            no->prox = atual;
            ant->prox = no;
        }
        return OK;
    }

}
*/
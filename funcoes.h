#define NUM_SIMBOLOS 27 //numero fixo de simbolos na tabela de simbolos
#define TAM 1000 //tamanho maximo da lista inicial de caracteres

//estrutura da lista de tokens e simbolos
struct elemento{
    char simbolo[20];
    char token[20];
};

typedef struct elemento* elem;

bool numero(char x);
bool letra(char x);

void limpa_saida();
void printa_saida(char* simbolo, char* token);
char* caixa_baixa(char* palavra);
char* busca_palavra_reconhecida(char* palavra, elem lista_simbolos);
char* cria_lista_caracteres();
struct elemento preenche_simbolos(FILE* file);
elem cria_lista_simbolos();

typedef struct cliente{
    int cod;
    char nome[60];
    char empresa[80];
    char depart[80];
    char telefone[15];
    char celular[16];
    char email[60];
} CLIENTE;

typedef struct elemento* Lista;

Lista *criaLista();

int listaCheia(Lista *li);
int listaVazia(Lista *li);
int tamanhoLista(Lista *li);

void coletaDados(int escolha, Lista *li);

void insereCliente(Lista *li);
int insere_lista_ordenada(Lista *li, CLIENTE cl);

void formatInputChar(int tamanho, bool x, void *input);

void consultaClienteCodigo(Lista *li);
int consulta_lista_cod(Lista *li, int cod, CLIENTE *cl);

void consulta_lista_nome(Lista *li);

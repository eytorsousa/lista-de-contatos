#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "listaContatos.h"

struct elemento{
    CLIENTE dados;
    struct elemento *prox;
};

typedef struct elemento ELEMENTO;

Lista *criaLista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL){
        *li = NULL;
    }
    return li;
}

int listaCheia(Lista *li){
    return 0;
}

int listaVazia(Lista *li){
    if(li == NULL){
        return 1;
    }
    if(*li == NULL){
        return 1;
    }
    return 0;
}

int tamanhoLista(Lista *li) {
    if(li == NULL){
        return -1;
    }

    int acum = 0;
    ELEMENTO *no = *li;
    while(no != NULL){
        acum++;
        no = no->prox;
    }
    return acum;
}


/* ----------------------------------------------------------- */
/* Switch principal: gerencia a chamada de funcoes auxiliares que, por sua vez, chamam as funcoes de execucao */
void coletaDados(int escolha, Lista *li){
    switch(escolha){
        case 1:
            system("cls");
            insereCliente(li);
            break;
        case 2:
            system("cls");
            consultaClienteCodigo(li);
            break;
        case 3:
            system("cls");
            consulta_lista_nome(li);
            break;
        case 6:
            system("cls");
            removeClienteCodigo(li);
            break;
    }
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void auxiliar: coleta informacoes e passa para funcao de aplicacao propriamente dita */
void insereCliente(Lista *li){
    CLIENTE cl;
    int x;

    printf("\n[-------------------- INSERINDO CLIENTE --------------------]\n\n");

    printf("Insira o CODIGO do cliente: ");
    scanf(" %d", &cl.cod);
    printf("\nInsira o NOME do cliente: ");
    formatInputChar(60, true, cl.nome);
    printf("\nInsira o NOME da EMPRESA: ");
    formatInputChar(80, true, cl.empresa);
    printf("\nInsira o NOME do DEPARTAMENTO: ");
    formatInputChar(80, true, cl.depart);
    printf("\nInsira o numero de TELEFONE com DDD (ex.: 1124044240)\nTELEFONE: ");
    formatInputChar(15, false, cl.telefone);
    printf("\nInsira o numero de CELULAR com DDD (ex.: 11912345678)\nCELULAR: ");
    formatInputChar(16, false, cl.celular);
    printf("\nInsira o E-MAIL do cliente: ");
    formatInputChar(60, false, cl.email);

    x = insere_lista_ordenada(li, cl);
    system("cls");
    if(x){
        printf("\n\tCLIENTE INSERIDO COM SUCESSO!\n");
    } else {
        printf("\n\tFALHA AO INSERIR CLIENTE!\n");
    }
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void auxiliar: limpa buffers, coleta variaveis do tipo char e converte em uppercase se for necessario */
void formatInputChar(int tamanho, bool x, void *input){

    fflush(stdin);
    fgets((char*)input, tamanho-1, stdin);

    size_t length = strlen((char*)input);
    if (length > 0 && ((char*)input)[length - 1] == '\n') {
        ((char*)input)[length - 1] = '\0';
    }

    fflush(stdin);

    if(x){
        strupr((char*)input);
    }
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao int: aplica a operacao desejada (insercao ordenada) */
int insere_lista_ordenada(Lista *li, CLIENTE cl){
    if(li == NULL){
        return 0;
    }
    ELEMENTO *no = (ELEMENTO*) malloc(sizeof(ELEMENTO));
    if(no == NULL){
        return 0;
    }
    no->dados = cl;
    if(listaVazia(li)){
        no->prox = (*li);
        *li = no;
        return 1;
    } else {
        ELEMENTO *ant, *atual = *li;
        while(atual != NULL && atual->dados.cod < cl.cod){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){
            no->prox = (*li);
            *li = no;
        } else {
            no->prox = ant->prox;
            ant->prox = no;
        }

        return 1;
    }
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void auxiliar: coleta informacoes e passa para funcao de aplicacao propriamente dita */
void consultaClienteCodigo(Lista *li){
    int x, cod;;
    CLIENTE cl;

    printf("\n[-------------------- CONSULTANDO CLIENTE (CODIGO) --------------------]\n");
    printf("\nInsira o CODIGO do cliente que deseja buscar: ");
    scanf(" %d", &cod);

    x = consulta_lista_cod(li, cod, &cl);
    if(x){
        printf("\n[-------------------- CONSULTANDO CLIENTE (CODIGO) --------------------]\n");
        printf("\nINFORMACOES DO CLIENTE DE CODIGO %d:", cod);
        printf("\n\nNome: \t\t\t%s", cl.nome);
        printf("\nEmpresa: \t\t%s", cl.empresa);
        printf("\nDepartamento: \t\t%s", cl.depart);
        printf("\nTelefone: \t\t%s", cl.telefone);
        printf("\nCelular: \t\t%s", cl.celular);
        printf("\nE-mail: \t\t%s", cl.email);
        printf("\n\n[-------------------------------------------------------------------------]\n");
    } else {
        printf("\n\tCliente %d nao encontrado!\n", cod);
    }

    printf("\n\tAPERTE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n\n");
    system("pause");
    system("cls");

}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao int: aplica a operacao desejada (consulta por codigo) */
int consulta_lista_cod(Lista *li, int cod, CLIENTE *cl){
    if(li == NULL){
        return 0;
    }
    ELEMENTO *no = *li;
    while(no != NULL && no->dados.cod != cod){
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    } else {
        *cl = no->dados;
        return 1;
    }
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void principal: coleta informacoes e realiza busca por nome */
void consulta_lista_nome(Lista *li){
    char nome[60];
    CLIENTE cl;

    printf("\n[-------------------- CONSULTANDO CLIENTE (NOME) --------------------]");
    printf("\nInsira o NOME do cliente que deseja buscar: ");
    formatInputChar(60, true, nome);
    system("cls");

    ELEMENTO *atual = *li;
    int cont = 0;

    printf("\n[-------------------- CONSULTANDO CLIENTE (NOME) --------------------]\n");
    while(atual != NULL) {
        if (strstr(atual->dados.nome, nome)){
            cl = atual->dados;
            printf("\nINFORMACOES DO CLIENTE DE NOME '%s':", nome);
            printf("\n\nNome: \t\t\t%s", cl.nome);
            printf("\nEmpresa: \t\t%s", cl.empresa);
            printf("\nDepartamento: \t\t%s", cl.depart);
            printf("\nTelefone: \t\t%s", cl.telefone);
            printf("\nCelular: \t\t%s", cl.celular);
            printf("\nE-mail: \t\t%s", cl.email);
            printf("\n\n[-------------------------------------------------------------------------]\n");
            cont++;
        }
        atual = atual->prox;
    }

    if (atual == NULL && cont == 0) {
        printf("\n\tNenhum cliente encontrado com o nome: '%s'\n", nome);
    }

    printf("\n\tAPERTE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n\n");
    system("pause");
    system("cls");
}
/* ----------------------------------------------------------- */

void removeClienteCodigo(Lista *li){
    int cod, x;
    CLIENTE cl;

    printf("\nInsira o CODIGO do cliente que deseja remover: ");
    scanf(" %d", &cod);
    system("cls");

    x = consulta_lista_cod(li, cod, &cl);
    if(x){
        printf("\n[-------------------- REMOVENDO CLIENTE (CODIGO) --------------------]\n");
        printf("\nINFORMACOES DO CLIENTE DE CODIGO %d:", cod);
        printf("\n\nNome: \t\t\t%s", cl.nome);
        printf("\nEmpresa: \t\t%s", cl.empresa);
        printf("\nDepartamento: \t\t%s", cl.depart);
        printf("\nTelefone: \t\t%s", cl.telefone);
        printf("\nCelular: \t\t%s", cl.celular);
        printf("\nE-mail: \t\t%s", cl.email);
        printf("\n\n[-------------------------------------------------------------------------]\n");
    } else {
        printf("\n\tCliente %d nao encontrado!\n", cod);
    }

    if(x){
        x = -1;
        do{
            printf("\nTem certeza que deseja REMOVER o cliente acima?");
            printf("\n\tSIM[1] // NAO[0]\n");
            printf("\nEscolha: ");
            scanf(" %d", &x);
            if(x < 0 || x > 1){
                do{
                    printf("\n\tESCOLHA INVALIDA! INSIRA NOVAMENTE!");
                    printf("\nInsira o numero da operacao: ");
                    scanf(" %d", &x);
                } while(x < 0 || x > 1);
            }
            system("cls");
        } while(x < 0 || x > 1);
    }

    if(x){
        x = remove_lista(li, cod);
    }

    if(x){
        printf("\n\tCLIENTE REMOVIDO COM SUCESSO!\n");
    } else {
        printf("\n\tFALHA AO REMOVER CLIENTE!\n\n\tOPERACAO CANCELADA!");
    }
}

int remove_lista(Lista *li, int cod){
    if(li == NULL){
        return 0;
    }
    ELEMENTO *ant, *no = *li;
    while(no != NULL && no->dados.cod != cod){
        ant = no;
        no = no->prox;
    }

    if(no == NULL){
        return 0;
    }

    if(no == *li){
        *li = no->prox;
    } else {
        ant->prox = no->prox;
    }

    free(no);
    return 1;
}

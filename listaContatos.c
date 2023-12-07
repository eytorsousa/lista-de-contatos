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
            buscaClienteCodigo(li);
            break;
        case 3:
            system("cls");
            buscaClienteNome(li);
            break;
    }
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void auxiliar: coleta informacoes e passa para funcao de aplicacao propriamente dita */
void insereCliente(Lista *li){
    CLIENTE cl;
    int x;

    printf("\n[-------------------- INSERINDO CLIENTE --------------------]\n");

    printf("Insira o codigo do cliente: ");
    scanf(" %d", &cl.cod);
    printf("\nInsira o nome do cliente: ");
    formatInputChar(60, true, cl.nome);
    printf("\nInsira o nome da empresa: ");
    formatInputChar(80, true, cl.empresa);
    printf("\nInsira o nome do departamento: ");
    formatInputChar(80, true, cl.depart);
    printf("\nInsira o numero de telefone com DDD (ex.: 1124044240)\nTELEFONE: ");
    formatInputChar(15, false, cl.telefone);
    printf("\nInsira o numero de celular com DDD (ex.: 11912345678)\nCELULAR: ");
    formatInputChar(16, false, cl.celular);
    printf("\nInsira o e-mail do cliente: ");
    formatInputChar(60, false, cl.email);

    x = insere_lista_ordenada(li, cl);
    system("cls");
    if(x){
        printf("\nCLIENTE INSERIDO COM SUCESSO!\n");
    } else {
        printf("\nFALHA AO INSERIR CLIENTE!\n");
    }
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void auxiliar: limpa buffers, coleta variaveis do tipo char e converte em uppercase se for necessario */
void formatInputChar(int tamanho, bool x, void *input){

    fflush(stdin);
    fgets((char*)input, tamanho, stdin);
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
void buscaClienteCodigo(Lista *li){
    int cod, x;
    CLIENTE cl;

    printf("\n[-------------------- CONSULTANDO CLIENTE (CODIGO) --------------------]\n");
    printf("\nInsira o codigo do cliente que deseja buscar: ");
    scanf(" %d", &cod);

    x = consulta_lista_cod(li, cod, &cl);
    system("cls");
    if(x){
        printf("\n[-------------------- CONSULTANDO CLIENTE (CODIGO) --------------------]\n");
        printf("\n\nINFORMACOES DO CLIENTE DE CODIGO %d:", cod);
        printf("\n\nNome: \t\t\t%s", cl.nome);
        printf("\nEmpresa: \t\t%s", cl.empresa);
        printf("\nDepartamento: \t\t%s", cl.depart);
        printf("\nTelefone: \t\t%s", cl.telefone);
        printf("\nCelular: \t\t%s", cl.celular);
        printf("\nE-mail: \t\t%s", cl.email);
        printf("\n[-------------------------------------------------------------------------]\n");
    } else {
        printf("\nCliente %d nao encontrado!\n", cod);
    }
    printf("\nAPERTE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n");
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
/* Funcao void auxiliar: coleta informacoes e passa para funcao de aplicacao propriamente dita */
void buscaClienteNome(Lista *li){
    int x;
    char nome[60];
    CLIENTE cl;

    printf("\n[-------------------- CONSULTANDO CLIENTE (NOME) --------------------]\n");
    printf("\nInsira o nome do cliente que deseja buscar: ");
    formatInputChar(60, true, nome);

    x = consulta_lista_nome(li, nome, &cl);
    system("cls");
    if(x){
        printf("\n[-------------------- CONSULTANDO CLIENTE (NOME) --------------------]\n");
        printf("\n\nINFORMACOES DO CLIENTE DE NOME '%s'", nome);
        printf("\n\nNome: \t\t\t%s", cl.nome);
        printf("\nEmpresa: \t\t%s", cl.empresa);
        printf("\nDepartamento: \t\t%s", cl.depart);
        printf("\nTelefone: \t\t%s", cl.telefone);
        printf("\nCelular: \t\t%s", cl.celular);
        printf("\nE-mail: \t\t%s", cl.email);
        printf("\n[-------------------------------------------------------------------------]\n");
    } else {
        printf("\nCliente '%s' nao encontrado!\n", nome);
    }
    printf("\nAPERTE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n");
    system("pause");
    system("cls");
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao int: aplica a operacao desejada (consulta por codigo) */
int consulta_lista_nome(Lista *li, char nome[60], CLIENTE *cl){
    if(li == NULL){
        return 0;
    }
    ELEMENTO *no = *li;

    while(no != NULL && !strcmp(no->dados.nome, nome)){
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


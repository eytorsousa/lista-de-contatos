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
    char contatos[] = ("contatos.bin");

    switch(escolha){
        case 1:
            system("cls");
            insereCliente(li, contatos);
            break;
        case 2:
            system("cls");
            consultaClienteCodigo(li, contatos);
            break;
        case 3:
            system("cls");
            consulta_lista_nome(li, contatos);
            break;
        case 4:
            system("cls");
            consulta_lista(li, contatos);
            break;
        case 5:
            system("cls");
            editaClienteCodigo(li, contatos);
            break;
        case 6:
            system("cls");
            removeClienteCodigo(li, contatos);
            break;
    }
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void auxiliar: coleta informacoes e passa para funcao de aplicacao propriamente dita */
void insereCliente(Lista *li, char contatos[]) {
    CLIENTE cl;
    FILE *f = fopen(contatos, "ab");

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

    // Primeiro insere na lista
    x = insere_lista_ordenada(li, cl);

    if (f != NULL && x) {
        // Abrir o arquivo novamente para adicionar o novo cliente
        fclose(f);
        f = fopen(contatos, "ab");

        fwrite(&cl, sizeof(CLIENTE), 1, f);
    }

    fclose(f);

    system("cls");
    if (x) {
        printf("\n\t\tCLIENTE INSERIDO COM SUCESSO!\n");
    } else {
        printf("\n\t\tFALHA AO INSERIR CLIENTE!\n");
    }

    printf("\n\tAPERTE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n\n");
    system("pause");
    system("cls");
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void auxiliar: limpa buffers, coleta variaveis do tipo char e converte em uppercase se for necessario */
void formatInputChar(int tamanho, bool x, void *input){

    // Limpar o buffer de entrada
    fflush(stdin);
    // Lendo uma variavel do tipo char/string
    fgets((char*)input, tamanho-1, stdin);
    // Removendo o ultimo caractere da string lida (\n)
    size_t length = strlen((char*)input);
    if (length > 0 && ((char*)input)[length - 1] == '\n') {
        ((char*)input)[length - 1] = '\0';
    }
    // Limpando o buffer novamente por seguranca
    fflush(stdin);

    // Se x for true, a string e convertida em maiuscula
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
/* Funcao void : coleta informacoes e realiza a operacao (consulta por codigo) */
void consultaClienteCodigo(Lista *li, char contatos[]) {
    int cod;
    CLIENTE cl;
    FILE *f = fopen(contatos, "rb");

    printf("\n[-------------------- CONSULTANDO CLIENTE (CODIGO) --------------------]\n");
    printf("\nInsira o CODIGO do cliente que deseja buscar: ");
    scanf(" %d", &cod);

    if (f != NULL) {
        fseek(f, 0, SEEK_SET); // Movendo o ponteiro do arquivo para o início
        while (fread(&cl, sizeof(CLIENTE), 1, f)) {
            if (cl.cod == cod) {
                printf("\n[-------------------- CONSULTANDO CLIENTE (CODIGO) --------------------]\n");
                printf("\nINFORMACOES DO CLIENTE DE CODIGO %d:", cod);
                printf("\n\nNome: \t\t\t%s", cl.nome);
                printf("\nEmpresa: \t\t%s", cl.empresa);
                printf("\nDepartamento: \t\t%s", cl.depart);
                printf("\nTelefone: \t\t%s", cl.telefone);
                printf("\nCelular: \t\t%s", cl.celular);
                printf("\nE-mail: \t\t%s", cl.email);
                printf("\n\n[-------------------------------------------------------------------------]\n");
                fclose(f);

                printf("\n\tAPERTE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n\n");
                system("pause");
                system("cls");

                return; // Sai da função após encontrar o cliente
            }
        }

        // Se o código não for encontrado
        printf("\n\tCliente %d nao encontrado na lista!\n", cod);
        fclose(f);
    } else {
        printf("\n\tErro ao abrir o arquivo!\n");
    }

    printf("\n\tAPERTE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n\n");
    system("pause");
    system("cls");
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void principal: coleta informacoes e realiza a operacao (consulta por nome) */
void consulta_lista_nome(Lista *li, char contatos[]) {
    char nome[60];
    CLIENTE cl;
    FILE *f = fopen(contatos, "rb");

    printf("\n[-------------------- CONSULTANDO CLIENTE (NOME) --------------------]");
    printf("\nInsira o NOME do cliente que deseja buscar: ");
    formatInputChar(60, true, nome);
    system("cls");

    int cont = 0;

    if (f != NULL) {
        fseek(f, 0, SEEK_SET);

        printf("\n[-------------------- CONSULTANDO CLIENTE (NOME) --------------------]\n");
        while (fread(&cl, sizeof(CLIENTE), 1, f)) {
            if (strstr(cl.nome, nome)) {
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
        }

        if (cont == 0) {
            printf("\n\tNenhum cliente encontrado com o nome: '%s'\n", nome);
        }

        fclose(f);
    } else {
        printf("\n\tErro ao abrir o arquivo!\n");
    }

    printf("\n\tAPERTE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n\n");
    system("pause");
    system("cls");
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void: Percorre todas as estruturas existentes e as exibe na tela (consulta total) */
void consulta_lista(Lista *li, char contatos[]) {
    if (li == NULL) {
        return;
    }

    CLIENTE cl;
    int cont = 0;
    FILE *f = fopen(contatos, "rb");

    if (f != NULL) {
        fseek(f, 0, SEEK_SET);

        while (fread(&cl, sizeof(CLIENTE), 1, f)) {
            printf("\nINFORMACOES DO CLIENTE DE CODIGO %d:", cl.cod);
            printf("\n\nNome: \t\t\t%s", cl.nome);
            printf("\nEmpresa: \t\t%s", cl.empresa);
            printf("\nDepartamento: \t\t%s", cl.depart);
            printf("\nTelefone: \t\t%s", cl.telefone);
            printf("\nCelular: \t\t%s", cl.celular);
            printf("\nE-mail: \t\t%s", cl.email);
            printf("\n\n[-------------------------------------------------------------------------]\n");

            cont++;
        }

        if (cont == 0) {
            printf("\n\tNenhum cliente foi inserido ainda!");
        }

        fclose(f);
    } else {
        printf("\n\tErro ao abrir o arquivo!\n");
    }

    printf("\n\tAPERTE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n\n");
    system("pause");
    system("cls");
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void: coleta informacoes e realiza a operacao (edicao de cliente) */
void editaClienteCodigo(Lista *li, char contatos[]) {
    int cod, x;
    CLIENTE cl;
    FILE *f = fopen(contatos, "rb");
    FILE *tempFile = fopen("temp.dat", "ab");  // Abre em modo adicaoo, ou seja, nao vai sobrescrever

    if (f == NULL || tempFile == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        exit(1);
    }

    printf("\n[-------------------- EDITANDO CLIENTE (CODIGO) --------------------]\n");
    printf("\nInsira o CODIGO do cliente que deseja editar: ");
    scanf(" %d", &cod);
    system("cls");

    int found = 0;

    while (fread(&cl, sizeof(CLIENTE), 1, f)) {
        if (cl.cod == cod) {
            printf("\nINFORMACOES DO CLIENTE DE CODIGO %d (a ser editado):", cod);
            printf("\n\nNome: \t\t\t%s", cl.nome);
            printf("\nEmpresa: \t\t%s", cl.empresa);
            printf("\nDepartamento: \t\t%s", cl.depart);
            printf("\nTelefone: \t\t%s", cl.telefone);
            printf("\nCelular: \t\t%s", cl.celular);
            printf("\nE-mail: \t\t%s", cl.email);
            printf("\n\n[-------------------------------------------------------------------------]\n");

            x = -1;

            do {
                printf("\nTem certeza que deseja EDITAR o cliente acima?");
                printf("\n\tSIM[1] // NAO[0]\n");
                printf("\nEscolha: ");
                scanf(" %d", &x);
                if (x < 0 || x > 1) {
                    do {
                        printf("\n\tESCOLHA INVALIDA! INSIRA NOVAMENTE!");
                        printf("\nInsira o numero da operacao: ");
                        scanf(" %d", &x);
                    } while (x < 0 || x > 1);
                }
                system("cls");
            } while (x < 0 || x > 1);

            found = 1;

            // Preenche a nova informação do cliente
            cl.cod = cod;
            printf("\n[-------------------- EDITANDO CLIENTE --------------------]\n\n");
            printf("\nInsira o NOVO NOME do cliente: ");
            formatInputChar(60, true, cl.nome);
            printf("\nInsira o NOVO NOME da EMPRESA: ");
            formatInputChar(80, true, cl.empresa);
            printf("\nInsira o NOVO NOME do DEPARTAMENTO: ");
            formatInputChar(80, true, cl.depart);
            printf("\nInsira o NOVO numero de TELEFONE com DDD (ex.: 1124044240)\nTELEFONE: ");
            formatInputChar(15, false, cl.telefone);
            printf("\nInsira o NOVO numero de CELULAR com DDD (ex.: 11912345678)\nCELULAR: ");
            formatInputChar(16, false, cl.celular);
            printf("\nInsira o NOVO E-MAIL do cliente: ");
            formatInputChar(60, false, cl.email);

            system("cls");

            // Insere o novo cliente no arquivo temporário
            fwrite(&cl, sizeof(CLIENTE), 1, tempFile);
        } else {
            // Mantém os outros clientes no arquivo temporário
            fwrite(&cl, sizeof(CLIENTE), 1, tempFile);
        }
    }

    fclose(f);
    fclose(tempFile);

    if (!found) {
        printf("\n\tCLIENTE %d NAO ENCONTRADO!\n", cod);
        remove("temp.dat"); // Caso ele não encontre, ele vai simplesmente apagar o arquivo
    } else {
        // Renomeia o arquivo temporário para o arquivo original
        remove(contatos);
        rename("temp.dat", contatos);
        printf("\n\tCLIENTE EDITADO COM SUCESSO!\n");
    }

    printf("\n\tAPERTE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n\n");
    system("pause");
    system("cls");
}
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/* Funcao void: coleta informacoes e realiza a operacao (remocao de cliente) */
void removeClienteCodigo(Lista *li, char contatos[]){ //https://pt.stackoverflow.com/questions/305195/como-remover-um-struct-armazenado-em-arquivo-em-c Criar temp file
    int cod, x;
    CLIENTE cl;
    FILE *f =  fopen(contatos, "rb");
    FILE *tempFile = fopen("temp.dat", "wb"); //Utilizando o wb ao invés de ab, pois se trata de um arquivo temporario e não preservarei o conteudo. Estarei recriando o file

    if (f == NULL || tempFile == NULL) {
        printf("Erro ao consultar clientes que serao removidos.\n");
        exit(1);
    }

    int found = 0;

    printf("\nInsira o CODIGO do cliente que deseja remover: ");
    scanf(" %d", &cod);
    system("cls");

    //x = consulta_lista_cod(li, cod, &cl);

    while (fread(&cl, sizeof(CLIENTE), 1, f)) {
        if (cl.cod == cod) {
            printf("\n[-------------------- REMOVENDO CLIENTE (CODIGO) --------------------]\n");
            printf("\nINFORMACOES DO CLIENTE DE CODIGO %d:", cod);
            printf("\n\nNome: \t\t\t%s", cl.nome);
            printf("\nEmpresa: \t\t%s", cl.empresa);
            printf("\nDepartamento: \t\t%s", cl.depart);
            printf("\nTelefone: \t\t%s", cl.telefone);
            printf("\nCelular: \t\t%s", cl.celular);
            printf("\nE-mail: \t\t%s", cl.email);
            printf("\n\n[-------------------------------------------------------------------------]\n");

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

            found = 1; //UTILIZANDO A SEGUINTE VARIAVEL PARA VALIDAR SE SERA POSSIVEL FAZER ESSA MIGRACAO DE ARQUIVOS
        }else{
            fwrite(&cl, sizeof(CLIENTE), 1, tempFile);
        }


    }

    fclose(f);
    fclose(tempFile);

    if(found && x == 1){
        remove(contatos);
        rename("temp.dat", contatos);
        printf("\n\tCLIENTE REMOVIDO COM SUCESSO!\n");
    }
    else if(!found){
        printf("\n\tCLIENTE %d NAO ENCONTRADO!\n", cod);
        remove("temp.dat"); //Caso ele não encontre, ele vai simplesmente apagar o arquivo
    }
    else{
        //Algum outro erro tem que ter acontecido e da mesam forma remove o arquivo temporario
        printf("\n\tOPERACAO CANCELADA E O CLIENTE NAO FOI REMOVIDO.\n");
        remove("temp.dat");
    }

    printf("\n\tAPERTE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n\n");
    system("pause");
    system("cls");


}
/* ----------------------------------------------------------- */

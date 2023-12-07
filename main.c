#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "listaContatos.h"

int main(){
    Lista *li;
    li = criaLista();
    int escolha;

    do{
        printf("\n[-------------------- MENU --------------------]\n");
        printf("[1] - Inserir novo cliente\n\n");

        printf("[2] - Buscar cliente por CODIGO\n");
        printf("[3] - Buscar cliente por NOME\n\n");

        printf("[4] - Gerar relatorio - Lista Completa\n\n");

        printf("[5] - Editar cliente\n\n");

        printf("[6] - Remover cliente\n\n");

        printf("[0] - ENCERRAR PROGRAMA");
        printf("\n[----------------------------------------------]\n");
        printf("\nInsira o numero da operacao: ");
        scanf(" %d", &escolha);

        if(escolha < 0 || escolha > 6){
            do{
                printf("\n\tESCOLHA INVALIDA! INSIRA NOVAMENTE!");
                printf("\nInsira o numero da operacao: ");
                scanf(" %d", &escolha);
            } while(escolha < 0 || escolha > 6);
        }
        if(escolha > 0 && escolha < 7){
            coletaDados(escolha, li);
        }
    } while(escolha != 0);
    //apagaLista(li);

    printf("\n\n\tFIM DO PROGRAMA!\n");
    system("pause");
    return 0;
}

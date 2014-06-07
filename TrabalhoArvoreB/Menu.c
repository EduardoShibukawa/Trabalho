#include <stdio.h>
#include "ArvoreB.h"


void Menu()
{
    char opcao = '0';
    do {
        system("cls");
        printf("Sistema de Gerenciamento de Candidatos ao Vestibular\n\n");
        printf("Escolha a opção desejada:\n\n");
        printf("1 - Importar dados a partir de um arquivo\n");
        printf("2 - Inserir novo registro\n");
        printf("3 - Remover registro existente\n");
        printf("4 - Pesquisar por inscricao\n");
        printf("5 - Listar indices \n");
        printf("6 - Sair\n");

        printf("\nSelecione uma opcao: ");
        fflush(stdin);
        scanf("%c", &opcao);
        switch (opcao){
        case '1': //Importar
            printf("\n");
            printf("opcao 1 escolhida");
            break;

        case '2': //Inserir
            printf("\n");
            printf("opcao 2 escolhida");
            break;

        case '3': //Remover
            printf("\n");
            printf("opcao 3 escolhida");
            break;
        case '4': //Buscar
            printf("\n");
            printf("opcao 4 escolhida");
            break;

        case '5': //Listar
            printf("\n");
            printf("Arquivo compactado com sucesso.");
            break;
        }
        printf("\n\nPressione <ENTER> para continuar...");
        getch();
    } while (opcao != '6');

    printf("\n\nPressione uma tecla para sair...");
    getch();
}

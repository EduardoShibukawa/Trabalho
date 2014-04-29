#include <stdio.h>
#include <stdlib.h>

#include "IndicesAluno.h"

void CadastrarAluno () {
    system("cls");
    Aluno a;
    char cInscricao[TAM_FIELD];
    printf("\n--- Cadastro de Aluno --- \n\n");
    printf("Inscricao: ");
    fflush(stdin);
    gets(cInscricao);
    a.Inscricao = atoi(cInscricao);

    printf("Nome: ");
    fflush(stdin);
    gets(a.Nome);

    printf("Curso: ");
    fflush(stdin);
    gets(a.Curso);

    printf("Nota: ");
    fflush(stdin);
    gets(a.NotaFinal);

    InserirAluno(a);

    printf("\nAluno cadastrado: %s", a.Nome);
    printf("\n\nPressione <ENTER> para continuar...");
    getch();
}
int main()
{
    char opcao = '0';
    int i;

    do {
        //system("cls");
        printf("Sistema de Gerenciamento de Candidatos ao Vestibular\n\n");
        printf("Escolha a opção desejada:\n\n");
        printf("1 - Importar a partir de um arquivo\n");
        printf("2 - Inserir novo registro\n");
        printf("3 - Remover registro existente\n");
        printf("4 - Pesquisas e Relatorios\n");
        printf("5 - Sair\n");
        printf("6 - Busca Aluno teste");

        printf("\nSelecione uma opcao: ");
        fflush(stdin);
        scanf("%c", &opcao);
        switch (opcao){

        case '1':
            printf("\n");
            ImportarDados(A_DADOS);
            MontarIndices();
            break;

        case '2':
            printf("\n");
            CadastrarAluno();
            MontarIndices();
            break;

        case '3':
            printf("\n");
            break;

        case '6':
            BuscaAluno(0);
        }
    } while (opcao != '5');

    EncerrarListas();
}

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
}

void ExcluirAluno() {
    system("cls");
    printf("\n--- Remoção de aluno --- \n\n");
    printf("Digite o numero da inscricao: ");
    fflush(stdin);
    char cInscricao[TAM_FIELD];
    gets(cInscricao);
    Aluno a = BuscarAlunoChavePrimaria(atoi(cInscricao));
    RemoverAluno(a);
}

void ImprimirBuscaChavePrimaria(){
    system("cls");
    printf("\n--- Pesquisa por chave primaria --- \n\n");
    printf("Digite o numero da inscricao: ");
    fflush(stdin);
    char cInscricao[TAM_FIELD];
    gets(cInscricao);
    Aluno a = BuscarAlunoChavePrimaria(atoi(cInscricao));
    ImprimirAluno(a);
}

void ImprimirBuscas () {
    char opcao;
    system("cls");
    printf("\n--- Busca por: --- \n\n");
    printf("1 - Inscrição \n");
    printf("2 - Nome \n");
    printf("3 - Curso \n");
    printf("\nSelecione uma opcao: ");
    fflush(stdin);
    scanf("%c", &opcao);
    switch (opcao){
    case '1':
        ImprimirBuscaChavePrimaria();
        break;
    case '2':
        system("cls");
        printf("\n--- Pesquisa por nome --- \n\n");
        printf("Digite o nome: ");
        fflush(stdin);
        char cNome[TAM_FIELD];
        gets(cNome);
        ImprimirBuscaSecundaria(cNome, BUSCA_NOME);
        break;
    case '3':
        system("cls");
        printf("\n--- Pesquisa por curso --- \n\n");
        printf("Digite o curso: ");
        fflush(stdin);
        char cCurso[TAM_FIELD];
        gets(cCurso);
        ImprimirBuscaSecundaria(cCurso, BUSCA_CURSO);
        break;
    default:
        break;
    }
}

int main()
{
    MontarIndices();
    char opcao = '0';
    do {
        system("cls");
        printf("Sistema de Gerenciamento de Candidatos ao Vestibular\n\n");
        printf("Escolha a opção desejada:\n\n");
        printf("1 - Importar a partir de um arquivo\n");
        printf("2 - Inserir novo registro\n");
        printf("3 - Remover registro existente\n");
        printf("4 - Pesquisas e Relatorios\n");
        printf("5 - Sair\n");

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
            ExcluirAluno();
            MontarIndices();
            break;
        case '4':
            printf("\n");
            ImprimirBuscas();
            break;
        }
        printf("\n\nPressione <ENTER> para continuar...");
        getch();
    } while (opcao != '5');
    CompactarArquivo();
    EncerrarListas();
}

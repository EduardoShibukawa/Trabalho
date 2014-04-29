#ifndef INDIVUOS_H_INCLUDED
#define INDIVUOS_H_INCLUDED
#include "IndicesAluno.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define A_PRINCIPAL "PRINCIPAL.TXT"
#define A_DADOS "dados.txt"
#define TAM_FIELD 50
#define TAM_REGISTRO 150
#define DELIMITADOR_FIELD "|"
#define DELIMITADOR_REGISTRO "|"
#define DELIM '|'
#define DELIMITADOR_REMOVE "*"

typedef struct{
    int Inscricao;
    char Nome[TAM_FIELD];
    char Curso[TAM_FIELD];
    char NotaFinal[TAM_FIELD];
} Aluno;

short pegarCampo(char field[], char recbuff[], short scan_pos, short rec_lgth){
      short fpos = 0;

      if (scan_pos == rec_lgth)  // if no more fields to read,
         return (0);             // return scan_pos = 0

      // scanning loop
      while ( scan_pos < rec_lgth &&
              (field[fpos++] = recbuff[scan_pos++]) != DELIM )
              ;

      if (field[fpos - 1] == DELIM)  // if last char is a field delimiter,
         field[--fpos] = '\0';           // replace it with null
      else
          field[fpos] = '\0';            /* otherwise, just ensure that the
                                            field is null terminated */

      return(scan_pos); // return position of start of next field
}

void ImportarDados (char *FileName) {
    Aluno a;
    FILE *arquivo;
    if ((arquivo = fopen(A_PRINCIPAL, "w+")) == NULL) {
                system("cls");
                printf("\nNenhum registro encontrado\n");
                getch();
                }
    fclose(arquivo);
    if ((arquivo = fopen(FileName, "r")) == NULL) {
            system("cls");
            printf("\nNenhum registro encontrado\n");
            getch();
            }
    char Buff;
    char recBuff[TAM_REGISTRO];
    char field[TAM_FIELD];
    int sucesso = 1;
    int i = -1;
    int fld_count = 1;
    int scan_pos = 0;
    int tamanhoLeitura = 0;
    rewind(arquivo);
    while (!feof(arquivo)) {
            i++;
            Buff = fgetc(arquivo);
            recBuff[i] = Buff;
            if (Buff == '\t') {
                recBuff[i] = DELIM;

            } else if (Buff == '\n') {
                recBuff[i] = DELIM;
                recBuff[i+1] = '\0';
                tamanhoLeitura = strlen(recBuff);
                while ((scan_pos = pegarCampo(field, recBuff, scan_pos, tamanhoLeitura)) > 0 ){
                    switch (fld_count){
                    case 1:
                        a.Inscricao = atoi(field);
                        break;
                    case 2:
                        strncpy(a.Nome, field, TAM_FIELD);
                        break;
                    case 3:
                        strncpy(a.Curso, field, TAM_FIELD);
                        break;
                    case 4:
                        strncpy(a.NotaFinal, field, TAM_FIELD);
                        break;
                    default:
                        printf("Bug na Importação do aluno, entrou em case diferente de 1-4.");
                        sucesso = 0;
                        break;
                    }
                fld_count++;
                }
                InserirAluno(a);
                a.Inscricao = -1;
                a.Nome[0] = '\0';
                a.Curso[0] = '\0';
                a.NotaFinal[0] = '\0';
                recBuff[0] = '\0';
                field[0] = '\0';
                scan_pos = 0;
                fld_count = 1;
                i = -1;
            }
    };
    if (sucesso == 1) printf("Importação realizada com sucesso!\n");
    fclose(arquivo);
}

Aluno BuscaAluno(int byteoffset){
    Aluno a;
    a.Curso[0] = '\0';
    a.Inscricao = -1;
    a.Nome[0] = '\0';
    a.NotaFinal[0] = '\0';
    if (byteoffset != -1) {
        FILE *arquivo;
        if ((arquivo = fopen(A_PRINCIPAL ,"r")) == NULL) {
                system("cls");
                printf("\nNenhum registro encontrado\n");
                getch();
                return a;
                }
        char recBuff[TAM_REGISTRO];
        char field[TAM_FIELD];
        int i;
        fseek(arquivo, byteoffset, SEEK_SET);
        fgets(recBuff, 4, arquivo);
        int tamanhoLeitura = atoi(recBuff);
        fgets(recBuff, tamanhoLeitura+1, arquivo);
        int fld_count = 1;
        int scan_pos = 0;
        int apagado = 0;
        while (((scan_pos = pegarCampo(field, recBuff, scan_pos, tamanhoLeitura)) > 0)&&apagado==0){
            switch (fld_count){
            case 1:
                if (field[0] == '*') {
                    apagado = 1;
                } else {
                    a.Inscricao = atoi(field);
                }
                break;
            case 2:
                strncpy(a.Nome, field, TAM_FIELD);
                break;
            case 3:
                strncpy(a.Curso, field, TAM_FIELD);
                break;
            case 4:
                strncpy(a.NotaFinal, field, TAM_FIELD);
                break;
            default:
                printf("Bug na função BuscarAluno, entrou em case diferente de 1-4.");
            }
        fld_count++;
        }
        fclose(arquivo);
    }
    return(a);
}

Aluno BuscarAlunoChavePrimaria (int Inscricao) {
    return BuscaAluno(BuscaBinariaByteOffSet(Inscricao));
}

void ImprimirAluno(Aluno a) {
    printf("----------------------------------------------\n");
    if (a.Inscricao != -1 ) {
        //printf("\n Aluno encontrado!\n");
        printf("Matricula: %d \n", a.Inscricao);
        printf("Aluno: %s \n", a.Nome);
        printf("Curso: %s \n", a.Curso);
        printf("NotaFinal: %s \n", a.NotaFinal);
    } else printf("Aluno não encontrado \n!");
    printf("----------------------------------------------\n");
}

void InserirAluno(Aluno a) {
    if (a.Inscricao != -1) {
        FILE *arquivo;
        if ((arquivo = fopen(A_PRINCIPAL ,"a+")) == NULL) {
            if ((arquivo = fopen(A_PRINCIPAL ,"w+")) == NULL) {
                    system("cls");
                    printf("\nNenhum registro encontrado\n");
                    getch();
                    return 0;
                    }
                }

        int tamanho = 0;
        char registro[TAM_REGISTRO];

        itoa(a.Inscricao, registro, 10);
        strcat(registro, DELIMITADOR_FIELD);
        strcat(registro, a.Nome);
        strcat(registro, DELIMITADOR_FIELD);
        strcat(registro, a.Curso);
        strcat(registro, DELIMITADOR_FIELD);
        strcat(registro, a.NotaFinal);
        strcat(registro, DELIMITADOR_REGISTRO);
        tamanho = strlen(registro);
        fprintf(arquivo, "%03d",tamanho);
        fwrite(registro, 1, tamanho, arquivo);
        fclose(arquivo);
    }
}

void RemoverAluno (Aluno a) {
    FILE *arquivo;
    if ((arquivo = fopen(A_PRINCIPAL ,"r+")) == NULL) {
            system("cls");
            printf("\nNenhum registro encontrado\n");
            getch();
            return 0;
            }
    int byteoffset = BuscaBinariaByteOffSet(a.Inscricao);
    fseek(arquivo, byteoffset + 3, SEEK_SET);
    fwrite(DELIMITADOR_REMOVE, 1, strlen(DELIMITADOR_REMOVE), arquivo);
    fclose(arquivo);
}

void CompactarArquivo() {
}
#endif // INDIVUOS_H_INCLUDED

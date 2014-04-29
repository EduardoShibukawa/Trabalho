#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef INDIVUOS_H_INCLUDED
#define INDIVUOS_H_INCLUDED
#define A_PRINCIPAL "PRINCIPAL.TXT"
#define A_DADOS "dados.txt"
#define TAM_FIELD 50
#define TAM_REGISTRO 150
#define DELIMITADOR_FIELD "|"
#define DELIMITADOR_REGISTRO "|"
#define DELIM '|'

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
                    }
                fld_count++;
                }
                InserirAluno(a);
                a.Inscricao = 0;
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
    fclose(arquivo);
}

void BuscarAluno (int Indice) {
}

Aluno BuscaAluno(int byteoffset){
    Aluno a;
    FILE *arquivo;
    if ((arquivo = fopen(A_PRINCIPAL ,"r+")) == NULL) {
            system("cls");
            printf("\nNenhum registro encontrado\n");
            getch();
            return a;
            }
    char recBuff[TAM_REGISTRO];
    char field[TAM_FIELD];
    int i;
    fseek(arquivo, byteoffset,SEEK_SET);
    fgets(recBuff, 4, arquivo);
    int tamanhoLeitura = atoi(recBuff);
    fgets(recBuff, tamanhoLeitura+1, arquivo);
    int fld_count = 1;
    int scan_pos = 0;
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
            printf("Bug na função BuscarAluno, entrou em case diferente de 1-4.");
        }
    fld_count++;
    }
    return(a);
}

int BuscaALuno(int Inscricao) {
    int ByteOffSet = -1;
    //busca ByteOffSet usandoquicksort;
    //BuscaAluno(ByteOffSet)
    return (ByteOffSet);
}

void Listar (){
}

void InserirAluno(Aluno a) {
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

void RemoverAluno (Aluno a) {
    FILE *arquivo;
    if ((arquivo = fopen(A_PRINCIPAL ,"rw")) == NULL) {
            system("cls");
            printf("\nNenhum registro encontrado\n");
            getch();
            return 0;
            }
    int byteoffset;
    char recBuff[TAM_REGISTRO];
    rewind(arquivo);
    fseek(arquivo, byteoffset, SEEK_SET);
    fgets(recBuff, 2, arquivo);
    int tamanhoLeitura = atoi(recBuff);
    fgets(recBuff, tamanhoLeitura, arquivo);
    return(a);
    fclose(arquivo);
}

#endif // INDIVUOS_H_INCLUDED

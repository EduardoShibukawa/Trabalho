#include <string.h>
#include <stdlib.h>
#ifndef INDIVUOS_H_INCLUDED
#define INDIVUOS_H_INCLUDED


#define A_PRINCIPAL "PRINCIPAL.TXT"
#define I_PRIMARIO "I_PRIMARIO.TXT"
#define I_NOME "I_NOME.TXT"
#define I_CURSO "I_CURSO.TXT"
#define TAM_FIELD 50
#define TAM_REGISTRO 150
#define DELIMITADOR_FIELD "|"
#define DELIMITADOR_REGISTRO "z"

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
              (field[fpos++] = recbuff[scan_pos++]) != DELIMITADOR_FIELD )
              ;

      if (field[fpos - 1] == DELIMITADOR_FIELD)  // if last char is a field delimiter,
         field[--fpos] = '\0';           // replace it with null
      else
          field[fpos] = '\0';            /* otherwise, just ensure that the
                                            field is null terminated */

      return(scan_pos); // return position of start of next field
}

void ImportarDados (FILE *dados) {
/*   LERDADOS
   ENQUANTO ACHA DADO
     InserirAluno() */
}

void BuscarAluno (int Indice) {
}

Aluno BuscaAluno(int byteoffset){
    Aluno a;
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
    rewind(arquivo);
    fseek(arquivo, byteoffset,SEEK_SET);
    fgets(recBuff, 2, arquivo);
    int tamanhoLeitura = atoi(recBuff);
    fgets(recBuff, tamanhoLeitura, arquivo);
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

    int tamanho;
    char registro[TAM_REGISTRO];

    itoa(a.Inscricao, registro, 10);
    strcat(registro, DELIMITADOR_FIELD);
    strcat(registro, a.Nome);
    strcat(registro, DELIMITADOR_FIELD);
    strcat(registro, a.Curso);
    strcat(registro, DELIMITADOR_FIELD);
    strcat(registro, a.NotaFinal);
    strcat(registro, DELIMITADOR_REGISTRO);

    tamanho = strlen(&registro);
    fwrite(tamanho, 1, sizeof(tamanho), arquivo);
    fwrite(registro, 1, tamanho, arquivo);
    fclose(arquivo);
    //MontarIndices();
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

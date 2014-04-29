#include "Alunos.h"
#include <stdio.h>
#include <stdlib.h>
#define I_PRIMARIO "I_PRIMARIO.TXT"
#define I_NOME "I_NOME.TXT"
#define I_CURSO "I_CURSO.TXT"
#ifndef INDICES_H_INCLUDED
#define INDICES_H_INCLUDED
#define TAM_MAX_ARRAY 1000

typedef struct {
    int ByteOffSet;
    int ID;
} IndicePrimario;

typedef struct {
    int RRN;
    char Valor[TAM_FIELD];
} IndiceSecundario;

typedef struct {
    int ID;
    int ProxRRNCurso;
    int ProxRRNNome;
} RegListaInvertida;

typedef struct {
    int Tamanho;
    IndiceSecundario Indice[TAM_MAX_ARRAY];
} IndicesSecundario;

typedef struct {
    int Tamanho;
    IndicePrimario Indice[TAM_MAX_ARRAY];
} IndicesPrimario;

typedef struct {
    int Tamanho;
    RegListaInvertida Reg[TAM_MAX_ARRAY];
} ListaInvertida;

IndicesPrimario _IndicesPrimario;
IndicesSecundario _IndicesSecNome;
IndicesSecundario _IndicesSecCurso;
ListaInvertida _ListaInvertida;

void IniciarListas() {
    int i;
    for (i = 0;  i <= (_IndicesPrimario.Tamanho-1); i++) {
        _IndicesPrimario.Indice[i].ByteOffSet = 0;
        _IndicesPrimario.Indice[i].ID = 0;
    }
    for (i = 0;  i <= (_IndicesSecCurso.Tamanho-1); i++) {
        _IndicesSecCurso.Indice[i].RRN = -1;
        _IndicesSecCurso.Indice[i].Valor[0] = '\0';
    }
    for (i = 0;  i <= (_IndicesSecNome.Tamanho-1); i++) {
        _IndicesSecNome.Indice[i].RRN = -1;
        _IndicesSecNome.Indice[i].Valor[0] = '\0';
    }
    for (i = 0;  i <= (_ListaInvertida.Tamanho-1); i++) {
        _ListaInvertida.Reg[i].ID = 0;
        _ListaInvertida.Reg[i].ProxRRNCurso = -1;
        _ListaInvertida.Reg[i].ProxRRNNome = -1;
    }
    _IndicesPrimario.Tamanho = 0;
    _IndicesSecCurso.Tamanho = 0;
    _IndicesSecNome.Tamanho = 0;
    _ListaInvertida.Tamanho = 0;
};

void SalvarListasPrimariaDisco(){
    FILE *arquivo;
    if ((arquivo = fopen(I_PRIMARIO ,"w+")) == NULL) {
            system("cls");
            printf("\nErro ao criar indice primario\n");
            getch();
            return 0;
            }

    int tamanho = 0;
    char registro[TAM_REGISTRO];
    int i;
    for (i = 0;  i <= (_IndicesPrimario.Tamanho-1); i++) {
        fprintf(arquivo, "%09d%s%06d%s",_IndicesPrimario.Indice[i].ByteOffSet, DELIMITADOR_FIELD,
                                    _IndicesPrimario.Indice[i].ID, DELIMITADOR_REGISTRO);
    }
    fclose(arquivo);
}

void SalvarListaSecundariaDisco(IndicesSecundario IndicesSec, char *FileName){
    FILE *arquivo;

    if ((arquivo = fopen(FileName ,"w+")) == NULL) {
            system("cls");
            printf("\nErro ao criar indice primario\n");
            getch();
            return 0;
            }

    int tamanho = 0;
    char registro[TAM_REGISTRO];
    int i;
    for (i = 0;  i <= (IndicesSec.Tamanho-1); i++) {
        fprintf(arquivo, "%05d%s%s%s",IndicesSec.Indice[i].RRN, DELIMITADOR_FIELD,
                                    IndicesSec.Indice[i].Valor, DELIMITADOR_REGISTRO);
    }
    fclose(arquivo);
}

void EncerrarListas () {
    SalvarListasPrimariaDisco();
    SalvarListaSecundariaDisco(_IndicesSecNome, I_NOME);
    SalvarListaSecundariaDisco(_IndicesSecCurso, I_CURSO);
}

void OrdenarListaPrimaria(IndicePrimario*indice, int esquerda, int direita){
    IndicePrimario aux;
    int i , j, meio, meio2;

    i = esquerda;
    j = direita;
    meio2 = (i + j)/2;
    meio = indice[meio2].ID;

    while(i < j) {
        while(indice[i].ID < meio) {
            i++;
        }
        while(indice[j].ID > meio){
            j--;
        }
        if(i <= j) {
            aux = indice[i];
            indice[i] = indice[j];
            indice[j] = aux;
            i++;
            j--;
        }
    }

    if(j > esquerda) {
        OrdenarListaPrimaria(indice, esquerda, j);
    }
    if(i < direita) {
        OrdenarListaPrimaria(indice, i, direita);
    }
}

void OrdenarListaSecundaria(IndiceSecundario*indice, int esquerda, int direita){
    IndiceSecundario aux;
    int i , j, meioVet;
    char meio[TAM_FIELD];

    i = esquerda;
    j = direita;
    meioVet = (i + j)/2;
    strncpy(meio, indice[meioVet].Valor, TAM_FIELD);

    while(i < j) {
        while(strcmp(indice[i].Valor, meio) == -1) {
            i++;
        }
        while(strcmp(indice[j].Valor, meio)==1){
            j--;
        }
        if(i <= j) {
            aux = indice[i];
            indice[i] = indice[j];
            indice[j] = aux;
            i++;
            j--;
        }
    }

    if(j > esquerda) {
        OrdenarListaSecundaria(indice, esquerda, j);
    }
    if(i < direita) {
        OrdenarListaSecundaria(indice, i, direita);
    }
}

void MontarIndices(){
    IniciarListas();
    MontarIndicePrimario();
    MontarListaInvEIndSecundarios();
    OrdenarListaPrimaria(_IndicesPrimario.Indice,0,_IndicesPrimario.Tamanho-1);
    OrdenarListaSecundaria(_IndicesSecNome.Indice,0,_IndicesSecNome.Tamanho-1);
    OrdenarListaSecundaria(_IndicesSecCurso.Indice,0,_IndicesSecCurso.Tamanho-1);
}

void MontarIndicePrimario (){
    FILE *arquivo;
    if ((arquivo = fopen(A_PRINCIPAL ,"r+")) == NULL) {
            system("cls");
            printf("\nNenhum registro encontrado\n");
            getch();
            return 0;
            }
    char Buff[9];
    char SubBuff[7];
    char SubBuffOffset[4];
    int posicaoOffset = 0;
    int inscricao = 0;
    int i=0;
    rewind(arquivo);
    while (fgets(Buff, 10, arquivo) != NULL) {
        SubBuff[0] = '\0';
        SubBuffOffset[0]= '\0';
            _IndicesPrimario.Indice[i].ByteOffSet = posicaoOffset;
            strncpy(SubBuffOffset, &Buff[0], 3);
            posicaoOffset += atoi(SubBuffOffset) + 3;
            strncpy(SubBuff, &Buff[3], 6);
            inscricao = atoi(SubBuff);
            _IndicesPrimario.Indice[i].ID = inscricao;
            fseek(arquivo, posicaoOffset, SEEK_SET);
            i =  i + 1;
    };
    _IndicesPrimario.Tamanho = i;
    fclose(arquivo);
    //printf("%d",_IndicesPrimario.Indice[0].ID);
}

void MontarListaInvEIndSecundarios () {
    Aluno a;
    int i;
    for (i = 0;  i <= (_IndicesPrimario.Tamanho-1); i++){
        _ListaInvertida.Reg[i].ID = _IndicesPrimario.Indice[i].ID;
        a = BuscaAluno(_IndicesPrimario.Indice[i].ByteOffSet);
        int findNome = 0;
        int auxNome = 0;
        int n;
        for (n = 0; n <= _IndicesSecNome.Tamanho-1; n++) {
            if (strcmp(a.Nome, _IndicesSecNome.Indice[n].Valor) == 0) {
                    findNome = 1;
                    auxNome = n;
            }
        }
        int ultimoRRN;
        if (findNome == 1){
            ultimoRRN = _IndicesSecNome.Indice[auxNome].RRN;
            while (_ListaInvertida.Reg[ultimoRRN].ProxRRNNome != - 1) {
              ultimoRRN = _ListaInvertida.Reg[ultimoRRN].ProxRRNNome;
            }
            _ListaInvertida.Reg[ultimoRRN].ProxRRNNome = i;
            _ListaInvertida.Reg[i].ProxRRNNome = -1;
        }else {
             strncpy(_IndicesSecNome.Indice[n].Valor, a.Nome, TAM_FIELD);
            _IndicesSecNome.Indice[n].RRN = i;
            _IndicesSecNome.Tamanho = n+1;
            _ListaInvertida.Reg[i].ProxRRNNome = -1;
        }

        int findCurso = 0;
        int auxCurso = 0;
        for (n = 0; n <= _IndicesSecCurso.Tamanho-1; n++) {
            if (strcmp(a.Curso, _IndicesSecCurso.Indice[n].Valor) == 0) {
                    findCurso = 1;
                    auxCurso = n;
            }
        }

        if (findCurso == 1){
            ultimoRRN = _IndicesSecCurso.Indice[auxCurso].RRN;
            while (_ListaInvertida.Reg[ultimoRRN].ProxRRNCurso != - 1) {
              ultimoRRN = _ListaInvertida.Reg[ultimoRRN].ProxRRNCurso;
            }
            _ListaInvertida.Reg[ultimoRRN].ProxRRNCurso = i;
            _ListaInvertida.Reg[i].ProxRRNCurso = -1;
        }else {
            strncpy(_IndicesSecCurso.Indice[n].Valor, a.Curso, TAM_FIELD);
            _IndicesSecCurso.Indice[n].RRN = i;
            _IndicesSecCurso.Tamanho = n+1;
            _ListaInvertida.Reg[i].ProxRRNCurso = -1;
        }
    }
}

#endif // INDICES_H_INCLUDED

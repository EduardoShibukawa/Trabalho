#include "Alunos.h"
#include <stdio.h>
#include <stdlib.h>

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
    _IndicesPrimario.Tamanho = 0;
    _IndicesSecCurso.Tamanho = 0;
    _IndicesSecNome.Tamanho = 0;
    _ListaInvertida.Tamanho = 0;
};

void EncerrarListas () {
//    SalvarListasPrimariaDisco;
//    SalvarListaSecundariaDisco;
}

void OrdernarListaPrimaria(){
}

void OrdenarListaSecundaria(){
}

void MontarIndices(){
    MontarIndicePrimario();
    MontarListaInvEIndSecundarios();
}

void MontarIndicePrimario (){
    FILE *arquivo;
    if ((arquivo = fopen(A_PRINCIPAL ,"r+")) == NULL) {
            system("cls");
            printf("\nNenhum registro encontrado\n");
            getch();
            return 0;
            }
    char Buff[8];
    char SubBuff[6];
    int posicaoOffset = 0;
    int inscricao;
    int i;
    rewind(arquivo);
    while (!feof(arquivo)) {
        fread(&posicaoOffset,1,sizeof(posicaoOffset),arquivo);
        fread(SubBuff, sizeof(char), 6, arquivo);
        inscricao = atoi(SubBuff);
        _IndicesPrimario.Indice[i].ByteOffSet = posicaoOffset;
        _IndicesPrimario.Indice[i].ID = inscricao;
        fseek(arquivo, posicaoOffset - 4, SEEK_CUR);
        /*
        fgets(Buff, 8, arquivo);
        _IndicesPrimario.Indice[i].ByteOffSet = posicaoOffset;
        strncpy(SubBuff, &Buff[0], 2);
        posicaoOffset = atoi(SubBuff) + 2;
        strncpy(SubBuff, &Buff[2], 6);
        inscricao = atoi(SubBuff);
        _IndicesPrimario.Indice[i].ID = inscricao;
        fseek(arquivo, posicaoOffset - 6, SEEK_CUR);
        */
        i =  i + 1;
    };
    _IndicesPrimario.Tamanho = i;
    fclose(arquivo);
//    OrdenarListaPrimaria();
}

void MontarListaInvEIndSecundarios () {
    Aluno a;
    int i;
    for (i = 0;  i <= _IndicesPrimario.Tamanho; i++){
        _ListaInvertida.Reg[i].ID = _IndicesPrimario.Indice[i].ID;
        a = BuscaAluno(_IndicesPrimario.Indice[i].ByteOffSet);
        int findNome = 0;
        int auxNome = 0;
        int n;
        for (n = 0; n <= _IndicesSecNome.Tamanho; n++) {
            if (a.Nome == _IndicesSecNome.Indice[n].Valor) {
                    findNome = 1;
                    auxNome = n;
            }
        }
        int ultimoRRN;
        if (findNome = 1){
            ultimoRRN = _IndicesSecNome.Indice[auxNome].RRN;
            while (_ListaInvertida.Reg[ultimoRRN].ProxRRNNome != - 1) {
              ultimoRRN = _ListaInvertida.Reg[ultimoRRN].ProxRRNNome;
            }
            _ListaInvertida.Reg[ultimoRRN].ProxRRNNome = i;
            _ListaInvertida.Reg[i].ProxRRNNome = -1;
        }else {
             strncpy(_IndicesSecNome.Indice[n].Valor, a.Nome, TAM_FIELD);
            _IndicesSecNome.Indice[n].RRN = i;
            _IndicesSecNome.Tamanho = n;
            _ListaInvertida.Reg[i].ProxRRNNome = -1;
        }

        int findCurso = 0;
        int auxCurso = 0;
        for (n = 0; n <= _IndicesSecCurso.Tamanho; n++) {
            if (strcmp(a.Curso, _IndicesSecCurso.Indice[n].Valor) == 1) {
                    findCurso = 1;
                    auxCurso = n;
                    break;
            }
        }

        if (findCurso = 1){
            ultimoRRN = _IndicesSecCurso.Indice[auxCurso].RRN;
            while (_ListaInvertida.Reg[ultimoRRN].ProxRRNCurso != - 1) {
              ultimoRRN = _ListaInvertida.Reg[ultimoRRN].ProxRRNCurso;
            }
            _ListaInvertida.Reg[ultimoRRN].ProxRRNCurso = i;
            _ListaInvertida.Reg[i].ProxRRNCurso = -1;
        }else {
            strncpy(_IndicesSecNome.Indice[n].Valor, a.Nome, TAM_FIELD);
            _IndicesSecCurso.Indice[n].RRN = i;
            _IndicesSecCurso.Tamanho = n;
            _ListaInvertida.Reg[i].ProxRRNCurso = -1;
        }
//        OrdernarListaSecundaria(_IndiceSecundarionNome);
 //       OrdernarListaSecundaria(_IndiceSecundarioCurso);
    }
}

#endif // INDICES_H_INCLUDED

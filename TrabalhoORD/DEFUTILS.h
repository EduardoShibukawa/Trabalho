#ifndef DEFUTILS_H_INCLUDED
#define DEFUTILS_H_INCLUDED

#define A_PRINCIPAL "PRINCIPAL.TXT"
#define A_DADOS "dados.txt"
#define TAM_FIELD 50
#define TAM_REGISTRO 150
#define DELIMITADOR_FIELD "|"
#define DELIMITADOR_REGISTRO "|"
#define DELIM '|'
#define INDICE_PRIMARIO 1
#define INDICE_SEC_NOME 2
#define INDICE_SEC_CURSO 3
#define TAM_MAX_ARRAY 1000
#define I_PRIMARIO "I_PRIMARIO.TXT"
#define I_NOME "I_NOME.TXT"
#define I_CURSO "I_CURSO.TXT"

typedef struct{
    int Inscricao;
    char Nome[TAM_FIELD];
    char Curso[TAM_FIELD];
    char NotaFinal[TAM_FIELD];
} Aluno;

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

#endif // DEFUTILS_H_INCLUDED

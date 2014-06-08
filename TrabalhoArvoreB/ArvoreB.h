#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#include "ArvoreB_Arquivo.h"
#include <stdlib.h>
#include <string.h>

//BTREE
#define MAX_KEYS 4
#define MIN_KEYS 2
// INSERÇÃO
#define ERROR -1
#define NO_PROMOTION 0
#define PROMOTION 1
//BUSCA
#define KEY_FOUND 1
#define KEY_NOT_FOUND 0
// ARQUIVO
#define A_ARVOREB "FUCK.txt"
#define A_DISPONIVEL "Disponivel.txt"
#define DELIMITADOR_REGISTRO "|"
#define DELIMITADOR_REMOVE "*"
#define DELIMITADOR_INSERE "+"
#define BYTEOFFSET sizeof(BTPage);
//OUTROS
#define NULL_INTERNAL -1

typedef struct{ //Registro
    int chave;
    int byteOffSet;
} Registro;

typedef struct { //BTPage
    int numeroChaves;
    Registro registro[MAX_KEYS];
    int child[MAX_KEYS + 1];
    int Deleted;
} BTPage;

void InicializarBTPage(BTPage *p) {
    int i;
    p->numeroChaves = 0;
    p->child[0] = NULL_INTERNAL;
    p->Deleted = 0;
    for (i = 0; i < MAX_KEYS; i++) {
        p->child[i+1] = NULL_INTERNAL;
        p->registro[i].chave = NULL_INTERNAL;
        p->registro[i].byteOffSet = NULL_INTERNAL;
    }
}
//ARQUIVO
BTPage *CarregaPagina(int RRN){
    BTPage p;
    InicializarBTPage(&p);
    FILE *arquivo;
    if ((arquivo = fopen(A_ARVOREB ,"r")) == NULL) {
            system("cls");
            printf("\nNenhum registro encontrado\n");
            getch();
            return &p;
    }
    int byteOffSet = (RRN  - 1) * BYTEOFFSET;
    byteOffSet = byteOffSet + sizeof(int);
    fseek(arquivo, byteOffSet, SEEK_SET);
    fread(&p, sizeof(BTPage), 1, arquivo);
    if (p.Deleted == 1){
        InicializarBTPage(&p);
    }
    fclose(arquivo);
    return &p;
}

void AtualizarCabecalho(int RRN) {
    FILE *arquivo;
    if ((arquivo = fopen(A_ARVOREB ,"r+")) == NULL) {
        if ((arquivo = fopen(A_ARVOREB ,"w+")) == NULL) {
                system("cls");
                printf("\nNenhum registro encontrado\n");
                getch();
                return 0;
        }
    }
    fseek(arquivo, 0, SEEK_SET);
    fwrite(&RRN, sizeof(int), 1, arquivo);
    fclose(arquivo);
}

void SalvarPagina(BTPage *page, int RRN) {
    FILE *arquivo;
    if ((arquivo = fopen(A_ARVOREB ,"r+")) == NULL) {
            system("cls");
            printf("\nNenhum registro encontrado\n");
            getch();
            return 0;
    }

    int byteOffSet = (RRN - 1) * BYTEOFFSET;
    byteOffSet = byteOffSet + sizeof(int);
    fseek(arquivo, byteOffSet, SEEK_SET);
    fwrite(page, sizeof(BTPage), 1, arquivo);
    fclose(arquivo);
}

void RemoverPagina(int RRN) {
    FILE *arquivo;
    if ((arquivo = fopen(A_ARVOREB ,"r+")) == NULL) {
            system("cls");
            printf("\nNenhum registro encontrado\n");
            getch();
            return 0;
    }
    int byteOffSet = RRN * (sizeof(BTPage) + sizeof DELIMITADOR_REMOVE);
    byteOffSet += sizeof RRN;
    fseek(arquivo, byteOffSet, SEEK_SET);
    fwrite(DELIMITADOR_REMOVE, sizeof DELIMITADOR_REMOVE, 1, arquivo);
    fclose(arquivo);
}

int AchaRRNRaiz(){
    FILE *arquivo;
    if ((arquivo = fopen(A_ARVOREB ,"r")) == NULL) {
            return NULL_INTERNAL;
    }

    fseek(arquivo, 0, SEEK_SET);
    int RRN;
    fread(&RRN, sizeof(int), 1, arquivo);
    fclose(arquivo);
    return RRN;
}

int AcharRRNDisponivel(){
    int RRN;
    FILE *arquivo;
    if ((arquivo = fopen(A_DISPONIVEL ,"r+")) == NULL) {
        AtualizarRRNDisponivel(2, 0);
        return 1;
    }
    char *Delim = malloc(sizeof(char)* (strlen(DELIMITADOR_REMOVE) + 1));
    int byteOffSet =  sizeof RRN + sizeof(char) + 1;
    fseek(arquivo, -byteOffSet, SEEK_END);
    fread(Delim, sizeof(char), strlen(DELIMITADOR_REMOVE), arquivo);
    fread(&RRN, sizeof(int), 1, arquivo);
    if (strcmp(Delim, DELIMITADOR_REMOVE) == 0) {
        fseek(arquivo, -byteOffSet , SEEK_END);
    }
    fclose(arquivo);
    AtualizarRRNDisponivel(RRN + 1, 0);
    return RRN;
}

void AtualizarRRNDisponivel(int RRN, int isDeletedRRN){
    FILE *arquivo;
    if ((arquivo = fopen(A_DISPONIVEL ,"r+")) == NULL) {
        if ((arquivo = fopen(A_DISPONIVEL ,"w+")) == NULL) {
                system("cls");
                printf("\nNenhum registro encontrado\n");
                getch();
                return 0;
        }
    }
    char *Delim;
    if (isDeletedRRN == 1) {
        fseek(arquivo, 0, SEEK_END);
        Delim = DELIMITADOR_REMOVE;
    }
    else {
        fseek(arquivo, 0, SEEK_SET);
        Delim = DELIMITADOR_REMOVE; // DELIMITADOR_INSERE;
    }
    fwrite(Delim, sizeof(char), strlen(Delim), arquivo);
    fwrite(&RRN, sizeof(int), 1, arquivo);
    fclose(arquivo);
}

int Buscar(int Chave, int RRN){
  	if (RRN == NULL_INTERNAL){ //se ficar loop infinito, colocar verificação para NULL (ponteiro de pagina nao existente(depois da folha))
            return (KEY_NOT_FOUND);
    } else {
        BTPage p;
        p = *CarregaPagina(RRN); //carrega em memoria primaria pagina apontado por RRN
		int i = 0;
		int achou = KEY_NOT_FOUND;
		for (i = 0; ((i <= p.numeroChaves) //p procura Chave na pagina carregada
            && (Chave <= p.registro[i].chave )); i++) {
                if (p.registro[i].chave == Chave)
                    achou = KEY_FOUND;
            }
		if (achou == KEY_FOUND) {
			return (achou);
		}
		else {
		    if (Chave < p.registro[i].chave){//ponteiro = ponteiro para a próxima página da possível ocorrência de Chave
                RRN = p.child[i];
		    }else{
                RRN = p.child[i++];
            }
			return (Buscar (Chave, RRN));
		}
	}
}

void Insercao(Registro registro){
    /*se o arquivo B-tree existe, então
    abra o arquivo B-tree
    senão
    crie um arquivo B-tree e coloque a primeira chave na raiz
    recupere o RRN da página raiz do arquivo e armazene em ROOT*/
    int ROOT = AchaRRNRaiz();
    if (ROOT == NULL_INTERNAL) {
        BTPage p;
        InicializarBTPage(&p);
        p.numeroChaves = 1;
        p.registro[0] = registro;
        ROOT =AcharRRNDisponivel();
        AtualizarCabecalho(ROOT);
        SalvarPagina(&p, ROOT);
    }
    else {
        Registro RegPromooFilho;
        RegPromooFilho.byteOffSet = NULL_INTERNAL;
        RegPromooFilho.chave = NULL_INTERNAL;
        int RRNPromoFilha = NULL_INTERNAL;
        if (InsercaoInterna(ROOT, registro, &RegPromooFilho, &RRNPromoFilha) == PROMOTION) {
            DivisaoRaiz(RegPromooFilho, RRNPromoFilha);
        }
    }
}

int InsercaoInterna(int RRN, Registro registro, Registro *registroPromovido, int *RRNPromoFilha) {
    BTPage p; //carrega em memoria primaria pagina apontado por RRN
    int i = -1;
    int RRNInicio = RRN;
    p = *CarregaPagina(RRN);
    int achou = KEY_NOT_FOUND;
	if (RRN == NULL_INTERNAL) { //se ponteiroRaiz nao aponta para nenhuma pagina
		*registroPromovido = registro;
		return(PROMOTION);
	} else {

        for (i = 0; ((i < p.numeroChaves) && (registro.chave >= p.registro[i].chave )); i++) { //p procura Chave na pagina carregada
                if (p.registro[i].chave == registro.chave){
                    achou = KEY_FOUND;
                }
        }

        if (achou == KEY_NOT_FOUND) {
                RRN = p.child[i];
        }
	}

	if (achou == KEY_FOUND) {
		return(ERROR); //chave ja esta na arvore, retorne uma flag de erro -nao pode inserir 2 chaves iguais
	}

	int flagRetorno = InsercaoInterna(RRN, registro, registroPromovido, RRNPromoFilha);//procedimento recursivo
	RRN = RRNInicio;

	if (flagRetorno != PROMOTION) {
		return(flagRetorno);
	} else if (p.numeroChaves < MAX_KEYS) {

		/*
		insere chavePromovida na página P
		escreve página P em arquivo
		*/
        for (i = p.numeroChaves-1;i >= 0; i--) {
            if (p.numeroChaves == 1) {
                if (p.registro[i].chave < registroPromovido->chave) {
                        p.registro[i + 1] = *registroPromovido;
                        p.child[i+2] = *RRNPromoFilha;
                }else {
                    p.registro[i + 1] = p.registro[i];
                    p.child[i+2] = p.child[i+1];
                    p.child[i+1] = *RRNPromoFilha;
                    p.registro[i] = *registroPromovido;
                }
            } else {
                if (p.registro[i].chave < registroPromovido->chave) {
                        p.registro[i + 1] = *registroPromovido;
                        p.child[i+2] = *RRNPromoFilha;
                        i = -1;
                }else {
                    p.registro[i + 1] = p.registro[i];
                    p.registro[i] = registro;
                    p.child[i+2] = p.child[i+1];

                }
            }
        }
        p.numeroChaves = p.numeroChaves + 1;
		SalvarPagina(&p, RRNInicio);
		return(NO_PROMOTION);
    } else { //nao ha espaço em P para key
		/*
		realize operação de split em P
		escreva em arquivo  a nova página e a página P
		*/
        BTPage newPage;
        InicializarBTPage(&newPage);
		Split(RRN, registro, &p, registroPromovido, RRNPromoFilha, &newPage);
        SalvarPagina(&newPage, *RRNPromoFilha);
        SalvarPagina(&p, RRN);
		return(PROMOTION);
	}
}

void DivisaoRaiz(Registro registro, int RRNPRomoFilha) {
    BTPage novaRaiz;
    InicializarBTPage(&novaRaiz);
    int novoRRNRaiz = AcharRRNDisponivel();
    novaRaiz.numeroChaves = 1;
    novaRaiz.registro[0] = registro;
    novaRaiz.child[0] = AchaRRNRaiz();
    novaRaiz.child[1] = RRNPRomoFilha;
    SalvarPagina(&novaRaiz, novoRRNRaiz);
    AtualizarCabecalho(novoRRNRaiz);
}

void Split (int RRN, Registro registro, BTPage *page, Registro *registroPromovido, int *RRNPromoFilha, BTPage *newPage) {
    int i;
    Registro auxReg[MAX_KEYS + 1];
    int j = 0;
    int inseriu = 0;
    for (i = 0; i <= MAX_KEYS; i++) {
        if ( (j!= 4) && ((registro.chave > page->registro[j].chave) || (inseriu == 1))) {
            auxReg[i] = page->registro[j];

            page->child[j] = NULL_INTERNAL;
            page->registro[j].byteOffSet = NULL_INTERNAL;
            page->registro[j].chave = NULL_INTERNAL;
            j++;
        }
        else {
            auxReg[i] = registro;
            page->child[j] = NULL_INTERNAL;
            inseriu = 1;
        }
    }

    for (i = 0; i <= MAX_KEYS; i++) {
        if (i < 2){
            page->registro[i] = auxReg[i];
        } else if ((MAX_KEYS/2) != i ) {
            newPage->registro[i - 3] = auxReg[i];
        }
    }
    page->numeroChaves = 2;
    newPage->numeroChaves = 2;
    *registroPromovido = auxReg[2];
    *RRNPromoFilha = AcharRRNDisponivel();
}

#endif // ARVOREB_H_INCLUDED
